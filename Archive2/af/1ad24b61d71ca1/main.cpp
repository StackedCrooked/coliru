#include <iostream>
#include <tuple>
#include <vector>

template <typename U>
class id_map
{
public:
  typedef U value_type;

public:
  std::vector<U> vec_;
};

template<typename ... T>
class constant_allkey_map
{
private:
  typedef std::tuple<id_map<T>...> tuple_t;

public:
  template<
    std::size_t Idx,
    typename U = typename std::tuple_element<Idx, tuple_t>::type::value_type
  >
  void push_back(U x)
  {
    std::get<Idx>(maps_).vec_.push_back(x);
  }

  template<
    std::size_t Idx,
    typename U = typename std::tuple_element<Idx, tuple_t>::type::value_type
  >
  U get(int i) const
  {
    return std::get<Idx>(maps_).vec_[i];
  }

private:
  tuple_t maps_;
};

int main(int, char**)
{
  constant_allkey_map<int, long> cakm;
  cakm.push_back<0>(1);
  cakm.push_back<0>(3);
  cakm.push_back<1>(2);
  cakm.push_back<1>(4);

  std::cout << cakm.get<0>(0) << std::endl;
  std::cout << cakm.get<1>(0) << std::endl;
  std::cout << cakm.get<0>(1) << std::endl;
  std::cout << cakm.get<1>(1) << std::endl;
}
