#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>
#include <vector>

//namespace std 
//  { 
    // We handle size_t, ptrdiff_t, and nullptr_t in c++config.h. 
 #ifndef __clang__ 
    using ::max_align_t; 
 #endif 
//  } 

namespace qi = boost::spirit::qi;

namespace ast
{
    typedef std::string				  String ;
	typedef std::vector<String>		  VEC ;
	// SQL statement type mapped structures
	struct SelectStatement{
		VEC Columns ;
		VEC GroupBy ;
		VEC OrderBY  ;
		String tableName ;
		String whereClause ;
	} ;

	// for debug
	static inline std::ostream& operator<<(std::ostream& os, SelectStatement const& o) 
	{
		os << "table_name[ " << o.tableName<< " ]\n "
			      << "columns[ " ;
		VEC::const_iterator it  = o.Columns.begin() ;
		VEC::const_iterator ite = o.Columns.end() ;
		for( ;it != ite ; ++it)	{ os<<*it ; if(it+1 != ite) os<< ", " ; else os<<" ]" ; }

		os<<"\n wherestring [ " << o.whereClause << " ]";

		os<<"\n group by[ " ;
		it  = o.GroupBy.begin() ;
		ite = o.GroupBy.end() ;
		for( ;it != ite ; ++it)	{ os<<*it ; if(it+1 != ite) os<< ", " ; else os<<" ]" ; }

		os<<"\n order by[ " ;
		it  = o.OrderBY.begin() ;
		ite = o.OrderBY.end() ;
		for( ;it != ite ; ++it)	{ os<<*it ; if(it+1 != ite) os<< ", " ; else os<<" ]" ; }

		return os ;
	}
}

using namespace ast;

BOOST_FUSION_ADAPT_STRUCT(	SelectStatement,
		(VEC,				SelectStatement::Columns)
		(String,			SelectStatement::tableName)
		(String,			SelectStatement::whereClause)
		(VEC,				SelectStatement::GroupBy)
		(VEC,				SelectStatement::OrderBY)
		)



template <typename It, typename Skipper = qi::space_type>
struct parser : qi::grammar<It, SelectStatement(), Skipper>
{
	parser() : parser::base_type(start)
	{
		using namespace qi ;

		ident			= +char_("a-zA-Z0-9_*") ;
		where_			= no_case["where"] ;
		sel_			= no_case["select"] ;
		from_			= no_case["from"] ;
		grp_			= no_case["group"] ;
		order_			= no_case["order"] ;
		by_				= no_case["by"] ;

		// Actual values in Update Statement

		columnlist		=  sel_  >> ident >> *(',' >> ident) ;

		table			=  from_ >> ident ;

		whereStr		=  -(where_ >> *(char_ - (grp_ | order_ | lit(';')) ) ) ;

		//- ( (grp_  >> by_) | (order_ >> by_) ) >> ';' ;
		//- ( (order_ >> by_) | (grp_  >> by_) ) >> ';' ;
		
		grpBylist		=  -( (grp_  >> by_  >> (ident % ',') ) >> -( (order_ >> by_)|char_(';') ) ) ;
	
		ordBylist		=  -( (order_ >> by_  >> (ident % ',') ) >> -( (grp_ >> by_) |char_(';') ) ) ;

		//-( (grpBylist | (ordBylist >> dir )) | ((ordBylist >> dir ) | grpBylist ) ) >> ';' ;
		-( (grpBylist >> ordBylist) | (ordBylist >> grpBylist ) ) >> ';' ;
		

		//start			=  columnlist >> table >> whereStr >> -((grpBylist >> ordBylist) | (ordBylist >> grpBylist) );
		start			=  columnlist >> table >> whereStr >> grpBylist >> ordBylist ;
	
		BOOST_SPIRIT_DEBUG_NODES(
				/*(columnlist)(table)(whereStr)*/(grpBylist) (ordBylist)//(start)
				)
	}
	private:
		qi::rule<It>								where_, sel_, from_, grp_, order_, by_ ;
		qi::rule<It, String()>						ident ;
		qi::rule<It, String(),			Skipper>	table, whereStr ;
		qi::rule<It, VEC(),				Skipper>	columnlist, grpBylist, ordBylist ;
		qi::rule<It, SelectStatement(),	Skipper>	start ;
	
};


template <typename C, typename Skipper>
bool ParseS(const C& input, const Skipper& skipper)
{
	auto f(std::begin(input)), l(std::end(input));

	parser<decltype(f), Skipper> p;
	SelectStatement data;

	try
	{
		bool ok = qi::phrase_parse(f, l, p, skipper, data);
		if (ok)
		{
			std::cout << "Success\n";
			std::cout << data << "\n";
		}
		else    std::cerr << "Failed!! " ;
		if (f!=l)
			std::cout << "\nTrailing unparsed: '" << std::string(f,l) << "'\n";
		return ok;
	}
	catch (const qi::expectation_failure<decltype(f)>& e)
	{
		std::string frag(e.first, e.last);
		std::cerr << e.what() << "'" << frag << "'\n";
	}
	return false;
}

int main()
{
	/// Trying to parse the select with group by and order by clause ... 
	/// they can exist in any order in the statement 
	const std::string input = "select \n* from employee \nwhere id='1234' order by tenure, sal group by sal, age;";

	// should be able to get group by in grplist and order by in a map<filed, asc/desc as bool>
	// const std::string input = "select \n* from employee \nwhere id='1234'  group by sal, age order by tenure desc, sal asc;";
																		  

	bool ok = ParseS(input, qi::space);
	std::cout << input << "\n";
	return ok ? 0 : 255;
}



////////  current out put shows  ///////////////
//<grpBylist>
//  <try> order by tenure, sa</try>
//  <success> order by tenure, sa</success>
//  <attributes>[[]]</attributes>
//</grpBylist>
//<ordBylist>
//  <try> order by tenure, sa</try>
//  <success> sal, age;</success>
//  <attributes>[[[t, e, n, u, r, e], [s, a, l], []]]</attributes>
//</ordBylist>
//Success
//table_name[ employee ]
// columns[ * ]
// wherestring [ id='1234' ]
// group by[
// order by[ tenure, sal,  ]
//
//Trailing unparsed: 'sal, age;'
//select
//* from employee
//where id='1234' order by tenure, sal group by sal, age;

////////////////////////////////////////////////
