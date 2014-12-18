#include <iostream>
#include <tuple>
#include <functional>

auto& 표준출력 = std::cout;
auto  줄바꿈   = "\n";
using 크기타입 = size_t;
using 위치타입 = std::tuple<크기타입, 크기타입>;

int 한글함수()
{
    표준출력 << "어라 한글 함수가 되네?" << 줄바꿈;
    return 3;
}
int main()
{
    size_t 한글변수 =3 ;
    표준출력 << 한글함수() << std::endl;
    auto 한글람다 = [](auto ㄱ, auto ㄴ)
    {
        표준출력 << (ㄱ <  ㄴ ? " (뒤에 것이 더 큼)" :
                     ㄱ == ㄴ ? " (크기가 같음)" :
                                " (앞의 것이 더 큼)")
        << 줄바꿈;
    };
    
    위치타입 가{3,5}, 나{4,6};
    
    한글람다(한글변수,1);
    한글람다(가, 나);
}

// Output
// 어라 한글 함수가 되네?
// 3
// (앞의 것이 더 큼)
// (뒤에 것이 더 큼)