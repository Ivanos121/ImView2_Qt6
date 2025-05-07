#ifndef ARCHIVERCHANNEL_H
#define ARCHIVERCHANNEL_H

#include <stdint.h>

class ArchiverChannel
{
public:
    ArchiverChannel();

    uint16_t rawStatus;
    uint32_t rawValue;
};

union RawAndFloat
{
    float floatValue;
    uint32_t rawValue;
};

#endif // ARCHIVERCHANNEL_H
