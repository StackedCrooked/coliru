#include <vector>
#include <iostream>

class Demo
{
    int member ;
    
public:
    Demo() : member{0} {}
    Demo(int x) : member{x} {}
    Demo(const Demo&) = delete ; // copy constructor cannot be invoked
    Demo(Demo&&) = default ; // default move constructor
    
    int getMember() const { return member; }
    
};


int main()
{
    std::vector<Demo> trial ;
    trial.push_back(Demo(2));
    std::cout << trial[0].getMember();
    
    // Try this :
    //Demo ob(3);
    //trial.push_back(ob);
    // will throw error
    return 0;
}