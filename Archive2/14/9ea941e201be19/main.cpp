#include <map>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

struct IDbQuery;
struct IFactory {};

template<typename T> 
IDbQuery * createInstance( boost::asio::ip::tcp::socket & s,const boost::property_tree::ptree & ptree ) 
{
    return 0;
}

struct IDbQueryFactory {

    typedef boost::asio::ip::tcp::socket Sock;
	typedef boost::property_tree::ptree PTree;
    typedef std::map<std::string, IDbQuery*(*)(Sock &, const PTree &)> Map;
	static Map * getMap() {static Map map; return &map;}

};

template <typename RegT>
class IDbQueryRegister : public IFactory
{
public:
    IDbQueryRegister(const std::string & sRegTypeName)
    {
        IDbQueryFactory::getMap()->insert( 
            std::make_pair(
                sRegTypeName, 
                &createInstance<RegT>
            )
        );
    }
};

int main() {
	IDbQueryRegister<int> r("TEST");
    std::cout << "Success\n";
}