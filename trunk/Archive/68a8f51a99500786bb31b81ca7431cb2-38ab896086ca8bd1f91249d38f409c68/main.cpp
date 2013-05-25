#include <memory>

//
// HEADER file
//
struct Device
{
    static std::shared_ptr<Device> create();
};


//
// CPP file
//
namespace {

struct DeviceImpl : Device
{
};

} // anonymous

std::shared_ptr<Device> Device::create()
{
    return std::make_shared<DeviceImpl>();
}

