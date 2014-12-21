#include <iostream>
#include <string>
#include <vector>
#include <functional>


using namespace std;


template<typename T>
struct memfun_type
{
    using type = void;
};

template<typename Ret, typename Class, typename... Args>
struct memfun_type<Ret(Class::*)(Args...) const>
{
	using type = std::function<Ret(Args...)>;
};

template<typename F>
typename memfun_type<decltype(&F::operator())>::type
FFL(F const &func)
{ // Function from lambda !
	return func;
}

int main()
{
   vector<function<void()>> v = { FFL([]{cout << "foo"; }), FFL([]{cout << "bar"; }) };
    
	for (auto&& a : v) a();
}
