#include <iostream>

inline void print() {}

template <typename T, typename ...ArgTypes>
inline void print(T t, ArgTypes ...args)
{
  std::wcout << t << '\n';
  if(sizeof...(args))
    print(args...);
}

template<typename ...Args>
void double_args(Args&& ...args)
{
  print(2 * std::forward<Args>(args)...);
}

int main()
{
    double_args(1,2,3);
}