#include <iostream>
int main()
{
    unsigned long data = 0x0010;
    unsigned int N = 2;

    unsigned long* MyPt = &data;
    unsigned char* MyBytePt = reinterpret_cast<unsigned char*>(MyPt);
    MyBytePt[N] = 0x12;


    std::cout << "size of long is " << sizeof data  << '\n'
              << std::hex << std::showbase << *MyPt << '\n';
}