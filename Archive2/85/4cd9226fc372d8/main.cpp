#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdlib.h> 
#include <time.h>

class Sink {
private:
  int dishCount;
  
public:
  Sink() {
    dishCount = 0;
  }
  
  bool hasDish() {
    return (dishCount >= 1);
  }
  
  void addDish() {
    dishCount++;
  }
  
  void removeDish() {
    dishCount--;
  }
  
  int getDishCount() {
    return dishCount;
  }
};

std::string getTime() {
  std::stringstream time;
  std::time_t t = std::time(nullptr);
  time << std::put_time(std::localtime(&t), "%H:%M");
  return time.str();
}

class Food {
private:
  Sink kitchenSink;

public:
  Food(Sink &aSink) {
    this->kitchenSink = aSink;
  }
  
  void cook() {
    for (int i = 0; i <= 4; i++)
      this->kitchenSink.addDish(); //Average dishes used to cook food
    //Stub to be implemented at cook time
  }
};

class Person {
private:
  Sink kitchenSink;

public:
  Person(Sink &aSink) {
    this->kitchenSink = aSink;
  }
  
  bool usedDish() {
    srand (time(NULL));
    return rand() % 2;
    //randomly returns true or false
    //Stub return value
  }
  
  bool doingDishes() {
    srand (time(NULL));
    return rand() % 2;
    //randomly returns true or false
    //Stub return value
  }
  
  void finishWithDish(int dishCount, bool location) { 
    //location == true -> dishwasher, location == false -> sink
    if (!location)
      for (int i = 0; i <= dishCount; i++)
        this->kitchenSink.addDish();
  }
  
  void doAllDishes() {
    for (int i = 0; i <= this->kitchenSink.getDishCount(); i++)
        this->kitchenSink.addDish();
  }
};

int main() {
  srand (time(NULL));
  Sink kitchenSink = Sink();
  Person resident = Person(kitchenSink);
  
  while (1) {
    if (getTime() == "16:30") {
      if (kitchenSink.hasDish()) {
        std::cout << "Will not cook with dishes in sink" << std::endl;
        continue;
      }
      else {
        std::cout << "Food cooked because sink is clear" << std::endl;
        Food(kitchenSink).cook();
      }
    }
    else if (resident.usedDish())
      resident.finishWithDish(rand() % 4, rand() % 2); //0-4 dishes used, and either in the sink or dishwasher
    else if (resident.doingDishes())
      resident.doAllDishes();
    else continue;
  }
}