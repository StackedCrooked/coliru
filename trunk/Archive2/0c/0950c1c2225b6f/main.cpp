#include <iostream>
 
template <typename T>
void bar(T t) { std::cout << t << '\n'; }
 
template <typename... Args>
void foo2(Args&&... args)
{
  __attribute__((unused)) int dummy[] = { 0, ((void) bar(std::forward<Args>(args)),0)... };
}
 
int main()
{
  foo2();
  foo2 (1, 2, 3, "30");
}