#include <iostream>
 
template <typename T>
bool gun(T val)
{
    std::cout<<val<<std::endl;
    return true;
}
 
template <typename ...T>
void fun(T... val)
{
    auto init={gun<T>(val)...};
    (void)init;
}
 
int main(int argc, char *argv[])
{
    fun(1,2,3,4.0,5.0f,'6');
}