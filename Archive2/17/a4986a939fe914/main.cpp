namespace detail {

struct Alice {};
struct Bob {};

}

// If operator| is defined before call_or, both compiles
//template <typename A>
//void operator|(const A&, const detail::Bob&) {}

namespace detail {

struct call_or
{
  template <typename A, typename B>
  static auto call(const A& a, const B& b)
    -> decltype(a | b)
  {
    return a | b;
  }
};

}

// If operator| is defined after call_or, clang fails to compile
template <typename A>
void operator|(const A&, const detail::Bob&) {}


int main()
{
  detail::Alice a;
  detail::Bob b;
  detail::call_or::call(a, b);
  
  return 0;
}