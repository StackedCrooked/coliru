#include <iostream>

// **** posix *****
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// **** posix *****

// **** windows *****
// #include <winsock2.h> 
// windows: link with winsock 2 library
// #pragma comment( lib, "ws2_32.lib" )    
// **** windows *****

const short standard_http_port = 80 ;
const char* const google = "74.125.236.201" ;
const char http_get[] = "GET /index.html HTTP/1.0 \r\n\r\n" ; // google search home page

int main()
{
    // **** windows *****
    // WSADATA data{} ;
    // if( WSAStartup( 1, &data ) != 0 ) return 1 ;
    // static auto close = [] ( SOCKET fd ) { closesocket(fd) ; } ;
    // **** windows *****

    sockaddr_in ipv4_address {} ;
    ipv4_address.sin_family = AF_INET;
    ipv4_address.sin_addr.s_addr = inet_addr(google);
	ipv4_address.sin_port = htons(standard_http_port);
	const sockaddr* address = reinterpret_cast<sockaddr*>( &ipv4_address ) ;

	auto sock = socket( AF_INET, SOCK_STREAM, 0 ) ;
	if( sock != -1 && connect( sock, address, sizeof(ipv4_address) ) >= 0
                   && send( sock, http_get, sizeof(http_get) - 1, 0 ) >= 0 )
    {
        const std::size_t SZ = 1024 * 32 ;
        static char page[SZ] {};
        const int nbytes = recv( sock, page, SZ, 0 ) ;
        if( nbytes != -1 ) std::cout << page << '\n' ;
    }
    close(sock) ;
}
