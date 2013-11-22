#include <iostream>

using namespace std;

class Bar
{
  public:
    struct BarCallbackIF
    {
        virtual void barCallback()
        { }
    };
    
    Bar(BarCallbackIF &callback);
    virtual ~Bar();
    
  protected:
    Bar(const Bar &);
    Bar &operator =(const Bar &);
  private:
    struct impl;
    impl* p_;
};

struct Bar::impl
{
    BarCallbackIF &callback_;
    
    impl(BarCallbackIF &callback) : callback_(callback)
    {
      cout << "Bar::impl constructor" << endl;
      callback_.barCallback();
    }
};

Bar::Bar(BarCallbackIF &callback)
{
  p_ = new impl(callback);
}

Bar::~Bar()
{
  delete p_;
}

template <typename T>
class Foo
{
  public:
    struct Args;
    
    Foo(const Args &args);
    virtual ~Foo();
  
  protected:
    Foo(const Foo &);
    Foo &operator =(const Foo &);
  private:
    struct impl;
    impl *p_;
};

template <>
struct Foo<int>::Args
{
    int a_;
    int b_;
    
    Args(int a, int b) : a_(a), b_(b)
    { }
    
    friend std::ostream &operator <<(std::ostream &s, const Args &args)
    {
      s << args.a_ << "," << args.b_;
      return s;
    }
};

template <>
struct Foo<int>::impl : public Foo<int>::Args, public Bar::BarCallbackIF
{
    impl(const Args &args) : Args(args)
    {
      cout << "Foo<int>::impl constructor; args=" << args << endl;
      cout << "Foo<int>::impl constructor; this=" << *this << endl;
      Bar bar(*this);
    }
    
    void barCallback()
    {
      cout << "In bar callback in Foo<int>::impl=" << *this << endl;
    }
    
    virtual ~impl()
    { }
};

template <>
Foo<int>::Foo(const Args &args)
{
  p_ = new impl(args);
}

template <>
Foo<int>::~Foo()
{
  delete p_;
}

class Test
{
  public:
    void run() 
    {
      cout << "Task starting..." << endl;
      Foo<int>::Args args(1, 2);
      Foo<int> int_foo(args);
      cout << "Task ending..." << endl;
    }
};

int main()
{
    Test test;
    test.run();
}
