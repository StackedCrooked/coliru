#include <type_traits>
#include <iostream>

class KeyEvent
{
public: enum TypeFlags {KEYFLAG1=1, KEYFLAG2=2, KEYFLAG3=4};
};

class MouseButtonEvent
{
public: enum TypeFlags {MOUSEFLAG1=1, MOUSEFLAG2=2, MOUSEFLAG3=4};
};

template<typename EC>
auto operator|(EC a, EC b) -> typename std::enable_if<std::is_same<EC, KeyEvent::TypeFlags>::value || std::is_same<EC, MouseButtonEvent::TypeFlags>::value, EC>::type
{
    std::cout << "operator|(EC a, EC b)" << std::endl;
    return static_cast<EC>(static_cast<int>(a)|static_cast<int>(b));
}

void DoSomething(KeyEvent::TypeFlags t) {std::cout << t << std::endl;}

int main()
{
    DoSomething(KeyEvent::KEYFLAG1 | KeyEvent::KEYFLAG2);
    return 0;
}
