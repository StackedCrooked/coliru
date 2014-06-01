#include <iostream>
#include <memory>

struct CustomDeleter
{
    template <typename T>
    void operator()(T* ptr)
    {
        std::cout << "they see me deletin'\n" "they hatin'\n\n";
        delete ptr;
    }
};

int main()
{
    std::shared_ptr<int> ptr(new int(1), CustomDeleter());
    
    ptr.reset(new int(2));
    
    ptr.reset(new int(3));
}
