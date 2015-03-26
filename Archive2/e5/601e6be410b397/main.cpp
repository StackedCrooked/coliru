#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int fruits = 6;

class fruit {
public:
  float weight, price;
  string name;
  fruit(float a, float b, string c) {
    weight = a;
    price = b;
    name = c;
  }
};

int ask(vector<fruit> const &fruit_array) {
  cout << "What would you like to buy? ";
  string s;
  getline(cin, s);
  if (s == "select") {
    return -1;
  }
  for (int i = 0; i < fruit_array.size(); i++) {
    if (s == fruit_array[i].name) {
      return i;
    }
  }
  return -1;
}

int main() {
  const vector<fruit> fruit_array = {
      fruit(.5, 1, "banana"), fruit(1.5, 3, "pineapple"),
      fruit(2, 2.5, "coconut"), fruit(1, 1.5, "papaya"),
      fruit(4, 2, "watermelon")};

  int selected_id = ask(fruit_array);

  if (selected_id > 0) {
    std::cout << "You selected " << fruit_array[selected_id].name
              << ", which weighs " << fruit_array[selected_id].weight
              << " and costs " << fruit_array[selected_id].price << '\n';
  } else {
    std::cout << "I don't recognize your selection.\n";
  }
}

