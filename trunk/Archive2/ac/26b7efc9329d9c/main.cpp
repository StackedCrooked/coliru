#include <iostream>
#include <functional>
using namespace std;

template<typename R, typename... Args>
auto call(R fun, Args&&... args) -> decltype(fun(std::forward<Args>(args)...))
{
    cout << "call@ " << __LINE__ <<endl;
    return fun(std::forward<Args>(args)...);
}

int main()
{
    cout << call(std::plus<int>(),1,2) <<endl;
    return 0;
}