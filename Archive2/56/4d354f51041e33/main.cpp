#include <stdexcept>

struct SocketExceptionCreate : std::runtime_error
{
    SocketExceptionCreate() : std::runtime_error("Could not create socket.") {}
};

struct SocketExceptionBind : std::runtime_error
{
    SocketExceptionBind() : std::runtime_error("Could not bind to port.") {}
};

struct SocketExceptionAccept : std::runtime_error
{
    SocketExceptionAccept() : std::runtime_error("Socket accept() failed.") {}
};

int main() {}
