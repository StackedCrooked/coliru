#include <iostream>

template<bool = true> class Singleton {
public:

    static Singleton singleton;
  
private:
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};
 
template<>
Singleton<> Singleton<>::singleton = {};

int main() {}