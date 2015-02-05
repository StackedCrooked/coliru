#include <iostream>

// Base case for Select when all variadic arguments are exhausted.
template <typename TRight>
static constexpr inline TRight Select(TRight default_value) {
  return default_value;
}

template <typename TLeft, typename TRight, typename ... TRest>
static constexpr inline TRight Select(TLeft condition,
                                      TRight value,
                                      TRest ... rest,
                                      TRight default_value) {
  return condition ? value : Select(rest ..., default_value);
}

  
#define EXPECT_EQ(a, b) std::cout << "a: " << a << ", b: " << b << std::endl;

int main() {

  EXPECT_EQ(0, Select(0));
  EXPECT_EQ(1, Select(true, 1, 0));
  EXPECT_EQ(2, Select(true, 2, true, 0, 0));
  EXPECT_EQ(2, Select(false, 3, true, 2, true, 1, 0));
  EXPECT_EQ(0, Select(false, 3, false, 2, false, 1, 0));
 
 return 0;
}