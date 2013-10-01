#include <iostream>

//+ example 1: a std::tuple-like class
    template<class... T>
    struct X
    {
        void print();
    };
    
    template<class T, class... Ts>
    struct X<T, Ts...>
    : X<Ts...>
    {
        using base = X<Ts...>;
        using base::print;
        
        T member;
        void print(T) { std::cout << member << std::endl; }
        
        X(T p, Ts... ps)
        : base(ps...), member(p)
        {}
    };
    
    void example1()
    {
        X<int, double, char> x(42, 2.5, 'c');
        x.print(int{});
        x.print(char{});
        x.print(double{});
    }
//- end of example 1


//+ example 2:
    template<class T>
    struct logger_extension : T
    {
        virtual int test() override
        {
            std::cout << "some logging" << std::endl;
            // call base class version
            return T::test();
        }
    };
    
    struct Base
    {
        virtual int test() = 0;
    };
    struct Derived : Base
    {
        virtual int test() override
        {
            return 42;
        }
    };
    
    void example2()
    {
        Base* p = new logger_extension<Derived>;
        auto result = p->test();
        std::cout << "the result is: " << result << std::endl;
    }
//- end of example 2

int main()
{
    std::cout << "example 1:" << std::endl;
    example1();
    
    std::cout << "\n\n\n\n";
    
    std::cout << "example 2:" << std::endl;
    example2();
}