#include <cstdio> 

namespace {
    template<typename...Args> 
    void f(Args&&...args) {
      [](...){}((args(),0)...);
    }
    
    void h() { puts("h"); }
    void i() { puts("i"); }
    void j() { puts("j"); }
}

int main() { 
    f(h, i, j); 
    puts("...");
}
