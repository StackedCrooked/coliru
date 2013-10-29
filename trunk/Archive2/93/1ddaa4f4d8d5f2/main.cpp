#include <vector>
#include <string>
#include <iostream>

struct A{
    struct Default {};
    template <typename T>
    struct Parm{
        Parm() : gotHam(false), ham() {};
        Parm(const Default&) : gotHam(false), ham() {}
        Parm(const T& ham_) : gotHam(true), ham(ham_) {}
        operator bool(){
            return gotHam;
        }
        const bool gotHam;
        T ham;
    };
    A(std::string s_) : s(s_), i(5) {}
    
    void myFunction(Parm<std::string> s_ = Parm<std::string>(), Parm<int> i_ = Parm<int>()){
        std::string sValue = s_?s_.ham:s;
        int iValue = i_?i_.ham:i;
        std::cout << sValue << '\t' << iValue << std::endl;
    }
    
    std::string s;
    int i;
};

int main() {
   A a("defaulted");
   
   a.myFunction(std::string("caller provided"));
   a.myFunction(A::Default());
   a.myFunction();
   
   a.myFunction(std::string("caller provided"), 10);
   a.myFunction(A::Default(), 10);
}
