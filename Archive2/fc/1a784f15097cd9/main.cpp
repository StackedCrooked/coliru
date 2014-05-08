#include <iostream>
#include <string>
#include <vector>
#include <mutex>

class Singleton
{
    public:
    static Singleton* instance()
    {
        static std::mutex mux;
        std::lock_guard<std::mutex> lock(mux);
        
        static Singleton i;
        return &i;
    }
};

int main()
{
  Singleton* i = Singleton::instance(); 
  return 0;
}
