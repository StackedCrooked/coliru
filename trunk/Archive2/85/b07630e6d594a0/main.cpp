#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


std::string ip2string(unsigned long ip)
{
   std::ostringstream s;
   s << (ip >> 24) << "."
      << ((ip >> 16) & 0xFF) << "."
      << ((ip >> 8) & 0xFF) << "."
      << (ip & 0xFF);

   return s.str();
}

unsigned long string2ip(std::string s)
{
   in_addr addr;
   if (!inet_aton(s.c_str(), &addr))
      throw InvalidIp(s);
   return ntohl(addr.s_addr);
}

#include <netdb.h>

std::string host2ipString(std::string host) // TODO: Turn this into a useful function. read man:getaddrinfo
{
   addrinfo * addrinfos;
   int ret = getaddrinfo(host.c_str(), NULL, NULL, &addrinfos);


   for (addrinfo const * i = addrinfos; i; i = i->ai_next)
   {
      switch (i->ai_family)
      {
      case AF_INET:
      {
         sockaddr_in const * addr = reinterpret_cast<sockaddr_in const *>(i->ai_addr);
         printf("IPv4: %s\n", ip2string(addr->sin_addr.s_addr).c_str());
         break;
      }
      case AF_INET6:
         printf("IPv6 ... TODO\n");
      }
   }

   int foo = 123;

   freeaddrinfo(addrinfos);
}
