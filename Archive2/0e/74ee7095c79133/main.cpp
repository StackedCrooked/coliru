#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Test
    {
    public:
          void blah() { std::cout << "BLAH!" << std::endl; }
    };

    class Bim
    {
    public:
          void operator()(){ std::cout << "BIM!" << std::endl; }
    };

    void boum() { std::cout << "BOUM!" << std::endl; }

    int mul(int i,int j) {return i*j;}

int main()
{
    // store the member function of an object:
    Test test;  
    std::function< void() > callback = std::bind( boum); //&Test::blah, test );
    callback();

    //std::function< int(int,int) > callback1 
    auto callback1= std::bind( mul,5,_1);
    //callback1();
    cout << callback1(4) << endl;
    // store a callable object (by copy)
    callback = Bim{};
    callback();

    // store the address of a static function
    callback = boum;
    callback();

    // store a copy of a lambda (that is a callable object)
    callback = [&]{ test.blah(); }; // often clearer -and not more expensive- than std::bind()
    callback();
}      
