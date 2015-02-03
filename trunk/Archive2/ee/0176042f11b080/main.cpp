#include <iostream>
#include <string>
#include <utility>
#include <functional>

template <class X, class T, class U> void super_case_impl(X val, T val2,
    						  U y)
{
  if (val == val2) {
    y();
  }
}

template <class X, class T, class U, class ...Pairs> 
void super_case_impl(X val, T val2, U func,
                     Pairs... case_pairs)
{
  super_case_impl(val, val2, func);
  super_case_impl(val, case_pairs...);
}

template <class X, class ...T> void super_case(X val, T... case_pairs)
{
  super_case_impl(val, case_pairs...);
}


int main(void)
{
  int x = 66;
  std::cout << "x before first case is " << x << std::endl;

  super_case(std::string("zomglol"),
    std::string("no hit"), 
    []() {},

    std::string("zomglol"),
    [&]() { 
      std::string a(" yeah,");
      std::string b(" I rule");
      std::cout << "run anything here:" 
		<< (a + b)
		<< std::endl;
      x = 10;
  });

  std::cout << "x after first case is " << x << std::endl;

  super_case(66,
    55, 
    []() {},

    66,
    [&]() { 
      std::string a(" yeah,");
      std::string b(" I rule so sweetly");
      std::cout << "run about anything here:" 
		<< (a + b)
		<< std::endl;
      x = 6;
    });

  std::cout << "x after second case is " << x << std::endl;
}
