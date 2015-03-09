#include <iostream>

int main()
{   
    bool tf = true;
    char a = 'a';
    short int b = 24;
    int c = 30000;
    long int d = 123000;
    long long int e = 9999999999;
    float f = 9.3;
    double g = 2.3e-24;
    
    char* chinese_mu = "無";
    char* chinese_li = "里";
    
    std::cout << chinese_mu << chinese_li << std::endl;
    
    std::cout << tf << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << g << std::endl;
    
    return 0;
}