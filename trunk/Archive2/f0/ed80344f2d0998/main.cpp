#include <iostream>
#include <memory>
#include <functional>
#include <string>

template <typename T>
class X {  
public:
    T t;
    X(T tt) {t = tt;}
    int getLuv() {
        return t[0]%100/2;    
    }
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    /*****************************************
    Vul in dit variabel hieronder je naam in
    *****************************************/
    std::string jeNaam = "Rob";
    
    
    auto refP = make_unique<X<std::string>>(jeNaam);
    auto refW = make_unique<X<std::string>>("Sebastiaan");
    
    std::cout << "Je houdt " << refP->getLuv() << "% van Sebastiaan - ";
    (refP->getLuv() > 35) ? (std::cout << "full homo") : (std::cout << "no homo");
    
    return 0;    
}