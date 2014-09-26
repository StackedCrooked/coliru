#include <boost/signals2.hpp>
#include <string>
#include <iostream>

class Something
{
    public:
        int x;
        bool operator()(std::string str)
        {
            std::cout << str << x << std::endl;
            return true;
        }
};

int main()
{
    boost::signals2::signal<bool (std::string)> sig;
    Something something;
    something.x = 3;

    Something somethingElse;
    somethingElse.x = 3;

    sig.connect(something);
    sig.connect(boost::ref(somethingElse)); 

    something.x = 2;
    somethingElse.x = 2;

    sig("x is : ");
}
