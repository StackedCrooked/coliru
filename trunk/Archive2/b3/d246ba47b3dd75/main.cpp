#include <unordered_map>
#include <iostream>

class Item {
 private:
  std::string type_;  // "intrinsic" state
 public:
  Item(const std::string &type) : type_(type) {} 
  void someOperation(std::string color, double speed) {  // pass in "extrinsic" state
  
    // do something using both "intrinsic" and "extrinsic" state...
    std::cout << color << " " << type_ << " moving at " << speed << "mph\n";
  }
};

class AnimalSim {
 private:
  std::unordered_map<int, std::string> duck_colors_;   // Store extrinsic
  std::unordered_map<int, std::string> sheep_colors_;  // state separately
  std::unordered_map<int, double>      duck_speeds_;   // in a more
  std::unordered_map<int, double>      sheep_speeds_;  // efficent way.
 public:
  void run();
  std::string getDuckColor(int duck_index) const;
  std::string getSheepColor(int sheep_index) const;
  double      getDuckSpeed(int duck_index) const;
  double      getSheepSpeed(int sheep_index) const;
};

void
AnimalSim::run() {
  auto duck = Item{"duck"};    // Create `Flyweight` objects that can be shared. This
  auto sheep = Item{"sheep"};  // should probably be done by a factory with a cache.

  // Create duck 0
  duck_colors_.emplace(0, "red");
  duck_speeds_.emplace(0, 150.0);
  
  // Create duck 1 - has no speed
  duck_colors_.emplace(0, "green");
  size_t num_ducks = 2;

  // Create sheep 0 - has no color
  sheep_speeds_.emplace(0, 100.0);
  size_t num_sheep = 1;

  // Do something with all the ducks
  for(size_t i = 0; i != num_ducks; ++i)
    duck.someOperation(getDuckColor(i), getDuckSpeed(i));
    
  // Do something with all the sheep
  for(size_t i = 0; i != num_sheep; ++i)
    sheep.someOperation(getSheepColor(i), getSheepSpeed(i));    
}

std::string
AnimalSim::getDuckColor(int duck_index) const {
  auto color_itr = duck_colors_.find(duck_index);
  return color_itr != duck_colors_.end() ? color_itr->second : "black"; 
}

std::string
AnimalSim::getSheepColor(int sheep_index) const {
  auto color_itr = sheep_colors_.find(sheep_index);
  return color_itr != sheep_colors_.end() ? color_itr->second : "white"; 
}

double
AnimalSim::getDuckSpeed(int duck_index) const {
  auto speed_itr = duck_speeds_.find(duck_index);
  return speed_itr != duck_speeds_.end() ? speed_itr->second : 0.0; 
}

double
AnimalSim::getSheepSpeed(int sheep_index) const {
  auto speed_itr = sheep_speeds_.find(sheep_index);
  return speed_itr != sheep_speeds_.end() ? speed_itr->second : 0.0; 
}

int main() {
  AnimalSim animal_sim;
  animal_sim.run();
}
