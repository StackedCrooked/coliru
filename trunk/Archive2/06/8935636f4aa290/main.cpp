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
    auto init={gun(val)...};
    (void)init; //silence "unused variable" warning ;-)
}
 
int main(int argc, char *argv[])
{
    fun(1,2,3,4.0,5.0f,'6');
}