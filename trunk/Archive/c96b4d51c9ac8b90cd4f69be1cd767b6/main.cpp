#include <iostream>
#include <vector>
#include <functional>


class A
{
    public:
        template<typename Function>
        void add(Function && fn) 
        {  
            _functions.push_back(std::forward<Function>(fn)); 
        }
        void invoke_all()
        {
           for(auto && fn : _functions)
                fn();
        }
    private:
        std::vector<std::function<void()>> _functions;
};

void myfunction() { std::cout << "myfunction" << std::endl ; }

struct myfunctor
{
       void operator()() { std::cout << "myfunctor" << std::endl ; }
};


int main()
{
    A a;
    a.add(myfunction);
    a.add(myfunctor());
    a.invoke_all();
}