#include <iostream>
#include <vector>

struct Face {
  Face() {}
  Face(Face const &other) { std::cout << "Copy constructor evoked!" << std::endl; }
  Face(Face &&other) { std::cout << "Move constructor evoked!" << std::endl; }
  Face& operator=(Face const &rhs) {
    std::cout << "Assignment operator evoked" << std::endl;
    return *this;
  }
  Face& operator=(Face &&rhs) {
    std::cout << "Move assignment operator evoked" << std::endl;
    return *this;
  }
};

auto main() ->int {
  std::vector<Face> faces;
  for (std::size_t i(0); i < 1; ++i) {
    Face f;
    faces.push_back(f);
  }

  return 0;
}