#include <iostream>
#include <array>


struct Functor // only supports signature `void()`
{
    template<typename F>
    Functor(F&& f) : base(new (&buf[0]) Fun<F>(std::forward<F>(f)))
    {        
        static_assert(sizeof(f) < sizeof(buf), "");
        static_assert(std::alignment_of<F>::value < std::alignment_of<SmallBuffer>::value, "");
    }
    
    Functor(Functor&& rhs) : buf(rhs.buf), base(rhs.base)
    {
        rhs.base = nullptr;
    }
    
    Functor& operator=(Functor&& rhs)
    {
        buf = rhs.buf;
        base = rhs.base;
        rhs.base = nullptr;
        return *this;
    }
    
    Functor(const Functor&) = delete;
    Functor& operator=(const Functor&) = delete;
    
    ~Functor()
    {
        if (base)
        {
            base->Base::~Base();
        }
    }
    
    void operator()() const
    {
        base->call();
    }
    
private:
    struct Base
    {
        virtual ~Base() {}
        virtual void call() const = 0;
    };
    
    template<typename F>
    struct Fun : Base, F
    {
        Fun(F&& f) : Base(), F(std::forward<F>(f)) {}
        
        void call() const override final
        {
            this->F::operator()();
        }
    };
    
    typedef std::array<long, 128> SmallBuffer; // use long to maximize alignment
    SmallBuffer buf;    
    Base* base;
};

int main()
{
    int a = 1;
    Functor f([=]{ std::cout << a << std::endl; });
    f();    
    
    
    // test destructor
    struct Test
    {
        ~Test()
        {
            std::cout << "~Test" << std::endl;
        }
    };
    
    Test t;
    Functor f2([=]{ std::cout << (&t) << std::endl; });
    f2();
    
    Functor f3 = std::move(f2);
    f3();
}

