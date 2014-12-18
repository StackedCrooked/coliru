
#include <iostream>

int 한글함수()
{
    std::cout << "어라 한글 함수가 되네?" << std::endl;
    return 3;
}
int main()
{
    size_t 한글변수 =3;
    std::cout << 한글함수() << std::endl;
    auto 한글람다 = [](auto 에이, auto 비이)
    {
        std::cout << (에이 < 비이  ? "뒤에 것이 더 큼" : "뒤의 것이 더 크지 않음") << std::endl;
    };
    
    한글람다(한글변수,1);
    //std::cout << "hahaha " << a << std::endl;
}