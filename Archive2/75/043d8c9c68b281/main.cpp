#include <iostream>
#include <string>
#include <vector>

#include <boost/unordered_set.hpp>
#include <boost/functional/hash.hpp>

//ip type
enum eIpType { ipv4, ipv6 , unkown_ip_type };

//ip address 
struct in6_address
{
    union 
	{
		short			u6_addr8[16];
		int		u6_addr16[8];
		long		u6_addr32[4];
	} in6_u;

	friend bool operator==(const in6_address& a1, const in6_address& a2){
		return (a1.in6_u.u6_addr32[0] == a1.in6_u.u6_addr32[0] &&
			   a1.in6_u.u6_addr32[1] == a1.in6_u.u6_addr32[1] &&
			   a1.in6_u.u6_addr32[2] == a1.in6_u.u6_addr32[2] &&
			   a1.in6_u.u6_addr32[3] == a1.in6_u.u6_addr32[3]);
	}

	friend bool operator>=(const in6_address& a1, const in6_address& a2){
		unsigned int nval = memcmp(a1.in6_u.u6_addr8 , a2.in6_u.u6_addr8 , sizeof(in6_address));
		if(nval >= 0 )
			return true;
		return false;
	}
	friend bool operator<(const in6_address& a1, const in6_address& a2){
		unsigned int nval = memcmp(a1.in6_u.u6_addr8 , a2.in6_u.u6_addr8 , sizeof(in6_address));
		if(nval < 0 )
			return true;
		return false;
	}
};

class IpAddress
{

public:
    int m_IpType; //values are value of enum eIpType
				   //RU8 would have been ok but we don't want rubbish in padding
	in6_address m_Address;


//Hash function for boost hash
std::size_t hash_value(const IpAddress &addr)
{
    std::size_t seed = 0;
	boost::hash_combine(seed, addr.m_IpType);
	for (int i=0; i<4; i++)
		boost::hash_combine(seed, addr.m_Address.in6_u.u6_addr32[i]);
	return seed;
}

/// Compare two addresses for equality.
bool operator==(const IpAddress& a1)
{
    return memcmp(&a1.m_Address, &m_Address,sizeof(in6_address)) == 0;
}

};

int main()
{
    
    boost::unordered_set< std::pair<IpAddress, IpAddress> > myset;
    
    IpAddress a;
    IpAddress b;
    myset.insert(std::make_pair(a,b));
    
    std::cout << "hello" << std::endl;
}
