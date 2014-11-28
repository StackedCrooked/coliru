#include <iostream>
#include <memory>

class test1{
public:
    std::string s_;
    test1(std::string s):s_(s){};
};
class testu{
public:
    std::unique_ptr<test1> us_;
    testu(std::unique_ptr<test1> us):us_(std::move(us)){};
};

template <int i>
class testt {
public:
    std::unique_ptr<test1> us_;
    testt<i>(std::unique_ptr<test1> us):us_(std::move(us)){};
};

template class testt<0>;

int main() {
    //without template
    std::unique_ptr<test1> us(new test1("test"));
    testu* t1=new testu(move(us));
    std::cout<<t1->us_->s_<<"\n";

    //with template the constructor fails!
    std::unique_ptr<test1> ust(new test1("test"));
    testt<0>* t2=new testt<0>(std::move(ust));
    std::cout<<t2->us_->s_<<"\n";  //crash!
    return 0;
}
