#include <limits>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <unordered_map>

using std::cout;
using std::endl;

template<typename T>
struct is_polymorphic_functor
{
private:
	//test if type has operator()
	template<typename U, typename V>
	static auto ftest(U *u, V* v) -> decltype((*u)(*v), char(0));
	static std::array<char, 2> ftest(...);
    
    struct private_type { };

public:
	static const bool value = sizeof(ftest((T*)nullptr, (private_type*)nullptr)) == 1;
};

struct polyfun
{
    template<class T>
    void operator()(T) {};
};

int main()
{  
  // cout<<std::boolalpha;
   
   //cout<<is_polymorphic_functor<polyfun>::value;
   
   cout<<"what";
}