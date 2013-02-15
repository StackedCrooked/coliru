#include <iostream>

inline void dummy(...) {}


int reportBoolState(bool bVal)
{
    std::cout << bVal << "\t";
    return 0;
}

template <typename... Args>
int reportBoolState(bool bVal, const Args&... args)
{
    std::cout << bVal << "\t";
    reportBoolState(args...);
    return 0;
}

template <typename... Args>
void bool_variadic(const Args&... args)
{
    std::cout << "\nbool states (in FORWARD order):\n" << std::boolalpha;
    //dummy(reportBoolState(args)...);  // this'd be reverse order (right-to-left)
    reportBoolState(args...);
    std::cout << std::endl;
}

template <typename T>
bool boolizer(const T& val)
{
    std::cout <<  val << "\t";
    return (val != 0);
}

template <typename... Args>
void TestVariadic(const Args&... args)
{
    std::cout << "vals (in reverse):" << std::endl;
    bool_variadic(boolizer(args)...);
}

int main ()
{
  int p = 5;
  TestVariadic(0, 4, 'a', '\0', p, 0, "string");

  return 0;
}