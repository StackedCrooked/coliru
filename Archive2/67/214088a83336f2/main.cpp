#include <stdio.h>

struct global_type {
    virtual ~global_type() { printf("global_type::~global_type()\n"); }
}; /* struct global_type */

namespace local {

struct base_type : public global_type {
    virtual ~base_type() { printf("base_type::~base_type()\n"); }
    
    virtual const char* get_type_name() const = 0;
}; /* struct base_type */

namespace network {
    
struct derived_type : public base_type {
    derived_type()
    {
        printf("network::derived_type::derived_type()\n");
    }

    ~derived_type()
    {
        printf("network::derived_type::~derived_type()\n");
    }
    
    const char* get_type_name() const
    {
        return "network::derived_type";
    }
}; /* struct derived_type */

} /* namespace network */

namespace usb {
    
struct derived_type : public base_type {
    derived_type()
    {
        printf("usb::derived_type::derived_type()\n");
    }

    ~derived_type()
    {
        printf("usb::derived_type::~derived_type()\n");
    }
    
    const char* get_type_name() const
    {
        return "usb::derived_type";
    }
}; /* struct derived_type */

} /* namespace usb */

} /* namespace local */
     
int main(int argc, char* argv[])
{
    local::base_type* object = new local::network::derived_type();
    printf("Object type is %s\n", object->get_type_name());
    //global_type* global_object = object;
    delete object;

    return 0;
}
