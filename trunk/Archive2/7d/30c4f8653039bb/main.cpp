#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/bimap.hpp>

    #define name_num(NAME, ...)                                                    \
    class NAME {                                                                   \
                                                                                   \
    public:                                                                        \
                                                                                   \
      enum   enums{NAME_NUM_BEGIN_OF_ENUM_MAP,                                     \
                   __VA_ARGS__,                                                    \
                   NAME_NUM_END_OF_ENUM_MAP};                                      \
                                                                                   \
      using  map_type = boost::bimap<enums, std::string>;                          \
                                                                                   \
      NAME(std::string const& str) {                                               \
        std::vector<std::string> v;                                                \
        boost::split(v, str, boost::is_any_of(", "), boost::token_compress_on);    \
        map_type m;                                                                \
                                                                                   \
        for(int i=NAME_NUM_BEGIN_OF_ENUM_MAP+1; i!=NAME_NUM_END_OF_ENUM_MAP; i++)  \
          map_.insert(map_type::value_type(static_cast<enums>(i), v[i-1]));        \
      }                                                                            \
                                                                                   \
      std::string string(enums val)        { return map_.left.at(val); }           \
                                                                                   \
      enums number(std::string const& val) {                                       \
        return map_.right.at(val);                                                 \
      }                                                                            \
                                                                                   \
    private:                                                                       \
      map_type map_;                                                               \
    } NAME(#__VA_ARGS__)


int main() {
  name_num(SEX, MALE, FEMALE);


  try {
    std::string in;
    std::cin >> in;

    switch(SEX.number(in)) {
      case SEX::MALE:
        std::cout << "red army is coming\n";
        break;

      case SEX::FEMALE:
        std::cout << "like the sun\n";
        break;
      
      default:;
      
    }
  }
  catch(std::exception& e) {
    std::cerr << "shit happens... " << e.what() << std::endl;
  }
}
