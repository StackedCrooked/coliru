#include <iostream>
#include <string>

int main()
{
    static const int SIZE = 60;
    char text [SIZE+1]= "06fb7405eba8d9e94fb1f28f0dd21fdec55fd54750ee84d95ecccf2b1b48";
    unsigned short hex[SIZE/2] = {0};
    int i=0;
    for(char *p = text; p < text + SIZE; p+=2, i++){
        hex[i] = std::stoul("0x"+std::string(p,2), nullptr, 16);
    }
    
    std::cout<< std::hex << std::endl;
    for (auto &i: hex){
        std::cout<< i << " ";
    }
}
