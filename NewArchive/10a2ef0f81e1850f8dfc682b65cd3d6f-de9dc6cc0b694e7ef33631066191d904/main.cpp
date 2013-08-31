#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include <list>
#include <vector>
#include <map>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/adapted/std_tuple.hpp> 

#include <boost/spirit/include/qi.hpp>

#include <boost/variant.hpp>

namespace qi=boost::spirit::qi;

struct normal_struct
{
    int integer;
	double real;
};

struct struct_with_single_element_container
{
	std::vector<int> cont;
};

BOOST_FUSION_ADAPT_STRUCT(
	normal_struct,
	(int, integer)
	(double, real)
)

BOOST_FUSION_ADAPT_STRUCT(
	struct_with_single_element_container,
	(std::vector<int>, cont)
)

struct accumulator
{
	accumulator(): total(){}
	int total;
};

namespace boost{ namespace spirit{ namespace traits
{
	template<>
	struct is_container<accumulator> : boost::mpl::true_
	{};
	
	template<>
	struct container_value<accumulator>
	{
		typedef int type;
	};
	
	template<>
	struct push_back_container<accumulator,int>
	{
		static bool call(accumulator& c, int val)
		{
			c.total+=val;
			return true;
		}
	};
}}}

struct distributor
{
	distributor():ints(),strings(){}
	std::vector<int> ints;
	std::vector<std::string> strings;
};

namespace boost{ namespace spirit{ namespace traits
{
	template<>
	struct is_container<distributor> : boost::mpl::true_
	{};
	
	template<>
	struct container_value<distributor>
	{
		typedef boost::variant<int,std::string> type;
	};
	
	template<>
	struct push_back_container<distributor,int>
	{
		static bool call(distributor& c, int val)
		{
			c.ints.push_back(val);
			return true;
		}
	};
	
	template<>
	struct push_back_container<distributor,std::string>
	{
		static bool call(distributor& c, std::string const& val)
		{
			c.strings.push_back(val);
			return true;
		}
	};
}}}


int main()
{
	{
		std::pair<int,double> parsed;
		qi::rule<std::string::const_iterator, std::pair<int,double>()> rule = 
					qi::int_ >> qi::lit(',') >> qi::double_;
		std::string test="1,2.5";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "First: " << parsed.first << ", Second: " << parsed.second << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		std::tuple<int,std::string,double> parsed;
		qi::rule<std::string::const_iterator, std::tuple<int,std::string,double>()> rule = 
					qi::int_ >> qi::lit(',') >> +~qi::char_(',') >> qi::lit(',') >> qi::double_;
		std::string test="1,abc,2.5";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "get<0>: " << std::get<0>(parsed) << ", get<1>: " << std::get<1>(parsed) << ", get<2>: " << std::get<2>(parsed) << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		normal_struct parsed;
		qi::rule<std::string::const_iterator, normal_struct()> rule = 
					qi::int_ >> qi::lit(',') >> qi::double_;
		std::string test="1,2.5";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "integer: " << parsed.integer << ", real: " << parsed.real << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		struct_with_single_element_container parsed;
		//there is a problem when you have a struct with a single element container, the workaround is simply adding qi::eps to the rule
		qi::rule<std::string::const_iterator, struct_with_single_element_container()> rule = 
					qi::eps >> qi::int_%qi::lit(','); 
		std::string test="1,2";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "[0]: " << parsed.cont[0] << ", [1]: " << parsed.cont[1] << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		std::list<int> parsed;
		qi::rule<std::string::const_iterator, std::list<int>()> rule = 
					qi::int_%qi::lit(',');
		std::string test="1,2";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "front: " << parsed.front() << ", back: " << parsed.back() << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		std::map<double,int> parsed;
		// qi::rule<std::string::const_iterator, std::pair<double,int>()> pair_rule = 
					// qi::double_ >> qi::lit('=') >> qi::int_;
		// qi::rule<std::string::const_iterator, std::map<double,int>()> rule = 
					// pair_rule%qi::lit(',');
		qi::rule<std::string::const_iterator, std::map<double,int>()> rule =
					(qi::double_ >> qi::lit('=') >> qi::int_)%qi::lit(',');
		std::string test="2.5=1,3.5=2";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "map[2.5]: " << parsed[2.5] << ", map[3.5]: " << parsed[3.5] << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		accumulator parsed;
		qi::rule<std::string::const_iterator, accumulator()> rule = 
					qi::int_%qi::lit(',');
		std::string test="1,2,3";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "total: " << parsed.total << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
	{
		distributor parsed;
		qi::rule<std::string::const_iterator, std::string()> string_rule = 
					+~qi::char_(',');
		qi::rule<std::string::const_iterator, distributor()> rule = 
					(qi::int_ | string_rule)%qi::lit(',');
		std::string test="abc,1,2,def,ghi,3,jkl";
		std::string::const_iterator iter=test.begin(), end=test.end();
		bool result = qi::parse(iter,end,rule,parsed);
		if(result && iter==end)
		{
			std::cout << "Success." << std::endl;
			std::cout << "ints" << std::endl;
			for(auto val: parsed.ints)
				std::cout << val << std::endl;
			std::cout << "strings" << std::endl;
			for(const auto& val: parsed.strings)
				std::cout << val << std::endl;
		}
		else
		{
			std::cout << "Failure." << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}
	
}