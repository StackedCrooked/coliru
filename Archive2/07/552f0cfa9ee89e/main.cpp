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
using Function = void (*)(Type);

template
    <
        typename Type,
        Function<Type> function = PrintInteger
    >
void CallFunction
    (
        Type&& value
    )
{
    function(std::forward<Type>(value));
}

int main()
{
    CallFunction(42);
    CallFunction<const std::string&, PrintString>("Hello!");
}