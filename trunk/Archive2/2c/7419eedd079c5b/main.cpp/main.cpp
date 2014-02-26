#include <iostream>

inline void print();

template <typename T, typename ...ArgTypes>
inline void print(T t, ArgTypes ...args)
{
  std::wcout << t << '\n';
  if(sizeof...(args))
    print(args...);
}

template<int... Ns>
void double_ints()
{
  print(2*Ns...);
}

int main()
{
    double_ints<1,2,3>();
}