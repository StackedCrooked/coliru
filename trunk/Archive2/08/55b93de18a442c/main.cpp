#include <iostream>
#include <utility>
#include <tuple>
#include <functional>

    struct helper {
        helper() { std::cout << "created\n"; }
        ~helper() { std::cout << "destroyed\n"; }
    };
    struct bob {
        operator helper() { return {}; }
    };
    void test( std::pair< helper const&, double const& > )
    {
        std::cout << "test body\n";
    }
    struct sink { template<class T>sink(T&&) {} };
    int main() {
      std::pair< bob, double > bad = {};
      sink{bad};
      std::pair< helper, double > good1 = {};
      std::pair< const helper, double > good2 = {};
      // test(bad); // does not compile
      test(good1); // compiles
      test(good2); // compiles
    }
