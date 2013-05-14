#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <boost/bind.hpp>

using namespace std;

class A{
public:
    A( const std::string& key )
    : key( key ) {}

    std::string getKey(){ return key; }
private:
    std::string key;
};

int main(int argc, const char *argv[]) {

    map<string, string> mp;
    vector<A> vec;
    find_if( vec.begin(), vec.end(), boost::bind( &map<string, string>::count, &mp, boost::bind( &A::getKey, _1 ) )) != 0);
    return 0;
}