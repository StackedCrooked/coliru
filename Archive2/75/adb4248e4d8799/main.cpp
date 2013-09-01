#include <list>
#include <iostream>
 
template <
    class T1,
    class... T,
    class = typename std::enable_if<std::is_trivial<T1>::value>::type
>
void run_with_trivial(T1, T...) {}
 
int main()
{
  std::list<short> list;
  run_with_trivial(1, 2, 3, 4); // ok: T1 = int, T = int, int, int
  // run_with_trivial(list, 2, 3, 4); // error: T1 is not trivial =>
      // couldn't infer template argument
  std::cout << "done\n";
}