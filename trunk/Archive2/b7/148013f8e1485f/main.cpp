#include <iostream>
#include <string>
#include <deque>

using std::deque;
using std::basic_string;

template<typename T = basic_string<char>>
class LogStack : public deque<T>
{
    private:
		deque<T> Stack;

	public:
		LogStack(int size = 1)
			: Stack(size) {}

		void push_back(T object)
		{
			if(Stack.size() == 1000) Stack.pop_front();
			Stack.push_back(object);
		}
        
        T operator[](int i) { return Stack.at(i); }
};

int main()
{
    LogStack<int> TheStack;
    for(int i = 0; i < 1001; i++) TheStack.push_back(i);
    for(int i = 0; i < 1000; i++)
    {
        std::cout<< TheStack[i]<< std::endl; std::cin.get();
    }
}