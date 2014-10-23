#include <iostream>
#include <thread>
#include <utility>
#include <vector>

template<class T> T max(T a, T b) { return a>b?a:b; }

//int max(int,int) { return 4;}
int main()
{

    int a =1;
    int b = 0;
    char c = 'c';
    char d = 'd';

    std::cout << " max(a,b) " <<  max(a,b) << std::endl;
    // max(int a, int b)
    std::cout << " max(a,b) " <<  max(c,d) << std::endl;
    // max(char a, char b)
    //std::cout << " max(a,b) " <<  max(a,c) << std::endl;
    


}
