#include <iostream>
#include <vector>
#include <list>

template<class T>
class MyClass
{
   public:
      void run()
      {
            std::cout << "Unsupported data type" << std::endl;
      }
};

template<>
void MyClass<std::vector<int>>::run()
{
    std::cout << "vector\n";
}

template<>
void MyClass<std::list<double>>::run()
{
    std::cout << "list\n";
}

int main()
{
    MyClass<std::vector<int>> m1;
    m1.run();
    MyClass<std::list<double>> m2;
    m2.run();
    MyClass<char> m3;
    m3.run();
}
