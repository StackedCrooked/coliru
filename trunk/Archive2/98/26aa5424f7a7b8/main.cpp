#include <iostream>
#include <exception>
#include <utility>

class MyException: public std::exception
{
public:
    MyException(std::string message, std::string caller = __func__)
        : _caller(std::move(caller)),
          _msg(std::move(message))
    {
    }

    char const *what() const noexcept override
    {
        return _caller.c_str();   
    }
private:
    std::string _caller;
    std::string _msg;
};

int main()
{
    try {
        MyException("test");
    } catch(std::exception const& e) {
        std::cout << e.what() << '\n';
    }
}
