#include <cstdio>
#include <functional>
#include <string>
#include <memory>

using namespace std;

class Foo {
public:
    Foo(): m_str("foo") { }

    void f1(string s1, string s2, const unique_ptr<Foo> &p)
        {
            printf("1: %s %s %s\n", s1.c_str(), s2.c_str(), p->str());
        }

    void f2(string s1, string s2, Foo* p)
        {
            printf("2: %s %s %s\n", s1.c_str(), s2.c_str(), p->str());
        }

    const char* str() const { return m_str.c_str(); }

private:
    string m_str;
};

int main()
{
    string arg1 = "arg1";
    string arg2 = "arg2";
    Foo s;
    unique_ptr<Foo> ptr(new Foo);


    function<void()> f(bind(&Foo::f1, &s, arg1, arg2, std::ref(ptr)));
    //function<void()> f(bind(&Foo::f2, &s, arg1, arg2, ptr.release()));

    f();
}