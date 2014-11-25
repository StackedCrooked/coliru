#include <memory>

#include <stdio.h>

class object {
public:
    object();
    ~object();

    void print();

private:
    void* impl_;
}; /* class object */

struct object_impl {
    int value = 1337;
}; /* struct object_impl */

#define impl reinterpret_cast<std::shared_ptr<object_impl>*>(impl_)

object::object()
    : impl_(new std::shared_ptr<object_impl>(std::make_shared<object_impl>()))
{
}

object::~object()
{
    delete impl;
}

void object::print()
{
    printf("Value = %d\n", impl->get()->value);
}

int main(int argc, char* argv[])
{
    object o;
    o.print();
    return 0;
}
