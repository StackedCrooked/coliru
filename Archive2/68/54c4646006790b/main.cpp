#include <iostream>
#include <string>

#include "boost/property_tree/json_parser.hpp"

class json
{
public:
    json ( std::string filename )
	{
		std::stringstream ss("{\"assetType\" : \"font\",\"assetName\" : \"default font\", \"assetFile\" : \"dat/assets/dfont.png\", \"charMap\" : \"`1234567890-=~!@#$%^&*()_+qwertyuiop[]\\\\QWERTYUIOP{}|asdfghjkl;'ASDFGHJKL:\\\"zxcvbnm,./ZXCVBNM<>? \" }");
		boost::property_tree::read_json(ss, m_data);
	}
	template <class T> T getData ( std::string key )
	{
		return m_data.get<T> ( key );
	}
private:
	std::string m_contents;
	boost::property_tree::ptree m_data;
};

int main()
{
	json InstanceofJSON("json.txt");
	std::string a = InstanceofJSON.getData<std::string> ( "assetType" );
	std::string b = InstanceofJSON.getData<std::string> ( "assetName" );
	std::string c = InstanceofJSON.getData<std::string> ( "assetFile" );
	std::string d = InstanceofJSON.getData<std::string> ( "charMap" );
	std::cout<<a<<'\n'<<b<<'\n'<<c<<'\n'<<d<<'\n';
};