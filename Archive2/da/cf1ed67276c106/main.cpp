#include <iostream>

class D1;

class D2;

class D3;

class visitor
{
    
public:
    
    virtual void accept(D1& obj) { }
    
    virtual void accept(D2& obj) { }
    
    virtual void accept(D3& obj) { }
    
};

template<typename T>
class static_visitor : public visitor
{
    
public:
    
    virtual void accept(D1& obj) override { return static_cast<T*>(this)->static_accept(obj); }
    
    virtual void accept(D2& obj) override { return static_cast<T*>(this)->static_accept(obj); }
    
    virtual void accept(D3& obj) override { return static_cast<T*>(this)->static_accept(obj); }
    
protected:
    
    template<typename U>
    void static_accept(U&) { }
    
};

class B
{
    
public:
    
    virtual void visit(visitor& v) = 0;
    
};

class D1 : public B
{ 
    
public:
    
    virtual void visit(visitor& v) override 
    {
        v.accept(*this);
    }
    
};

class D2 : public B
{
    
public:
    
    virtual void visit(visitor& v) override 
    {
        v.accept(*this);
    }
        
};

class D3 : public B
{
    
public:
    
    virtual void visit(visitor& v) override 
    {
        v.accept(*this);
    }
        
};

template<typename T>
class delegating_visitor : public static_visitor<delegating_visitor<T>>
{

public:

    delegating_visitor(T&& handler)
        : _handler{std::forward<T>(handler)}
    {
    }

    template<typename U>
    void static_accept(U& obj)
    {
        _handler(obj);
    }

private:

    T _handler;

};

template<class... Fs> struct overloaded;

template<class F1, class... Fs>
struct overloaded<F1, Fs...> : F1, overloaded<Fs...>::type
{
    using type = overloaded;
    overloaded(F1 head, Fs... tail) : F1(head), overloaded<Fs...>::type(tail...) { }
    using F1::operator ();
    using F1::operator = ;
    using overloaded<Fs...>::type::operator ();
    using overloaded<Fs...>::type::operator =;
};

template<class F>
struct overloaded<F> : F
{
    using type = F;
    using F::operator ();
    using F::operator =;
};

template<class... Fs>
typename overloaded<Fs...>::type overload(Fs... fs)
{ 
    return overloaded<Fs...>(fs...); 
}

template<typename... Fs>
delegating_visitor<overloaded<Fs...>> make_delegating_visitor(Fs... fs)
{
    return overload(fs...);
}

class my_visitor : public static_visitor<my_visitor>
{
    
public:
    
    void static_accept(D1& obj)
    {
        std::cout << "D1" << std::endl;
    }
    
    template<typename T>
    void static_accept(T& obj)
    {
        std::cout << "D2 or D3" << std::endl;
    }

};

void foo(B& b)
{
    auto&& v = my_visitor{};
    
    b.visit(v);    
}

int main()
{
    D1 d1;
    foo(d1);
    
    D2 d2;
    foo(d2);
    
    D3 d3;
    foo(d3);    
    
    auto v = make_delegating_visitor(
        [] (D1& obj) { std::cout << "D1" << std::endl; },
        [] (D2& obj) { std::cout << "D2" << std::endl; },
        [] (D3& obj) { std::cout << "D3" << std::endl; });
        
    d1.visit(v);
    
    d2.visit(v);
    
    d3.visit(v);
}