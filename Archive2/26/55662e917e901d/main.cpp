#include <iostream>
#include <string>
#include <vector>

class Singleton
{
    public:
    static Singleton* instance()
    {
        static Singleton i;
        return &i;
    }
};

int main()
{
  Singleton* i = Singleton::instance(); 
  return 0;
}
