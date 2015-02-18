#include <type_traits>
#include <iostream>
#include <typeinfo>

void do_in_order() {}

template<class...Fs>
void do_in_order( Fs&&...fs ) {
  int _[]={0, (void(
    std::forward<Fs>(fs)()
  ),0)... };
  (void)_;
}
template<class T>
void print_type_name() {
    std::cout << typeid(T).name() << std::endl;
}
template<class...Ts>
void print_type_names() {
#if 1
  do_in_order( [&]{
    std::cout << typeid(Ts).name() << std::endl;
  }... );
#else
  do_in_order( print_type_name<Ts>... );
#endif
}

int main() {
    print_type_names<int, double, char>();
}