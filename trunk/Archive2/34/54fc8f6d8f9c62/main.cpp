#include <iostream>
#include <string>
#include <vector>

struct Noisy {
    Noisy() { std::cout << "Default construct" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Copy construct" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Move construct" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "Copy assignment" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "Move assignment" << std::endl; return *this; }
    ~Noisy() { std::cout << "Destructor" << std::endl; }
};

Noisy f(){
    Noisy ret; //NRVO possible
    return ret;
}
Noisy g(){
    int i;
    Noisy ret;  //NRVO not possible?
    return ret;
}

int main()
{
    g();
}
