#include<boost/range/adaptors.hpp>
#include<memory>
#include<vector>

class Car {
  public:
    void Drive() {}
    void DisplayMileage() const {}
};

int main() {
    std::vector<std::shared_ptr<Car>> cars;
    
    for(int i = 0; i < 10; ++i)
      cars.push_back(std::make_shared<Car>());
    
    for(auto const& car : cars | boost::adaptors::indirected) {
      car.DisplayMileage();
      car.Drive();
    }
}
