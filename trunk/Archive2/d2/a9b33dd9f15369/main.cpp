#include <iostream>
#include <tuple>


#ifndef SET
    #define SET(NAME, VALUE) decltype(VALUE) NAME = VALUE
#endif


// just to see what really called
class Widget {
public:
  Widget(){std::cout << "Widget ctor  " << std::endl; }
  Widget(int h) : h(h){std::cout << "Widget ctor param " << std::endl; }

  Widget(const Widget&) { std::cout << "Widget copy ctor  " << std::endl;  }
  Widget(Widget&&) { std::cout << "Widget move ctor  " << std::endl;  }           // added this

  template<typename T>
  Widget(const T&) { std::cout << "Generalized Widget copy ctor  " << std::endl;  }

  template<typename T>
  Widget(T&&) { std::cout << "Universal Widget ctor  " << std::endl;  }

  int h;
};


// Our concrete classes
struct Plugin1 : Widget{};
struct Plugin2 : Widget{};
struct Plugin3 : Widget{};


struct Hub{
    Plugin1 plugin1;
    Plugin2 plugin2;
    Plugin3 plugin3;
    
    SET (plugins, std::forward_as_tuple(           // Here, only const static, and nothing more
        plugin1, 
        plugin2,
        plugin3
    ));
    
    Hub(){
        plugin1.h = 1;
        plugin2.h = 2;
        plugin3.h = 3;
    }
};

Hub hub;

int main() {
    // well, this gets actually goes in template loop, but I just simplify it.
    // This should be sufficient to test life time.
    
    auto &&i1 = std::get<0>(hub.plugins);
    auto &&i2 = std::get<1>(hub.plugins);
    auto &&i3 = std::get<2>(hub.plugins);
    
    std::cout << i1.h << std::endl;
    std::cout << i2.h << std::endl;
    std::cout << i3.h << std::endl;
    
    return 0;
}