#include <map>
#include <string>
#include <vector>
#include <utility>
#include <boost/assign/list_of.hpp>
int main()
{
    enum an_enum {a,b,c,d,e};
    typedef std::vector<std::pair<std::string,an_enum>> pair_container;
    auto pairs = (boost::assign::map_list_of
                       ("a",static_cast<an_enum>(3))              
                       ("b",static_cast<an_enum>(4))
                       ("c",static_cast<an_enum>(0))).operator pair_container();

    return 0;
}