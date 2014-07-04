#include <random>
#include <iostream>

template <typename Distribution, typename... Args>
typename Distribution::param_type make_param_type(Args&&... args)
{
  return typename Distribution::param_type(std::forward<Args>(args)...);
}

int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());

  {
    std::uniform_int_distribution<> dist;
    std::cout << dist(gen, make_param_type<decltype(dist)>(0, 10)) << std::endl;
  }
  {
    std::uniform_real_distribution<> dist;
    std::cout << dist(gen, make_param_type<decltype(dist)>(20., 30.)) << std::endl;
  }
  {
    std::bernoulli_distribution dist;
    std::cout << dist(gen, make_param_type<decltype(dist)>(0.25)) << std::endl;
  }
  {
    std::binomial_distribution<> dist;
    std::cout << dist(gen, make_param_type<decltype(dist)>(4, 0.25)) << std::endl;
  }
  {
    std::weibull_distribution<> dist;
    std::cout << dist(gen, make_param_type<decltype(dist)>(1., 1.)) << std::endl;
  }
}
