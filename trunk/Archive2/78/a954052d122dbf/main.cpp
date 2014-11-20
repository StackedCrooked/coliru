#include <iostream>

struct Object
{
    int a[10]; // change to 1 and the warning disappears
    Object() {}
    ~Object() {}
};

void Deconstruct(Object* objects, size_t num_objects)
{
    while(num_objects) objects[--num_objects].~Object();
}

void foo(Object* o)
{
    Deconstruct(o, 0x1FFFFFFFFFFFFFFFll);
}

int main(int argc, char* argv[]) 
{
    std::cout << "gcc version: " << __VERSION__ << "\nfinished\n";
}
