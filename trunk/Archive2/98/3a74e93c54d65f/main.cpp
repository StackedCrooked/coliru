#include <stdio.h>

class type_impl;

class type {
public:
    type();
    ~type();

    void print();

protected:
    type_impl* impl_;
}; /* class type */

class type_impl {
public:
    type_impl(int value)
        : value(value) {}

    int value;
}; /* class type_impl */

type::type()
    : impl_(new type_impl(1337))
{
}
    
type::~type()
{
    delete impl_;
}

void type::print()
{
    printf("value = %d\n", impl_->value);
}

namespace internal {

class type : public ::type {
public:
    type_impl* get_implementation()
    {
        return impl_;
    }
}; /* class type */

} /* namespace internal */

int main(int argc, char* argv[])
{
    type object;
    object.print();

    internal::type& internal_object = static_cast<internal::type&>(object);
    internal_object.get_implementation()->value = 7331;
    
    object.print();
    return 0;
}
