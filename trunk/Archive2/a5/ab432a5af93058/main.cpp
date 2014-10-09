#include <iostream>
#include <string>

void PrintInteger(int i)
{
    std::cout << "Integer: " << i << std::endl;
}

void PrintString(const std::string& s)
{
    std::cout << "String: " << s << std::endl;
}

template <typename Type>
struct Function
{
    typedef void (*type)(Type);
};

template
    <
        typename Type,
        typename Function<Type>::type function
    >
void CallFunction
    (
        Type value
    )
{
    function(value);
}

int main()
{
    CallFunction<int, PrintInteger>(42);
    CallFunction<const std::string&, PrintString>("Hello!");
}
