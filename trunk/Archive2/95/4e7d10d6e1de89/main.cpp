template<typename Self>
class A
{
public:
    void foo()
    {
        Self s;
        s._method(s); // ERROR, because _method is protected
    }
protected:
    virtual void _method(const Self& b) = 0;
};

class B : public A<B>
{
    friend class A<B>;
protected:
    void _method(const B& b) {}
};

int main()
{
    B b;
    b.foo();
}