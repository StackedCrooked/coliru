#include <string>
#include <map>

template< class btype >
class registry {
    typedef std::map< std::string, int > regmap;
	static regmap creators;
};

template< class btype >
std::map< std::string, int > registry< btype >::creators;
//registry< btype >::regmap registry< btype >::creators;

int main(){
}