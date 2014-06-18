#include <iostream>
#include <functional>

using namespace std;


class Parent{
    public:
        Parent() {}

};


class Child1 : public Parent{
    public:
        Child1() : fcn_ptr(std::bind(&Child1::fcn_default, this, std::placeholders::_1)) {}
        std::function<double(double const&)> fcn_ptr;
        
    private:
        double fcn_default(const double &phit){
            return 3.2+phit;
        }
};

class Child2 : public Parent{
    public:
        Child2() : fcn_ptr(std::bind(&Child2::fcn_default, this, std::placeholders::_1)) {}
        std::function<double(double const&)> fcn_ptr;
        double aaa = 0.2;
        
    private:
        double fcn_default(const double &phit){
            return 3.2+phit + aaa*0.1;
        }
};



double fcn_mod1(const double &phit){
    return 1.2+phit;
}

double fcn_mod2(const double &phit){
    return 1.2+phit;
}

int main(){

    Child1 test11,test12;

    cout << (test11.fcn_ptr)(2) << endl;

    test12.fcn_ptr = &fcn_mod1;
    cout << (test12.fcn_ptr)(2) << endl;

    cout << "test" << endl;
}
