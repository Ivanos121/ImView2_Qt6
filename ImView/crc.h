#include <sys/types.h>

#if (_tCRC_MRTU == 0)
__inline u_int16_t MRTU_CRC(u_int8_t* data, ushort len)
{
    ushort res_CRC = 0xFFFF;
    ushort count = 0;
    u_int8_t count_crc;
    u_int8_t dt;
    while(count < len)
    {
        //
        count_crc = 0;
        dt = (u_int8_t)(data[count]);
        res_CRC ^= (ushort)(dt);
        //
        while(count_crc < 8)
        {
            if((res_CRC & 0x0001) < 1)
            {
                res_CRC = (res_CRC >> 1) & 0x7FFF;
            }
            else
            {
                res_CRC = (res_CRC >> 1) & 0x7FFF;
                res_CRC ^= 0xA001;
            };
            count_crc++;
        };
        count++;
    }
    return (res_CRC);
}
#else
__inline u_int16_t MRTU_CRC(u_int8_t *data, ushort len)
{
    u_int8_t uchCRCHi = 0xFF;
    u_int8_t uchCRCLo = 0xFF;
    u_int16_t uIndex ;
    while(len--)
    {
        uIndex = uchCRCHi ^ *data++ ;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
        uchCRCLo = auchCRCLo[uIndex] ;
    }
    return (((u_int16_t)(uchCRCLo) << 8) | (u_int16_t)(uchCRCHi));
}

#endif // CRC_H
