//http://stackoverflow.com/questions/28184984/different-behavior-of-c11-list-initialization
#include <string>
#include <initializer_list>

class A {
private:
  std::string s;
public:
  A() = delete;
  A(const A&) = delete;
  A(A&&) = delete;
  A(const std::string &a) : s(a) {}
};

template< typename T >
struct Aggr {
    T arr[2];
    template<typename ...A> Aggr(A&&...t):arr{ std::forward<A>(t)... } {}
};

template< typename T >
struct Nested {
    struct { T arr[2]; } aggregate;
    Nested() : aggregate { {
        {"[0]"},{"[1]"}
    }} {}
};

int main() {
    Nested<           A > obj;
    Nested< std::string > obj2;
    Aggr  < std::string > obj3;
    Aggr  <           A > obj4{ {{"[0]"},{"[1]"}} }; // main.cpp:23:46: error: use of deleted function 'A::A(A&&)'
}

