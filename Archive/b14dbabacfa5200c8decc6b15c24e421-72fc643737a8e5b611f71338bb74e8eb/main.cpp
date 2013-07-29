#include <iostream>
#include <string>
#include <map>

#include <boost/variant.hpp>

typedef boost::make_recursive_variant<double, int, std::string, std::map<std::string, boost::recursive_variant_> >::type ConfigVariant;

struct printer : boost::static_visitor<>
{
    void operator()(int val) const
	{
		std::cout << val;
	}
	void operator()(double val) const
	{
		std::cout << val;
	}
	void operator()(const std::string& val) const
	{
		std::cout << val;
	}
	void operator()(const std::map<std::string,ConfigVariant>& val) const
	{
		std::cout << "map_of{ ";
		for(std::map<std::string,ConfigVariant>::const_iterator it=val.begin(),end=val.end(); it!=end; ++it)
		{
			boost::apply_visitor(*this,it->second);
			std::cout << " ";
		}
		std::cout << "}";	
	}
};


int main()
{
	ConfigVariant intconf=1;
	ConfigVariant doubleconf=1.2;
	ConfigVariant stringconf="conf";
	std::map<std::string, ConfigVariant> mapconf, mapconf2;
	mapconf["int"]=intconf;
	mapconf["string"]=stringconf;
	mapconf2["map"]=mapconf;
	mapconf2["double2"]=doubleconf;
	ConfigVariant visitable=mapconf2;
	
	boost::apply_visitor(printer(), visitable);
	std::cout << std::endl;
}