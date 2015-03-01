#include <iostream>

typedef unsigned char Byte;

int main()
{
    int value = 300;
    Byte* byteArray = static_cast<Byte*>(&value);
    if (byteArray[0] > 0)
    {
        std::cout<< "This line is never reached. Trying to access the array index results in a seg-fault." << std::endl;
    }
}
