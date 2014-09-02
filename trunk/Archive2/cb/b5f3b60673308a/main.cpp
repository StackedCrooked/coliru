#include<iostream>

using namespace std;

class Object
{
public:
};

template<typename T>
class SmartPtr
{
public:

    template<typename Y>
    explicit SmartPtr(Y* p) { p_ = p; }

    SmartPtr(std::nullptr_t) { p_ = nullptr; }

private:
    T* p_;
};

class Variant
{
public:
    Variant(bool b) : _b(b) { }

private:
    bool _b;
};

class Obj
{
public:
    void test(SmartPtr<Object> /*p*/) { cout << "smartptr version!" << endl; }
    void test(Variant /*v*/) { cout << "variant version!" << endl; }
};

int main(int argc, const char *argv[])
{
    Obj o;
    o.test(nullptr); // calls SmartPtr version
    o.test(true); // calls Variant version
    o.test(false); // -> compiler error: ambiguous call to overloaded function

    return 0;
}