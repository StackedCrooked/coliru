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
}