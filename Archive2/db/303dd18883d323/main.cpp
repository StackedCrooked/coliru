#include <iostream>
#include <exception>

class MyException: public std::exception
{
public:
    MyException(const std::string message, const std::string caller = __func__)
        : _caller(caller),
          _msg(message)
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
