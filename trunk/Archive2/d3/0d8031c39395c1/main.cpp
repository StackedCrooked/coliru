#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <stack>

///////////////////////////////////////////////////////////////////////////////
/// State Monad
///////////////////////////////////////////////////////////////////////////////
namespace state_monad {
    
/// value를 반환하는 형식의 monadic type
///   std::pair<T, State> (State)
///
/// void를 반환하는 형식의 monadic type
///   State (State)
///

template <typename T>
auto ret(T t)
{
  return [t] (auto s) { return std::make_pair(t, s); };
}

auto ret()
{
  return [] (auto s) { return s; };
}

template <typename State, typename M, typename C>
auto bind(M m, C c,        
          std::enable_if_t<std::is_same<State, decltype(m(std::declval<State>()))>::value>* = nullptr)
{
   return [m,c] (State s) {
     auto p = m(s);
     return c()(p);
   };
}

template <typename S, typename M, typename C>
auto bind(M m, C c,
          std::enable_if_t<!std::is_same<S, decltype(m(std::declval<S>()))>::value>* = nullptr)
{
   return [m, c] (S s) {
     auto p = m(s);
     return c(p.first)(p.second);
   };
}

  
} /* state_monad */

///////////////////////////////////////////////////////////////////////////////
/// Sample1
///////////////////////////////////////////////////////////////////////////////
namespace sample1 {
//-----------------------------------------------------------------------------
// alias

namespace sm = state_monad;

using State = std::string;

using st_int    = std::pair<int, State>;
using st_double = std::pair<double, State>;
using st_string = std::pair<std::string, State>;

using re_int    = std::function<st_int   (State)>;
using re_double = std::function<st_double(State)>;
using re_string = std::function<st_string(State)>;

template<typename U, typename V>
U value(const std::pair<U,V>& t) { return t.first; };

template<typename U, typename V>
V state(const std::pair<U,V>& t) { return t.second; };

//-----------------------------------------------------------------------------

re_double int_to_double(int v)
{
  return [v] (State s) {
    s += "int_to_double;\n";
    return st_double{static_cast<double>(v), s };
  };
}

re_string double_to_string(double v)
{
  return [v] (State s) {
    s += "double_to_string;\n";
    return st_string{ std::to_string(v), s };
  };
}

re_int string_to_int(std::string v)
{
  return [v] (State s) {
    s += "string_to_int;\n";
    return st_int{ std::stol(v), s };
  };
}

void run()
{
  auto f = 
         sm::bind<State>(  int_to_double(4),       [] (auto v1) { 
  return sm::bind<State>(  double_to_string(v1),   [] (auto v2) {
  return sm::bind<State>(  string_to_int(v2),      [] (auto v3) {
                           return sm::ret(v3);
  });});});

  State init;
  auto p = f(init);
  std::cout << "= sample 1 ==============================" << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << "result value:" << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << value(p) << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << "result state:" << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << state(p) << std::endl;
  std::cout << std::endl;
}
  
} /* sample1 */

///////////////////////////////////////////////////////////////////////////////
/// Sample2
///////////////////////////////////////////////////////////////////////////////
namespace sample2 {

namespace sm = state_monad;

template <typename T>
struct stack_t
{
  void push(T t) { stack_.push(t); }
  T pop() { auto t = stack_.top(); stack_.pop(); return t; }

  std::stack<T> stack_;
};

using stack_i   = stack_t<int>;
using values_t  = std::vector<int>;
using result_t  = std::pair<values_t, stack_i>;

inline values_t merge(values_t first, values_t second)
{
  first.insert(end(first), begin(second), end(second));
  return first;
}

auto push(int element)
{
  return [=] (stack_i stack)
  {
    stack.push(element);
    return stack;
  };
}

auto pop()
{
  return [] (stack_i stack)
  {
    values_t value{ stack.pop() };
    return result_t{ value, stack };
  };
}

void print(values_t vals, const std::string& header = "")
{
  if (header != "")
    std::cout << header;

  std::cout << "{";
  if (!vals.empty())
  {
    std::copy(begin(vals), end(vals) - 1, std::ostream_iterator<decltype(*begin(vals))>(std::cout, ", "));
    std::copy(end(vals) - 1, end(vals), std::ostream_iterator<decltype(*begin(vals))>(std::cout));
  }
  std::cout << "}";
}

void println(values_t vals, const std::string& header = "")
{
  print(vals, header);
  std::cout << std::endl;
}

void println(stack_i stack, const std::string& header = "")
{
  values_t vals;
  while (!stack.stack_.empty())
    vals.push_back(stack.pop());
  print(vals, header);
}

void run()
{
  auto f =
           sm::bind<stack_i>(push(4),   [=] ()        {
    return sm::bind<stack_i>(push(5),   [=] ()        {
    return sm::bind<stack_i>(pop(),     [=] (auto v2) {
    return sm::bind<stack_i>(sm::ret(), [=] ()        {             /// for testing
    return sm::bind<stack_i>(pop(),     [=] (auto v3) {
                             auto v_2_3 = merge(v2, v3);
                             return sm::ret(v_2_3);
  });});});});});

  stack_i stack_0;
  auto result = f(stack_0);
  std::cout << "= sample 2 ==============================" << std::endl;
  println(result.first, "values : ");
}

} /* sample2 */

int main()
{
  sample1::run();
  sample2::run();
}
