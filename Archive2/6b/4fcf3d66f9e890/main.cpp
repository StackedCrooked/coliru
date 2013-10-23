#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <boost/generator_iterator.hpp>

int main()
{
  const std::string data = "hello";
  auto curr = data.end();
  
  std::function<char()> gen = [curr,data]() mutable -> char
  { 
      if (curr==data.end())
          return *(curr=data.begin())++;
      return *curr++;
  };

  auto it = boost::make_generator_iterator(gen);
  std::copy_n(it, 35, std::ostream_iterator<char>(std::cout, ";"));
}
