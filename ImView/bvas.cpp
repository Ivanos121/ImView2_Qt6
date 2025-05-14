#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "bvas.h"

#define CAPTURE_PACK_SIZE 12800

#define BUFFER_SIZE 62500

uint16_t data_buffer[6400][6];
uint8_t back_data_buffer[100000];

t_pack packs[100500];

libusb_device_handle *bvas_handle;


void print_transfer_error_information(int error)
{
    switch (error)
    {
    case LIBUSB_ERROR_TIMEOUT:
        fprintf(stderr,"Transfer timeout");
        break;
    case LIBUSB_ERROR_PIPE:
        fprintf(stderr,"endpoint halted");
        break;
    case LIBUSB_ERROR_OVERFLOW:
        fprintf(stderr,"device offered more data");
        break;
    case LIBUSB_ERROR_NO_DEVICE:
        fprintf(stderr,"device has been disconnected");
        break;
    default:
        fprintf(stderr,"Bulk transfer error %d\n",error);
    }
}

int bulk_write_packages(libusb_device_handle *bvas_handle,int first, int last,
                        t_pack *packs, int endpoint)
{
    int transfer_res;
    int transferred;
    for (int i=first;i<last;i++)
    {
        transfer_res = libusb_bulk_transfer(bvas_handle, endpoint,\
                                                                  packs[i].data, packs[i].size, &transferred, 0);
        if (transfer_res!=0)
        {
            print_transfer_error_information(transfer_res);
            return 1;
        }
        if (transferred!=packs[i].size)
        {
            fprintf(stderr,"Packet size %d bytes, transferred only %d bytes\n",\
                                                                                packs[i].size,transferred);
            return 1;
        }
    }
    return 0;
}

int bulk_read_data(libusb_device_handle *bvas_handle,int endpoint, uint8_t
                                                                        *data, int size)
{
    int transfer_res;
    int transferred;
    transfer_res = libusb_bulk_transfer(bvas_handle, endpoint,		\
                                        data, size, &transferred, 0);
    if (transfer_res!=0)
    {
        print_transfer_error_information(transfer_res);
        return 1;
    }
    if (transferred!=size)
    {
        fprintf(stderr,"Received %d bytes instead of %d bytes\n",transferred,size);
        return 1;
    }
    return 0;
}

int read_capture_file(t_pack *packs, const char * cap_filename)
{
    int packs_counter = 0;
    FILE *capfile;
    capfile = fopen(cap_filename,"r");
    if (capfile)
    {
        char buffer[100500];
        uint8_t bin_buffer[100500];

        while (!feof(capfile))
        {
            char *p_end_sym;
            char *p_begin_sym = buffer;
            fscanf(capfile,"%s", buffer);
            int i;
            for(i = 0;i<100500;i++)
            {
                bin_buffer[i] = (uint8_t)strtol(p_begin_sym, &p_end_sym, 16);
                if (!(*p_end_sym))
                    break;
                p_begin_sym = p_end_sym + 1;
            }

            packs[packs_counter].data = (uint8_t *)malloc(i+1);
            memcpy(packs[packs_counter].data, bin_buffer, i+1);
            packs[packs_counter].size = i+1;
            packs_counter++;
        }
        fclose(capfile);
    }
    else
    {
        fprintf(stderr,"Can not open capture file %s\n",cap_filename);
        return 0;
    }
    return packs_counter;
}

int init_bvas(void)
{
    int packs_count = read_capture_file(packs, "testcapture6signalsfullz.txt");
    if (!packs_count)
    {
        fprintf(stderr,"Reading capture file failed\n");
        return 1;
    }

    if(libusb_init(NULL)!=0)
    {
        fprintf(stderr,"libusb initialization failed\n");
        return 1;
    }

    bvas_handle = libusb_open_device_with_vid_pid(NULL, 0x0471, 0x0666);
    if (bvas_handle==NULL)
    {
        fprintf(stderr,"BVAS not found on usb\n");
        return 1;
    }
    printf("resetted: %d\n",libusb_reset_device(bvas_handle));
    int claim_res = libusb_claim_interface(bvas_handle, 0);
    if (claim_res!=0)
    {
        switch (claim_res)
        {
        case LIBUSB_ERROR_NOT_FOUND:
            fprintf(stderr,"Interface 0 not found\n");
            break;
        case LIBUSB_ERROR_BUSY:
            fprintf(stderr,"Interface 0 busy\n");
            break;
        case LIBUSB_ERROR_NO_DEVICE:
            fprintf(stderr,"Device disconnected\n");
            break;
        default:
            fprintf(stderr,"Interface 0 error %d\n",claim_res);
        }
        return 1;
    }

    if (!bulk_write_packages(bvas_handle, 0, 4, packs, 0x03))
        if (!bulk_read_data(bvas_handle, 0x82, back_data_buffer, 64))
            if (!bulk_write_packages(bvas_handle, 4, 7, packs, 0x03))
                if (!bulk_read_data(bvas_handle, 0x82, back_data_buffer, 9088))
                    if (!bulk_write_packages(bvas_handle, 7, 20, packs, 0x03))
                        if (!bulk_write_packages(bvas_handle, 20, 21, packs, 0x01))
                            if (!bulk_write_packages(bvas_handle, 21, 53, packs, 0x03))
                            {
                                printf("BVAS init OK!\n");
                                return 0;
                            }

    return 1;
}

int read_data_block_bvas(void)
{
    uint8_t * data_pointer = (uint8_t*)&data_buffer[0][0];
    for (int i=0;i<6;i++)
    {
        if (bulk_read_data(bvas_handle, 0x82, (uint8_t *)data_pointer,
                           CAPTURE_PACK_SIZE))
        {
            //printf("resetted: %d\n",libusb_reset_device(bvas_handle));
            return 1;
        }
        data_pointer += CAPTURE_PACK_SIZE;
    }
    return 0;
}

void stop_bvas(void)
{
    if (!bulk_write_packages(bvas_handle, 53, 54, packs, 0x03))
    {
        bulk_read_data(bvas_handle, 0x82, back_data_buffer,
                       CAPTURE_PACK_SIZE);
        bulk_read_data(bvas_handle, 0x82, back_data_buffer,
                       CAPTURE_PACK_SIZE);
        if (!bulk_write_packages(bvas_handle, 54, 55, packs, 0x03))
        {
            bulk_read_data(bvas_handle,
                           0x82,back_data_buffer,
                           CAPTURE_PACK_SIZE);
            bulk_write_packages(bvas_handle, 55, 56, packs, 0x03);
        }
    }
}
