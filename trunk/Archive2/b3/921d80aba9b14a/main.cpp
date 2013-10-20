#include <iostream>

class sayhello {
public:
    static void saySomething(void) {
        std::cout << "sayhello:: ";
        std::cout<<"Hello!"<<std::endl;
    }
};

template<typename T>
class talk /*: virtual T*/ {
public:
    static void doSomething(void) {
        std::cout << "talk:: ";
        T::saySomething();
    }
};

template<typename T>
class host1 /*: virtual T*/ {
public:
    void hostAction(void) {
        std::cout << "host1::";
        T::doSomething();
    }
};

template<typename T, typename L>
class host2 /*: virtual T, virtual L*/ {
public:
    void hostAction(void) {
        std::cout << "host2::";
        T::doSomething();
        L::saySomething();
    }
};

int main() {
    host1<talk<sayhello> > HOST1;
    HOST1.hostAction(); // ok that works

    host2<talk<sayhello>,sayhello> HOST2;
    HOST2.hostAction(); // error, ambiguity!

    return 0;
}
