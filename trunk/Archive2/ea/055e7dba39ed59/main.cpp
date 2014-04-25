#include <iostream>
#include <string>
#include "boost/property_tree/json_parser.hpp"

class json
{
public:
    json (std::string filename)
    {
		std::ifstream ifs(filename);
		boost::property_tree::read_json(ifs, m_data);
	}
	template<class T> T getData(std::string key)
	{
		return m_data.get<T>(key);
	}
private:
	std::string m_contents;
	boost::property_tree::ptree m_data;
};

int main()
{
	json doc("json.txt");
    for (auto key : { "assetType", "assetName", "assetFile", "charMap" })
        std::cout << doc.getData<std::string>(key) << "\n";
}
