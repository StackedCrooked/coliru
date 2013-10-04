#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

char* getIPAddress(char* src)
{
    struct ifaddrs *ifaddr, *ifa;
    int family;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;
              
        family = ifa->ifa_addr->sa_family;
        if (0 == strcmp(ifa->ifa_name, "eth0" ) && (family == AF_INET)) { // v4
            inet_ntop(
                AF_INET,
                &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr,
                src,
                sizeof(struct sockaddr_in)
            );
            
            break;
        }
    }

    freeifaddrs(ifaddr);
    return src;
}
 
int main(int argc, char** argv)
{
    char ip[INET_ADDRSTRLEN];
    puts(getIPAddress(ip));
}

