#include <iostream>
#include <tuple>

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



template<typename T>
struct RvalueTest{
    RvalueTest(T&& value) : value( std::forward<T>(value) ){}
    T&& value;
};



int main() {
    auto t = std::forward_as_tuple(Widget(12));
    //auto t = std::tuple<Widget&&>(Widget(12));
    std::cout << std::get<0>(t).h;
    /*
    RvalueTest<Widget> r(Widget(12));
    std::cout << r.value.h;*/
}