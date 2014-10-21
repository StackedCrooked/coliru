class A
{
    public: virtual void foo() const {  }
};
class B : public A
{
    public: virtual void foo() {  }
};

