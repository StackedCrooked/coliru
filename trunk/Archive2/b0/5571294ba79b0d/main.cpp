#include <iostream>
#include <functional>
#include <vector>
#include <string>  

template<typename F> class Foo
{
public:
    Foo(int a) : wombat(a) {};
    ~Foo() {}

    bool get_result() { return result; }

protected:
    template<typename A> bool do_something(std::string& s, A& a, A b, A c);

    bool result;
    int wombat;
};

template<typename F> template<typename A> bool Foo<F>::do_something(std::string& s, A& a, A b, A c)
{
    if ( a > b && a < c)
    {
        std::cout << s << std::endl;
        return true;
    }
    return false;
}

struct Tim
{
    int age;
    float weight;
};

class Bar : public Foo<Tim>
{
public:
    Bar(int a) : Foo<Tim>(a) {};
    ~Bar() {};

    void do_somethings();
};

void Bar::do_somethings()
{
     Tim t;
     t.age = 15;

     std::vector<std::function<bool(std::string&)> > my_list = {
         std::bind(&Bar::do_something<int>, this, std::placeholders::_1, std::ref(t.age), 10, 100)
     };   // Error shows up here

     std::string s("howdy");
     for( auto v : my_list) { result = v(s); }
}

int main(int argc, char** argv)
{
    Bar b(200);
    b.do_somethings();
    return 0;
}
