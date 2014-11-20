#include <iostream>

struct Object
{
    Object() {}
    ~Object() {}
};

void Deconstruct(Object* objects, size_t num_objects)
{
    while(num_objects) objects[--num_objects].~Object();
}

int main(int argc, char* argv[]) 
{
    std::cout << "gcc version: " << __VERSION__ << "\nfinished\n";
}
