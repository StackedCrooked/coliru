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
void print_fptr_types(R (*fptr)(Args...))
{
    std::cout << type_str<R>() << " (*)(" << arg_types_str<Args...>() << ")" << std::endl;
}


template<class T, class R, class... Args>
void print_memfptr_types(R (T::*memfptr)(Args...))
{
    std::cout << type_str<R>() << " (" << type_str<T>() << "*)(" << arg_types_str<Args...>() << ")" << std::endl;
}

template<class T>
void print_fnc_obj_types(const T&)
{
    print_memfptr_types(&T::operator());
}

struct FncObj
{
    int operator()(int, char)
    {
        return 0;
    }
};

template<>
string type_str<FncObj>() { return "FncObj"; }

int main()
{
    int (*fptr)(char, int);
    print_fptr_types(fptr);

    FncObj fnc_obj;
    print_fnc_obj_types(fnc_obj);
}