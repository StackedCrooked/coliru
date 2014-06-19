#include <iostream>
#include <typeinfo>
#include <memory>

class B {
  public:
    virtual std::string name() { return "B::name"; }
    virtual ~B() {}
};



class A {
  private:
    std::unique_ptr<B> b;

  public:
    std::function<std::unique_ptr<B>()> b_maker;

    A() {
        b_maker = []{ return std::unique_ptr<B>(new B); };
    }

    A(std::function<std::unique_ptr<B>()> func) {
        b_maker = func;
    }

    void createB() {
        b = b_maker();
    }

    void print() {
        std::cout << (b ? b->name() : std::string()) << std::endl;
    }
    ~A() {}
};

class MockedB : public B {
    std::string name() override { return "MockedB::name"; }
};

int main()
{
    A a;
    a.createB();
    a.print();
    
    A a_withmock([]{return std::unique_ptr<B>{new MockedB};});
    a_withmock.createB();
    a_withmock.print();
}