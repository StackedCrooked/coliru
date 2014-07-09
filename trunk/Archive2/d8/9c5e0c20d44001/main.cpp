#include <stdexcept>
#include <iostream>

class SocketExceptionCreate : public std::runtime_error
{
    public:
		SocketExceptionCreate() : std::runtime_error("Could not create socket.") {}
};

struct SocketExceptionBind : public std::runtime_error
{
    SocketExceptionBind() : std::runtime_error("Could not bind to port.") {}
};

int main() {}