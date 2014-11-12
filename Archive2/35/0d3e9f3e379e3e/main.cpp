#include <exception>
#include <stdexcept>

int main()
{
    [] () [[noreturn]] -> int { throw std::runtime_error("error"); };
}
