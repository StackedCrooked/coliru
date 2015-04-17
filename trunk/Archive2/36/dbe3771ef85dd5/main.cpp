#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

class zoo;

class foo
{
    private:
    foo(foo const&);

    public:
    foo(){}

    void abc()
    {
        std::cout << "abc" << std::endl;
    }
};


int main()
{
    foo f;
    
    {
        boost::thread testThread(boost::bind(&foo::abc, &f));
    }
    {
        boost::thread testThread(&foo::abc, &f);
    }
    {
        boost::thread testThread(&foo::abc, boost::ref(f));
    }

    return 0;
}
