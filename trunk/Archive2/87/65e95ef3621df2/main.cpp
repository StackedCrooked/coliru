#include <iostream>
#include <cstdio>

using namespace std;

class static_thing {
public:
    static_thing() { cout << "Static thing constructed. " << endl; }
    ~static_thing(){ cout << "Static thing destructed" << endl; }
};

void check_thing(static_thing * x){
    printf("Addr: %p\n", static_cast<void*>(x));
}

template <typename T>
class Test {
 public:
    Test() {}
    ~Test() {}
    
    void Initialize(){
        static_thing * y = &Test<T>::x;
        check_thing(y);
    }

 static static_thing x;
};

template <typename T> static_thing Test<T>::x {};

// Crashes:  clang++ -std=c++1y -Wall -pedantic -pthread main.cpp && ./a.out
// Link Failure: g++ -std=c++1y -fno-implicit-templates -Wall -pedantic -pthread main.cpp && ./a.out
// Works: g++ -std=c++1y -Wall -pedantic -pthread main.cpp && ./a.out

// With this line, everything works.
// template <> static_thing Test<int>::x {};

int main(int argc, char* argv[]){
    
    auto x = new Test<int>();
    x->Initialize();
    
    delete x;
    
    return 0;
}
