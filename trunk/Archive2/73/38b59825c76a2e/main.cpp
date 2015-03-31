//Title of this code
//clang 3.4

#include <iostream>


struct Test;

void closeMe(Test*)
{
    std::cout << __FUNCTION__ << "\n";
}


struct Deleter
{
    template<typename T>
    void operator()(T* t) const
    {
        delete t; // default.
    }
};


template<typename T, typename Del = Deleter>
class Wrapper
{
        public:
            Wrapper(T* ptr = nullptr, Del del = Deleter())
                : m_ptr(ptr)
                , m_del(del)
                { }
            ~Wrapper()
            {
                m_del(m_ptr);
            }
    
    private:
    T* m_ptr;
    Del m_del;
};

struct Test
{
    ~Test() { std::cout << __FUNCTION__ << "\n"; }
};


int main()
{
    {
        Wrapper<Test> w (new Test());
    }
    {
        typedef void(*close)(Test*);
        Wrapper<Test, close> (new Test(), closeMe);
    }
}