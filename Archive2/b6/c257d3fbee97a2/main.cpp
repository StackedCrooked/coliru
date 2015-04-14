namespace ns
{
    template <typename T>
    class Foo
    {
    public:
        Foo();

        ~Foo();

        void DoIt();
    };
}

#include <iostream>

int main() {
    ns::Foo<int> f;
    f.DoIt();
}

namespace ns
{
    template <typename T>
    Foo<T>::Foo() { std::cout << "Being constructed." << std::endl; }

    template <>
    void Foo<int>::DoIt()
    {
        std::cout << "Int" << std::endl;
    }

    template <>
    void Foo<double>::DoIt()
    {
        std::cout << "Double" << std::endl;
    }

    template class Foo<int>;
    template class Foo<double>;
}