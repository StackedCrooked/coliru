#include <iostream>

class car {
  private:
    int mileage;
  public:
    car(int); // Constructor
    int odometer();
};

car::car(int m) {
  mileage = m;
}

int car::odometer() {
  return mileage;
}

int main(void) {
  car ford(10000), honda(20000);

  std::cout<<ford.odometer(); //Returns 20000, since honda constructor overwrites private variable 'mileage'
}