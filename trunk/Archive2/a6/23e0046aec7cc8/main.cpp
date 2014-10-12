#include <memory>
#include <iostream>

struct Animal {
  virtual ~Animal() {}
  virtual void speak() = 0;
};

struct Cat : Animal {
  void speak() override { std::cout << "Meow!\n"; }
};

struct Dog : Animal {
  void speak() override { std::cout << "Woof!\n"; }
};

std::unique_ptr<Animal> createPet(double obedience) {
  if (obedience > 5.0)
    return std::make_unique<Dog>();
  return std::make_unique<Cat>();
}

class House {
 private:
  std::unique_ptr<Animal> pet_;
 public:
  House(std::unique_ptr<Animal> pet) : pet_(std::move(pet)) {}
};

int main() {
  auto pet = createPet(6.0);
  House house(std::move(pet));
}
