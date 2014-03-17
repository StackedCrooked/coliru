
#include <limits>
#include <new>
#include <iostream>

int main(int argc, char** argv) {
    typedef unsigned char byte;
    byte*gb;
    try{
        gb=new byte[std::numeric_limits<std::size_t>::max()];
    }
    catch(const std::bad_alloc&){
        std::cout<<"Normal"<<std::endl;
        return 0;}
    try
    {
        gb[0] = 1;
        gb[std::numeric_limits<std::size_t>::max() - 1] = 1;
        std::cout << gb[0] << gb[std::numeric_limits<std::size_t>::max() - 1] << "\n";
    }
    catch ( ... )
    {
        std::cout << "On access\n";
    }
    delete[]gb;
    std::cout<<"Abnormal"<<std::endl;
    return 1;
}