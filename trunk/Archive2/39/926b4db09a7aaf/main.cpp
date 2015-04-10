#include <iostream>
#include <sstream>
namespace Test {
    struct foo {
    };
    template<class T>
    void operator<<(foo, const T& t) {
        std::stringstream s;
        s << t;
        std::cout << s.str();
    }
}

Test::foo f;

#include <vector>

namespace Wrap {
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
    {
      for (const auto &it : v)
        os << it << " ";
      return os;
    }
    
    template<class T>
    struct Wrapper {
        const T& t;
        Wrapper(const T& t) : t(t) {}
        friend std::ostream& operator<<(std::ostream& os, Wrapper w){
            os << w.t;
            return os;
        }
    };
    
    template<class T>
    Wrapper<T> wrap(const T& t) { return Wrapper<T>(t); }
}

using Wrap::wrap;


int main()
{
  std::vector<int> v{1,2,3};

  f << wrap(v);
}