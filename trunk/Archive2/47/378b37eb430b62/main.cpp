#include <iostream>

float join(float f, int)   { return f; }
float join(float f, float) { return f; }

template <typename Inner>
struct wrapper
{
  using inner_t = Inner;
  inner_t value;
};

template <typename Inner>
std::ostream& operator<<(std::ostream& os, const wrapper<Inner>& w)
{
  return os << "wrap(" << w.value << ')';
}

template <typename Inner1, typename Inner2>
auto
join(const wrapper<Inner1>& w1, const wrapper<Inner2>& w2)
  -> wrapper<decltype(::join(w1.value, w2.value))>
{
  return {join(w1.value, w2.value)};
}

template <typename Inner1, typename T2>
auto
join(const wrapper<Inner1>& w1, const T2& value2)
  -> wrapper<decltype(::join(w1.value, value2))>
{
  return {join(w1.value, value2)};
}

template <typename T1, typename Inner2>
auto
join(const T1& value1, const wrapper<Inner2>& w2)
  -> decltype(::join(w2, value1))
{
  return join(w2, value1);
}

int main()
{
  int i = 1;
  float f = 2.2;
  wrapper<float> fw = {3.3};
#define ECHO(S) std::cerr << #S": " << S << '\n'
  ECHO(join(f, i));
  ECHO(join(fw, i));
  ECHO(join(i, fw));
  ECHO(join(fw, fw)); // Works.
}
