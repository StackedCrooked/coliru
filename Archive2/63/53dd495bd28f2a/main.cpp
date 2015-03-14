#include <iostream>
#include <string>

using std::string;

template<class T>
string type_str();

template<>
string type_str<int>() { return "int"; }

template<>
string type_str<char>() { return "char"; }

string arg_types_str()
{
    return "";
}

template<class T>
string arg_types_str()
{
    return type_str<T>();
}

template<class T, class U, class... Args>
string arg_types_str()
{
    return type_str<T>() + ", " + arg_types_str<U, Args...>();
}

template<class R, class... Args>
void print_fptr_type(R (*fptr)(Args...))
{
    std::cout << type_str<R>() << " (*)(" << arg_types_str<Args...>() << ")" << std::endl;
}

int main()
{
    int (*fptr)(char, int);
    print_fptr_type(fptr);
}