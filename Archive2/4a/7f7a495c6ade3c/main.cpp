#include <iostream>
#include <tuple>
#include <memory>


struct Test {
    bool a;
    bool b;
    Test() : a(false),b(false) {};
};


template<typename T, bool T::* ... props>
std::shared_ptr<T> activate(std::shared_ptr<T> inst) {
    std::tie((inst.get()->*props)...) = std::make_tuple((props,true)...);
    return inst;
}

int main()
{
    auto t1 = activate<Test,&Test::a>(std::make_shared<Test>());
    auto t2 = activate<Test,&Test::a,&Test::b>(std::make_shared<Test>());
    std::cout << "t1: a = " << t1->a << ", b = " << t1->b << std::endl;
    std::cout << "t2: a = " << t2->a << ", b = " << t2->b << std::endl;
}
