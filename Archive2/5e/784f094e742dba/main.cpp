#include <iostream>
#include <functional>

using namespace std;

double fcn_mod(const double &phit){
    return 1.2+phit;
}

class Object{
    public:
        Object() : fcn_ptr(std::bind(&Object::fcn_default, this, std::placeholders::_1))
        {}
        std::function<double(double const&)> fcn_ptr;

    private:
        double fcn_default(const double &phit){
            return 3.2+phit;
        }
};


int main(){

    Object test1,test2;

    cout << (test1.fcn_ptr)(2) << endl;

    test2.fcn_ptr = &fcn_mod;
    cout << (test2.fcn_ptr)(2) << endl;

    cout << "test" << endl;
}
