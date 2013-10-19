#include <iostream>

class sayhello {
protected:
    void saySomething(void) {
        std::cout<<"Hello!"<<std::endl;
    }
};

template<typename T>
class talk : virtual T {
protected:
    void doSomething(void) {
        T::saySomething();
    }
};

template<typename T>
class host1 : virtual T {
public:
    void hostAction(void) {
        T::doSomething();
    }
};

template<typename T, typename L>
class host2 : virtual T, virtual L {
public:
    void hostAction(void) {
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
