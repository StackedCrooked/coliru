    #include <iostream>
 
    template<typename T>
    struct DoSomething
    {
        void operator()(T const& v)
        {
           std::cout << "do_something(T)" << std::endl;     
        }
    };
     
    class Foo
    {
        public:
    
        template<typename T>
        void bar(T v)
        {
            DoSomething<T>()(v);
        }
    };
    
    template<>
    struct DoSomething<std::string>
    {
        void operator()(std::string s)
        {
            std::cout << "do_something(std::string)" << std::endl;
        }
    };
    
    template<>
    struct DoSomething<int>
    {
        void operator()(int x)
        {
            std::cout << "do_something(int)" << std::endl;
        }
    };
    
    int main()
    {
        Foo f;
        f.bar(std::string("abc")); // not "abc" because that would be const char*       
        f.bar(123);
    }