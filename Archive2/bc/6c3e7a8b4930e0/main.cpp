    template <class T>
    struct multiCompareProxy {
      bool b;
      T const& t;

      explicit operator bool() const {return b;}
      multiCompareProxy operator==(T const& rhs) {
        return {b && t.equals(rhs), t};
      }
    };

    template <class T>
    multiCompareProxy<T> operator==(T const& lhs, T const& rhs) {
      return { lhs.equals(rhs), lhs };
    }

    struct A {
      int i;
      bool equals(A const& rhs) const {
        return i == rhs.i;
      }
    };
    
#include <iostream>

    int main() {
      A a{5};
      A b{5};
      A c{5};
      A d{6};

      if (a==b==c) {
        std::cout << "a==b==c\n";
      }

      if (a==b==c==d) {
        std::cout << "a==b==c==d\n";
      }
    }
    