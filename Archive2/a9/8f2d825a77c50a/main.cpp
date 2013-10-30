#include <functional>

using namespace std;

template<typename T> struct identity { using type = T; };

template<class CharType>
void f1(CharType* str, typename identity<function<bool(CharType)>>::type fn_filter)
{}

template<class CharType>
void f2(CharType* str, function<bool(const char)> fn_filter)
{}

void f3(const char* str, char c)
{
    auto fn_filter = [=](char e) -> bool 
    {
        return e == c; 
    };

    f1(str, fn_filter); // error C2784
    f2(str, fn_filter); // OK
}

int main()
{
    f3("ok", 'k');
}
