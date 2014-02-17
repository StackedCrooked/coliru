#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <typeinfo>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


template<class Tuple, std::size_t N>
  struct TupleStringizer
  {
      static std::string to_string(const Tuple& t) 
      {
          std::ostringstream o;
          std::string ans = TupleStringizer<Tuple, N-1>::to_string(t) + ", ";
          std::string info = std::string("[") + typeid(std::get<N-1>(t)).name() + std::string("]");
          o << std::get<N-1>(t);
          return (ans + info + o.str());
      }
  };
   
  template<class Tuple>
  struct TupleStringizer<Tuple, 1>
  {
      static std::string to_string(const Tuple& t) 
      {
          std::ostringstream o;
          std::string info = std::string("[") + typeid(std::get<0>(t)).name() + std::string("]");
          o << std::get<0>(t);
          return (info + o.str());
      }
  };
   
  template<class... Args>
  std::string to_string(const std::tuple<Args...>& t) 
  {
      return ( "("+ TupleStringizer<decltype(t), sizeof...(Args)>::to_string(t) + ")" );
  }




int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    auto a = std::make_tuple(1,3,"eleenty",6);
    std::cout << to_string(a) << std::endl;
}

