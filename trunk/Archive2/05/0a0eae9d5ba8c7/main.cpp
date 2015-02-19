#include <iostream>

struct Class1
{
    int data;
    int *dataPtr;
};

int main()
{
     Class1 object;
     object.data = 1100;
     object.dataPtr = &(object.data);

     std::cout << object.dataPtr << std::endl;
     std::cout << (void *) (object.data) << std::endl;
     std::cout << (void *) &(object.data) << std::endl;
}