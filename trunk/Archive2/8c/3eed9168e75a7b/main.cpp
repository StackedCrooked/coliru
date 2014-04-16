#include <vector>
#include <deque>
#include <set>
#include <list>

namespace container
{
    template <typename T> struct vector { typedef std::vector<T> type; };
    template <typename T> struct set    { typedef std::set   <T> type; };
    template <typename T> struct list   { typedef std::list  <T> type; };
    template <typename T> struct deque  { typedef std::deque <T> type; };
}

template<typename T, template <typename> class Container>
struct wrap_into_container
{
    typedef typename Container<T>::type type;
};

#include <string> 

int main() {

    wrap_into_container<int,         container::set>::type    ws;
    wrap_into_container<double,      container::list>::type   wl;
    wrap_into_container<bool,        container::deque>::type  wd;
    wrap_into_container<std::string, container::vector>::type wv;


    return ws.size() + wl.size() + wd.size() + wv.size();

}
