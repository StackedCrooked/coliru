#include <boost/variant.hpp>

#include <iostream>
#include <functional>
#include <vector>
#include <string>

using variant = boost::make_recursive_variant
<
  std::string,
  std::vector<boost::recursive_variant_>,
  std::function
  <
    boost::recursive_variant_ (std::vector<boost::recursive_variant_> const&)
  >
>::type;
using variant_string = std::string;
using variant_vector = std::vector<variant>;
using variant_function = std::function<variant (variant_vector const&)>;

using recursive_variant = boost::recursive_variant_;
using recursive_vector = std::vector<recursive_variant>;

int main()
{
  variant vs{ "ok" };
  std::cout << boost::get<variant_string>(vs) << std::endl;

  variant vv{ variant_vector{ "1", "2" } };
  for(auto const &e : boost::get<variant_vector>(vv))
  { std::cout << boost::get<variant_string>(e) << " "; }
  std::cout << std::endl;

  variant vfv
  {
    /* XXX: These should not be the recursive types. */
    [](recursive_vector const&) -> recursive_variant
    {
      std::cout << "boop" << std::endl;
      return {};
    }
  };
}