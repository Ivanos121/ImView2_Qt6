#include <QThread>

#include "device.h"
#include "bvas.h"

Device::Device()
{

}

int Device::init()
{
  if(init_bvas())
  {
      emit bvasFailure();
      return 1;
  }

  return 0;
}

void Device::readData()
{
    if(read_data_block_bvas())
    {
        emit bvasFailure();
    }
    else
    {
        memcpy(buf,data_buffer,6400*6*2);
    }
}

void Device::stop()
{
    stop_bvas();
}
