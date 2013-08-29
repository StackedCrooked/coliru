#include <string>
#include <iostream>

template <typename T>
struct Foo1{
};

template <typename T>
struct Foo2{
};

namespace ExampleSpecializations{
        template <typename T>
                std::string name(const T& ){
                        return "generic";
                }   
        template <>
                std::string name(const int&){
                        return "int";
                }   
        template <typename T>
                std::string name(const Foo1<T>& ){
                        std::string  ret = "Foo1<" + ExampleSpecializations::name<T>(T()) + ">";
                        return ret;
                }   
        template <typename T>
                std::string name(const Foo2<T>& ){
                        std::string  ret = "Foo2<" + ExampleSpecializations::name<T>(T()) + ">";
                        return ret;
                }   
}

template <typename Arg>
struct Bar {
        std::string name()
        {   
                std::string ret = std::string("Bar<") + ExampleSpecializations::name<>(Arg()) + std::string(">");
                return ret; 
        }           
};          

int main()
{
        Bar<int> a;
        std::cout << a.name() << std::endl;
        Bar<char> b;  
        std::cout << b.name() << std::endl;

        Foo1<int> f1i;
        std::cout << ExampleSpecializations::name(f1i) << std::endl;

        Foo2<int> f2i;
        std::cout << ExampleSpecializations::name(f2i) << std::endl;

        Bar<Foo2<int> > bf2i;
        std::cout << bf2i.name() << std::endl;
} 