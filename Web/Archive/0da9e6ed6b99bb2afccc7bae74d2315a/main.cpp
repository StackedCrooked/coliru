#include <tuple>

struct X{};

struct Y{
  X& member;
};

int main(){
  std::tuple<X> t1;
  std::tuple<Y> t2(t1);
}