#include <iostream>

// a specific kind of oracle
class h2g2_oracle {
  protected:
    static int _answer;

  public:
    static constexpr const int& answer = _answer; // public alias for reading
};
int h2g2_oracle::_answer = 42;

// some class template using a specific kind of oracle
template<typename oracle>
struct forecast {
  // try to define an own alias
  //static constexpr const int& answer = oracle::answer; // works
  static constexpr const int& answer = h2g2_oracle::answer; // ERROR; WHY?
};

// specialized version for the h2g2_oracle
template<>
struct forecast<h2g2_oracle> {
  // also define the own alias
  static constexpr const int& answer = h2g2_oracle::answer; // works
};

int main() {
  static constexpr const int& answer = h2g2_oracle::answer; // works
  std::cout << answer << std::endl;

  std::cout << forecast<h2g2_oracle>::answer << std::endl;
  return 0;
}