#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Base
{
public:
    Base() =  default;
    ~Base() = default;
public:   
    //functions to override in descendant;
    virtual int getFive()   const { return 5; }
    virtual int getTen()    const { return 10; }    
            int getTwenty() const { return 20;}
    virtual int getForty()  const final {return 40;} 
    //virtual and final rarely appear in one line, 
    //here we simulate that a getForty inherited from another class
    //and set it to final in Base.
};

//override helps us and the compiler to find out that we
//managed to override a function or we failed it.
class Descendant : public Base
{
    public:
        Descendant() =  default;
        ~Descendant() = default;
public:   
    //functions to override - ;
    int getFive()   const override { return 5+1; }
    int getTen()          override { return 10+1;}    
    int getTwenty() const override { return 20+1;}
    int getForty()  const override { return 40+1;}
    int getSixty()  const override { return 60+1;}
};


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
