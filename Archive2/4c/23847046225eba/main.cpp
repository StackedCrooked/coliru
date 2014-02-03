#include <iostream>

class Function
{
    struct Base
    {
        virtual void Invoke() = 0;
        virtual Base *clone() const = 0;
        virtual ~Base() {}
    };
    
    template<typename T>
    struct Impl : public Base
    {
        typedef void (T::*MemberPointer)();
        T *obj;
        MemberPointer member;
        
        Impl(T* obj, MemberPointer member) : obj(obj), member(member) {}
        
        void Invoke()
        {
            (obj->*member)();
        }
        
        Base *clone() const
        {
            return new Impl(obj, member);
        }
    };
    
    Base *thunk;
    
public:
    Function()
        : thunk(nullptr)
    {
    }
    
    template<typename T>
    Function(T *obj, void (T::*member)() = &T::operator())
        : thunk(new Impl<T>(obj, member))
    {
    }

    Function(Function const& r)
        : thunk(r.thunk ? r.thunk->clone() : nullptr)
    {
    }

    Function(Function&& r)
        : thunk(r.thunk)
    {
        r.thunk = nullptr;
    }

    Function& operator=(Function&& r)
    {
        if (&r != this)
        {
            thunk = r.thunk;
            r.thunk = nullptr;
        }
        return *this;
    }

    Function& operator=(Function const& r)
    {
        if (&r != this)
        {
            delete thunk;
            thunk = r.thunk->clone();
        }
        return *this;
    }
    
    ~Function()
    {
        delete thunk;
    }
    
    void operator()()
    {
        thunk->Invoke();
    }
};

class Test
{
public:
    void operator()()
    {
        std::cout << "Test::operator() called" << std::endl;
    }
    
    void test()
    {
        std::cout << "Test::test() called" << std::endl;
    }
};

int main()
{
    Test t;
    Function f0(&t, &Test::test);
    Function f1(&t);
    f0();
    f1();
}
