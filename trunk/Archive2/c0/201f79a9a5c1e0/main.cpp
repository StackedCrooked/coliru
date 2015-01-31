#include <boost/variant.hpp>

#include <iostream>
#include <functional>
#include <vector>
#include <string>

enum class cell_type
{
  string,
  list,
  function
};

template <cell_type C>
struct cell;

using variant = boost::variant
<
  boost::recursive_wrapper<cell<cell_type::string>>,
  boost::recursive_wrapper<cell<cell_type::list>>,
  boost::recursive_wrapper<cell<cell_type::function>>
>;

template <>
struct cell<cell_type::string>
{ std::string data; };
template <>
struct cell<cell_type::list>
{ std::vector<variant> data; };
template <>
struct cell<cell_type::function>
{ std::function<variant (cell<cell_type::list> const&)> data; };

using cell_string = cell<cell_type::string>;
using cell_list = cell<cell_type::list>;
using cell_func = cell<cell_type::function>;

int main()
{
  variant vs{ cell_string{ "ok" } };
  std::cout << boost::get<cell_string>(vs).data << std::endl;

  variant vv{ cell_list{ { cell_string{ "1" }, cell_string{ "2" } } } };
  for(auto const &e : boost::get<cell_list>(vv).data)
  { std::cout << boost::get<cell_string>(e).data << " "; }
  std::cout << std::endl;

  variant vfv
  {
    cell_func
    {
      [](cell_list const&) -> variant
      {
        std::cout << "boop" << std::endl;
        return {};
      }
    }
  };
  boost::get<cell_func>(vfv).data(boost::get<cell_list>(vv));
}