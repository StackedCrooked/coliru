#include<iostream>
#include<boost/lexical_cast.hpp>
int main(){
    int a = boost::lexical_cast<int>("123456");
    std::cout << a <<std::endl;
    return 0;
}