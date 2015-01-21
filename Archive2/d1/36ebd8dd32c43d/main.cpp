#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

template<class T>
auto read_from_stream( std::istream& stream )
-> T
{
    T val;
    stream >> val;
    return val;
}

template<typename... args>
std::tuple<args...> parse(std::istream& stream)  {
  return std::make_tuple(read_from_stream<args>(stream)...);
}
int main()
{
    std::istringstream words ( "1 2" );

    auto t = parse<int, int>(words);
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
}
