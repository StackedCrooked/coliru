#include <iostream>
#include <cstdlib>
#include <memory>
#include <mutex>

class Singleton
{
public:

  ~Singleton()
  {
    std::cout << "Destructor" << std::endl;
  }

  static Singleton & getInstance()
  {
    std::call_once(mInstanceLock, []()
    {
      mInstance.reset(new Singleton());
    });
    return *mInstance;
  }

private:

  Singleton()
  {
    std::cout << "Constructor" << std::endl;
  }

  Singleton(const Singleton &fOther) = delete;
  Singleton & operator=(const Singleton &fRhs) = delete;

  static std::shared_ptr<Singleton> mInstance;
  static std::once_flag mInstanceLock;
};

std::once_flag Singleton::mInstanceLock;
std::shared_ptr<Singleton> Singleton::mInstance = nullptr;

int main(int argc, char **argv)
{
  std::cout << "Main start" << std::endl;

  Singleton &localRef = Singleton::getInstance();

  std::cout << "Main end" << std::endl;

  return EXIT_SUCCESS;
}