#include <iostream>
#include <string>
#include <vector>


class Printer {
    public:
    template<typename T>
   static void printSomething(T toPrint){
        std::cout << toPrint;
    }
};

std::string print(std::string test){
    std::cout << test;
    return test;
}
int main()
{
   bool test = false;
std::string teststr;
   test && (std::cout << "test is true");
   !test && (std::cout << "test is false");
   test && teststr = "wow";
   
   std::cout << teststr;
    // test && print("test is very true");
}
