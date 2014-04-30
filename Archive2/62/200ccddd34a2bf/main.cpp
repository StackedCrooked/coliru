#include <iostream>

class Person {
public:
   int age;

   Person(int a) {
      this->age = a;
   }

   Person(const Person& person) {
      std::cout << "hello\n";
   }
};

int main() {
   Person timmy(10);
   Person sally(15);

   Person timmy_clone = timmy;
   std::cout << "timmy age " << timmy.age << " " << "sally age " << sally.age << " " <<   "timmy_clone age " << timmy_clone.age << std::endl;
   timmy.age = 23;
   std::cout << "timmy age " << timmy.age << " " << "sally age " << sally.age << " " << "timmy_clone age " << timmy_clone.age << std::endl;

   std::cout << &timmy << std::endl;
   std::cout << &timmy_clone << std::endl;

}