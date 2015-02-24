#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct in_addr addr;
    inet_aton("127.0.0.1", &addr);
    
    char *s = inet_ntoa(addr);
    printf("%s\n", s);
    
    return 0;
}