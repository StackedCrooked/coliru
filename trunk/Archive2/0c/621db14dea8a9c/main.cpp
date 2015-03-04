    #include <iostream>
    
    template<class T>
    class A
    {
    public:
        void foo(int){ std::cout << "foo" << std::endl; };
        template<class V> void foo(V v){ std::cout << "foo" << std::endl; }
    };
    
    A<int> a;
    int main(){ a.foo(3); } //Here is the error.