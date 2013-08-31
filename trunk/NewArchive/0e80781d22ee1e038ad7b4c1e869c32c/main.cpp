#include <map>

struct X{
  X(int, int, int){}
};


int main(){
    std::map<int, X> m;
    m.emplace(42, 1,2,3);
}