// SocketException class
#ifndef SocketException
#define SocketException

#include <exception>

class SocketExceptionCreate : std::exception
{
    public:
		const char *what() { return( "Could not create socket." ) };
};


class SocketExceptionBind : std::exception
{
	public:
		const char *what() { return( "Could not bind to port." ) };
};


class SocketExceptionAccept : std::exception
{
	public:
		const char *what() { return( "Socket accept() failed." ) };
};



// Examples of throwing these exceptions:
throw SocketExceptionCreate();
throw SocketExceptionBind();
throw SocketExceptionAccept();

#endif
