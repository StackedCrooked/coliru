#include <functional>
#include <string>
#include <iostream>
 
void goodbye(const std::string& s)
{
    std::cout << "Goodbye " << s << '\n';
}
 
class Object {
public:
    void hello(const std::string& s)
    {
        std::cout << "Hello " << s << '\n';
    }
};
 
int main()
{
    typedef std::function<void(const std::string&)> ExampleFunction;
    Object instance;
    std::string str("World");
    ExampleFunction f = std::bind(&Object::hello, &instance, 
                                  std::placeholders::_1);
 
    // equivalent to instance.hello(str)
    f(str);
    f = std::bind(&goodbye, std::placeholders::_1);
 
    // equivalent to goodbye(str)
    f(str);    
    return 0;
}