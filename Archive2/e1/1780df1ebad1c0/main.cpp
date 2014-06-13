#include <boost/operators.hpp>
#include <iostream>

using std::cout;
using std::endl;

using namespace std;

double fcn_mod(const double &phit){
    return 1.2+phit;
}

class Object{
    public:
        Object() : fcn_ptr(&Object::fcn_default)
        {}
        double (Object::*fcn_ptr)(const double &) = NULL;

    private:
        double fcn_default(const double &phit){
            return 3.2+phit;
        }
};


int main(){

    Object test1,test2;

    cout << (test1.*(test1.fcn_ptr))(2) << endl; // can not compile here

//    test2.fcn_ptr = &fcn_mod;
//    cout << (test2.*fcn_ptr)(2) << endl; // and here
//
//    cout << "test" << endl;
}
