#include <type_traits>
#include <new>
#include <utility>


struct Functor // only supports signature `void()`
{
    template<typename F>
    Functor(F&& f) : base(new (&buf) Fun<F>(std::forward<F>(f)))
    {        
        static_assert(sizeof(f) <= sizeof(buf), "");
        static_assert(std::alignment_of<F>::value <= std::alignment_of<SmallBuffer>::value, "");
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
    
    struct SmallBuffer
    {
        char data[128];
    };
    alignas(128) SmallBuffer buf;    
    Base* base;
};

int main()
{
    Functor([&]{})();
}

