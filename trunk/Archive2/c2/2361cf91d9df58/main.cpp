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
    std::call_once(flag,[&args...](/*accept variable number of arguments*/)
                        {
                                // more code here
                                gFunc( args...);
                        }
                        );
}

int main() {
    // your code goes here
	func(1);
	return 0;
}