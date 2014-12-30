#include <iostream>

using namespace std;

int sum(int a, int b) { return a + b; }

template<typename Func, typename... Args>
auto MainCall(Func func, Args&&... args)-> typename std::result_of<Func(Args...)>::type
{
    return func(std::forward<Args>(args)...);
}

template <typename... Args>
int call2(Args const&... args)
{
    return MainCall(sum, args...); /* calling template function MainCall,  
                                      how to pass the variable arguments to   
                                      Maincall from here?
                                   */
}

int main()
{
  cout << call2(4,5) << endl;
}
