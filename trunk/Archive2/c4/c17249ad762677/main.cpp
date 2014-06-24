using max_align_t = double;

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::signals2;

class Dispatcher {
public:
   signal<void ()> signal1;
   signal<void (int)> signal2;
};

class Controller {
public:
    void onSignal1() {
        std::cout << "onSignal1()" << std::endl;
    }

    void onSignal2(int n) {
        std::cout << "onSignal2()" << n << std::endl;
    }
};

int main()
{
    Dispatcher dispatcher;
    Controller controller;
    
    dispatcher.signal1.connect(boost::bind(&Controller::onSignal1, & controller));
    dispatcher.signal1();
    
    dispatcher.signal2.connect(boost::bind(&Controller::onSignal2, & controller, _1));
    dispatcher.signal2(42);
}