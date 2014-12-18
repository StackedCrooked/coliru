#include <memory>
#include <stdio.h>
#include <stdint.h>

typedef std::shared_ptr<int> int_ptr;

class type {
public:
    type(int value)
        : value_(std::make_shared<int>(value)),
          value_ptr_(value_.get())
    {
        printf("value_ptr_ = %p\n", (void*) value_ptr_);
        value_ptr_ = value_.get();
        printf("value_ptr_ = %p\n", (void*) value_ptr_);
    }
    
    void print()
    {
        printf("Value = %d\n", *value_ptr_);
    }

private:
    int* value_ptr_;
    int_ptr value_;
}; /* class type */

int main(int argc, char* argv[])
{
    type object(1337);
    object.print();
    return 0;
}
