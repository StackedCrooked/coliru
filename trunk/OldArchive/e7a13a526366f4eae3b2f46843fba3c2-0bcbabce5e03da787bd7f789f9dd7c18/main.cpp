#include <iostream>
#include <functional>
#include <vector>

void foo(int a, int b)
{
  std::cout << (a*10+b) << "\n" << std::endl;
}

template<int... Is>
struct seq { };

template<int N, int... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

template<int... Is>
struct gen_seq<0, Is...> : seq<Is...> { };

template<class... Args, int... Is>
void callByVector(std::function<void(Args...)> f, std::vector<int>& arguments, seq<Is...>)
{
  f(arguments[Is]...);
}

template<class... Args>
void callByVector(std::function<void(Args...)> f, std::vector<int>& arguments)
{
  callByVector(f, arguments, gen_seq<sizeof...(Args)>());
}

int main()
{
  std::vector<int> arguments;
  arguments.push_back(2);
  arguments.push_back(3);

  callByVector(std::function<void(int,int)>(foo),arguments);
}
