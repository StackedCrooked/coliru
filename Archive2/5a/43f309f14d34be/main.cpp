#include <functional>

template<class T = int> class Test {
    typedef std::function<void ()> Foo;
    
    public:
        Test(Foo const& foo = [] () {}){ // this is line 24
    }
    
};

int main()
{
    Test<> x;
}