#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class variadic_format
{
public:
  variadic_format(std::ostream &os)
    : out_{ os }
  { out_ << std::boolalpha; }

  void print(char const * const format)
  {
    /* Check for remaining occurrences of %%. */
    for(char const *tmp{ format }; *tmp; ++tmp)
    {
      if(tmp && *tmp == '%' && *(tmp + 1) == '%')
      { throw std::out_of_range("not enough format arguments supplied"); }
    }
    out_ << format;
  }

  template <typename T, typename... Args>
  void print(char const *format, T &&value, Args &&... args)
  {
    for(; *format; ++format)
    {
      if(*format == '%' && *(format + 1) == '%')
      {
        out_ << std::forward<T>(value);
        print(format + 2, std::forward<Args>(args)...);
        return;
      }
      out_ << *format;
    }
    /* Didn't find %%. */
    throw std::out_of_range{ "too many format arguments" };
  }

private:
  std::ostream &out_;
};

#define log_debug(...) \
{ \
  std::stringstream ss; \
  variadic_format{ ss }.print(__VA_ARGS__); \
  std::cout << ss.str() << std::flush; \
}

int main()
{
    int const a{ 42 };
    std::string const s{ "jeaye" };
    
    log_debug("some text, value: %%; string: %%", a, s);
}
