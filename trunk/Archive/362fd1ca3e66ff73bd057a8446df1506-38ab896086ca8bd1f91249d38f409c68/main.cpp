#include <memory>

struct Device
{
    static std::shared_ptr<Device> create();
};


struct DeviceImpl : Device
{
};


std::shared_ptr<Device> Device::create()
{
    return std::make_shared<DeviceImpl>();
}

