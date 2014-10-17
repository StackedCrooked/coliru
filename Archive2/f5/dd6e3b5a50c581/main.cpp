#include <iostream>
#include <thread>
#include <utility>
#include <vector>

struct Bob
{

    Bob() { std::cout << "default constructor" << std::endl;}

    Bob(const Bob&) noexcept(true){ std::cout << "copy constructor"<< std::endl;}
    Bob(Bob&&) noexcept(true) { std::cout << "move constructor"<< std::endl;}


    Bob& operator=(const Bob&) { std::cout << "copy assignment" << std::endl; return *this;}
    Bob& operator=(Bob&&) { std::cout << "move assignment" << std::endl; return *this;}
};

int main()
{

   std::vector<Bob> first{Bob{}, Bob{}};
   //std::vector<bool> first{true, true, false};
   
   std::cout << "loop starts here "<<std::endl;
    std::vector<Bob> second;
    for (auto& bob: first)
    {
        second.emplace_back(std::forward<decltype(bob)>(bob));
    }
        
}
