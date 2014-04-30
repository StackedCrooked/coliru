#include <functional>
#include <iostream>

class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc) { return 0;}

class GameCharacter {
public:
  typedef std::function<int (const GameCharacter&)> HealthCalcFunc;
  
  explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
  int healthValue() const { return healthFunc(*this); }
  
  private:
    HealthCalcFunc healthFunc;
};

int main() {
  GameCharacter gc;
  int health = gc.healthValue();
  std::cout << health << std::endl;
}
