#include <iostream>
#include <mutex>
using namespace std;

std::once_flag flag;

template<typename ...Args>
void gFunc(Args... args)
{
}

template<typename ...Args>
void func(Args... args)
{
    auto lm = [&, args...] 
	          {
	          	// more code here
	            return gFunc(args...);
	          };
    std::call_once(flag,lm);
}

int main() {
	// your code goes here
	func(1);
	return 0;
}