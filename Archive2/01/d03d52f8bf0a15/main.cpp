class Foo
{
public:
    virtual void doSomething() = 0;
    virtual void* getBar() = 0;
protected:
    Foo(){};
};

class Bar : public Foo
{
public:    
    void doSomething() {}
    void* getBar() { return nullptr; }
};

int main()
{
    Bar b;
    return 0;
}