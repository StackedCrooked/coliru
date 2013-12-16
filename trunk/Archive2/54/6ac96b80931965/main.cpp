#include <utility>
#include <iostream>
#include <cstdint>
 
struct Default {
    int foo() const {return 1;}
};
 
struct NonDefault {
    NonDefault(const NonDefault&) {}
    std::int32_t foo() const {return 1;}
};
 
int main()
{
    decltype(Default().foo()) n1 = 1; // int n1
//  decltype(NonDefault().foo()) n2 = n1; // will not compile
    decltype(std::declval<NonDefault>().foo()) n2 = n1; // int n2
    std::cout << "n2 = " << n2 << '\n';
    decltype(Default().foo()) arr[] = {1, 2};
    std::cout<<"arr[0]: "<<arr[0]<<", arr[1]: "<<arr[1]<<std::endl;
    wchar_t const * greetingsMsg = L"Hello!";
    std::wcout<<greetingsMsg<<std::endl;
    
}