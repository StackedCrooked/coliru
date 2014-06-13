#include <iostream>
#include <functional>

using namespace std;

double fcn_mod(const double &phit){
  return 1.2 + phit;
}

class Object{
public:
  double(*fcn)(double const&);
  Object() {
    fcn = &Object::fcn_default;
  }

private:
  static double fcn_default(const double &phit){
    return 3.2 + phit;
  }
};

int main() {
  Object test1, test2;
  cout << test1.fcn(2.0) << endl; // can not compile here
  test2.fcn = &fcn_mod;
  cout << test2.fcn(2.0) << endl; // and here
  cout << "test" << endl;
}
