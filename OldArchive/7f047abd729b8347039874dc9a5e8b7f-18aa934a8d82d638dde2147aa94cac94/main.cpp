#include <iostream>
#include <stack>
#include <functional>

class G 
{
public:
    G() {}
    template<typename F>
    G(F&&) 
    {
       std::cout << "G(F&&)" << std::endl;
    }
   // G(G const&) = default;
    ~G() { std::cout << "destructed" << std::endl; }
};
int main()
{
    G g1;
    const G g2;
    
    G g3(g1); //invokes the templated constructor; absence  or presence of of explicit copy-constructor doesn't change this fact
    
    std::cout << "----" << std::endl;
    
    G g4(g2); //invokes the copy-constructor; absence or presence of explicit copy-constructor doesn't change this fact
    return 0;
}