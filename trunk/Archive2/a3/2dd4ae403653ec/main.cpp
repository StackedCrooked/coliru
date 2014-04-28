#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <random>
#include <stdexcept>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

using std::cout;
using std::endl;

class MyRng {
    std::mt19937 _rng{ 20140422 };
    std::uniform_int_distribution<uint64_t> _uint64_dist;
public:
    uint64_t operator()() { return _uint64_dist( _rng ); }
};

struct IPv6 {
    uint64_t _lo;
    uint64_t _hi;
    void set_random( MyRng & r ) {
        _lo = r();
        _hi = r();
    }
};

struct Object {
    IPv6 _ip;
};

struct IPv6PtrPair {
    IPv6 _key;
    Object const * _ptr;
};

class IPv6Map {
    std::vector< IPv6PtrPair > _map;
    public:
    void add( IPv6 const & ip, Object const & obj ) {
        _map.push_back( IPv6PtrPair{ ip, & obj } );
    }
};

int main() {
    MyRng rng;
    std::vector< IPv6 > _ip( 100 );
    IPv6Map _obj;
    for(auto & it : _ip) it.set_random( rng );
    for(auto & it : _ip) _obj.push_back( { it._ip{ ~_ip_vset_random( rng );
	return 0;
}