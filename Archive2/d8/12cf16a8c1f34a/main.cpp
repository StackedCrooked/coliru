// fake testing stuff
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

// real thing
#include <vector>

namespace Wrap {
    // define any << you want here
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
    {
      for (const auto &it : v)
        os << it << " ";
      return os;
    }
    
    // simplistic wrapper that forwards << to the wrapped object
    // in a context where unqualified lookup for << will always find the
    // <<s declared so far in the Wrap namespace.
    template<class T>
    struct Wrapper {
        const T& t;
        Wrapper(const T& t) : t(t) {}
        friend std::ostream& operator<<(std::ostream& os, Wrapper w){
            os << w.t;
            return os;
        }
    };
    
    // helper function to create a wrapper.
    template<class T>
    Wrapper<T> wrap(const T& t) { return Wrapper<T>(t); }
}

using Wrap::wrap;


int main()
{
  std::vector<int> v{1,2,3};

  f << wrap(v);
}