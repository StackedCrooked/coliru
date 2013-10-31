#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>

struct OtherClass { };

struct MyClass
{
  void start()
  {
    if (inst)
      throw std::logic_error ("");

    inst.reset(new OtherClass);
  }

  void stop()
  {
    if (!inst)
      throw std::logic_error ("");

    inst.reset();  // this throw an exception
  }

  private:
  std::shared_ptr<OtherClass> inst;
};


int main()
{
  MyClass a;
  a.start();
  a.stop();
}
