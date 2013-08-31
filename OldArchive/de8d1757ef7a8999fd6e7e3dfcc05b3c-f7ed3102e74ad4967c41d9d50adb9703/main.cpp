#include <iostream>
#include <memory>
#include <string>

//
// HEADER file
//
struct Device
{
    static std::shared_ptr<Device> create();
    
    std::string get_name() const;
};


//
// CPP file
//
namespace {

struct DeviceImpl : Device
{
    std::string get_name_impl() const
    {
        return "foo";
    }
};

} // anonymous

std::shared_ptr<Device> Device::create()
{
    return std::make_shared<DeviceImpl>();
}


std::string Device::get_name() const
{
    return static_cast<const DeviceImpl&>(*this).get_name_impl();
}



//
// USER
//
int main()
{
    Device d;
    std::cout << d.get_name() << std::endl;
}