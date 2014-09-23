#include <iostream>
#include <iomanip>
int main()
{
    for(int num=0;num<100;++num){
        std::cout << std::setfill('0') <<
                     std::setw(3) << num<<' ';
    }
}
