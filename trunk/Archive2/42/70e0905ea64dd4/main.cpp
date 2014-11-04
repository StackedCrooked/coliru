#include <iostream>
#include <functional>
#include <sstream>

template<typename T>
std::ostream& serialize(std::ostream& out, const std::function<T>& fn)
{
  using decay_t = typename std::decay<T>::type;
  if(fn.target_type() != typeid(decay_t)) throw std::runtime_error(std::string(typeid(decay_t).name()) + " != " + fn.target_type().name());
  const auto ptr = fn.template target<decay_t>();
  out << reinterpret_cast<void*>(*ptr);
  return out;
}

template<typename T>
std::istream& deserialize(std::istream& in, std::function<T>& fn)
{
  using decay_t = typename std::decay<T>::type;
  void* ptr = nullptr;
  in >> ptr;
  fn = reinterpret_cast<decay_t>(ptr);
  return in;
}

int square(int x) { return x * x; }

int main(int argc, char** argv)
{
  std::stringstream ss { };
  {
    std::function<int(int)> fn = square;
    serialize(ss, fn);
    std::cout << fn(2) << std::endl;
  }
  {
    std::function<int(int)> fn = square;
    deserialize(ss, fn);
    std::cout << fn(2) << std::endl;
  }
}
