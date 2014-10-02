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

template <typename T>
auto ret(T t)
{
  return [=] (auto s) { return std::make_pair(t, s); };
}

template <typename S, typename M, typename C>
auto bind(M m, C c)
{
   return [=] (S s) {
     auto p = m(s);
     return c(p.first)(p.second);
   };
}
  
} /* state_monad */

///////////////////////////////////////////////////////////////////////////////
/// Sample1
///////////////////////////////////////////////////////////////////////////////
namespace sample1 {

namespace sm = state_monad;

using State = std::string;

std::function<std::pair<double, State>(State)>
int_to_double(int v)
{
  return [=] (State s) -> std::pair<double, State> {
    s += "int_to_double;\n";
    return { static_cast<double>(v), s };
  };
}

std::function<std::pair<std::string, State>(State)>
double_to_string(double v)
{
  return [=] (State s) -> std::pair<std::string, State>  {
    s += "double_to_string;\n";
    return { std::to_string(v), s };
  };
}

std::function<std::pair<int, State>(State)>
string_to_int(std::string v)
{
  return [=] (State s) -> std::pair<int, State> {
    s += "string_to_int;\n";
    return { std::stol(v), s };
  };
}

void run()
{
  auto f = 
         sm::bind<State>(int_to_double(4),       [=] (auto v1) { 
  return sm::bind<State>(double_to_string(v1),   [=] (auto v2) {
  return sm::bind<State>(string_to_int(v2),      [=] (auto v3) {
                         return sm::ret(v3);
  });});});

  std::string s;
  auto p = f(s);
  std::cout << "= sample 1 ==============================" << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << "result value:" << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << p.first << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << "result state:" << std::endl;
  std::cout << "-------------" << std::endl;
  std::cout << p.second << std::endl;
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
    return result_t{ values_t{}, stack};
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
           sm::bind<stack_i>(push(4), [=] (auto )   {
    return sm::bind<stack_i>(push(5), [=] (auto )   {
    return sm::bind<stack_i>(pop(),   [=] (auto v2) {
    return sm::bind<stack_i>(pop(),   [=] (auto v3) {
                             auto v_2_3 = merge(v2, v3);
                             return sm::ret(v_2_3);
  });});});});

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
