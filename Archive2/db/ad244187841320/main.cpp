#include <iostream>

namespace lib
{
    template <typename T>
    int bar(T t)
    {
        std::cout << "generic.\n";
        return 0;
    }
}

namespace custom
{
    struct foo
    {
    };
    
    int bar(foo f)
    {
        std::cout << "custom.\n";
        return 0;
    }
}

void quaz(custom::foo& f)
{
    using lib::bar;
    bar(f);
}

struct bar2
{
  bar2(custom::foo& f);
  int i;
  private:
  static int wrapper(custom::foo& f)
  {
      using lib::bar;
      return bar(f);
  }
};

bar2::bar2(custom::foo& f)
  : i{wrapper(f)} // want a::foo if available, else std::foo
{ }

int main()
{
    custom::foo f;
    bar2 bar2{f};
    return 0;
}
