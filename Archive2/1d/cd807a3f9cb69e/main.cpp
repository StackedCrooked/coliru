#include <functional>
#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>

template <typename... Functions>
class overloaded_function {};

template <typename Return, typename... Args, typename... Rest>
class overloaded_function<Return(Args...), Rest...> : public overloaded_function<Rest...>
{
private:
  typedef std::function<Return(Args...)> fn_t;
  fn_t fn_;

public:
  overloaded_function(fn_t fn, std::function<Rest>... rest)
  : overloaded_function<Rest...>(rest...),
    fn_(fn)
  {
  }
  Return operator()(Args... args)
  {
    using namespace std
    vector<string> names{typeid(Args).name()...};
    cout << "operator()( ";
    for(auto name: names) cout << name << ' ';
    cout << ")\n";

    return fn_(args...);
  }
};

int main()
{
  using namespace std;
  overloaded_function<
    int(int), 
    float(float, float), 
    string(string)
    >
  three(
    [](int){return 3;}, 
    [](float, float){return 3.F;}, 
    [](string){return "three";}
    );
  
  three(1);
  three(3.F, 1.F);
  three(string("yo"));
  
  return 0;
}