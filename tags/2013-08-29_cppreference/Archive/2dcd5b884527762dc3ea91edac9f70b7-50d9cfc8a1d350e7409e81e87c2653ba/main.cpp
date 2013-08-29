#include <type_traits>

template<typename T>
void f();



int main(){ f<std::make_signed<const unsigned int>::type>(); }