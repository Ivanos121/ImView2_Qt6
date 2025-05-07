#ifndef BVAS_H
#define BVAS_H

#include <libusb-1.0/libusb.h>

extern uint16_t data_buffer[6400][6];

typedef struct
{
  int size;
  uint8_t * data;
}t_pack;

int init_bvas(void);
int read_data_block_bvas(void);
void stop_bvas(void);
int bulk_write_packages(libusb_device_handle *bvas_handle,int first, int last,
                        t_pack *packs, int endpoint);
int bulk_read_data(libusb_device_handle *bvas_handle,int endpoint,
                   uint8_t *data, int size);

#endif
