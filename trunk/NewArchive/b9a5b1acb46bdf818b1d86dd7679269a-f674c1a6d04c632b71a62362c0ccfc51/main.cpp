#define BOOST_SPIRIT_DEBUG

#include <vector>
#include <string>
#include <memory>
#include <map>
// PROJECT
//#include <boost/spirit.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp> // arguments, actors, values, references, ...
#include <boost/spirit/include/phoenix_operator.hpp> // if_else, bitwise, logical, arithmetic, ... operators
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_stl.hpp> // push_back
#include <boost/spirit/include/qi_symbols.hpp> // used in: columns_list
#include <boost/spirit/home/phoenix/bind/bind_function.hpp> // used in: aggregates_list
#include <boost/fusion/include/adapt_struct.hpp> // used in: filter options
#include <boost/spirit/include/phoenix_fusion.hpp> // used in : filter options
#include <boost/variant.hpp> // JSON value
#include <boost/bind.hpp> // used in: aggregate list
#include <boost/any.hpp> // used in: aggregate list, filter options
#include <boost/fusion/adapted/std_pair.hpp> // used in: filter options, aggregate list
#include <boost/fusion/adapted.hpp>
#include <boost/assign/list_of.hpp> // used in: DSU
#include <boost/algorithm/string/split.hpp> // used in: init DSU
#include <boost/algorithm/string.hpp> // -||-


enum sql_faggregate { AVG, COUNT, FIRST, LAST, MAX, MIN, SUM };
typedef std::string column_name_t;
typedef std::pair< column_name_t, sql_faggregate > column_and_aggregate;
typedef std::vector< column_and_aggregate > column_and_aggregate_container;
typedef std::wstring db_string;
typedef boost::variant< std::string, int, double, bool, column_and_aggregate > value_t;
typedef unsigned char uchar;
enum relation { GRT, LESS, GEQ, LEQ, EQ, NEQ };
enum logic { and_, or_ };
// filter
struct interval
{
    /*relation*/unsigned relation_with_min;
    value_t min_val;
	/*relation*/unsigned relation_with_max;
	value_t max_val;
	/*uchar*/unsigned concatenation_logic;
};
BOOST_FUSION_ADAPT_STRUCT(
	interval,
	(/*s2p::mms::relation*/unsigned, relation_with_min)
	(value_t, min_val)
	(/*s2p::mms::relation*/unsigned, relation_with_max)
	(value_t, max_val)
	(unsigned, concatenation_logic)
)
typedef std::vector<value_t> values_container;
typedef values_container set;
typedef boost::variant<interval,set> column_filter;
typedef std::pair<column_name_t,column_filter> column_to_filter;
typedef std::vector<column_to_filter> column_to_filter_container;

typedef std::vector< column_name_t > columns_container;
struct order_container
{
	columns_container columns;
	unsigned order;
};
enum order { asc, desc };
BOOST_FUSION_ADAPT_STRUCT(
	order_container,
	(columns_container, columns)
	(unsigned, order)
)
typedef unsigned long int offset_t; // At the maximum page size of 65536 bytes. The maximum size of a database file is 2147483646 pages.
									// A 140 terabytes database can hold no more than approximately 1e+13 rows, 
									// this translates into a maximum database size of approximately 1.4e+14 bytes (140 terabytes)
									// and then only if there are no indices and if each row contains very little data. 
typedef unsigned long int rows_cnt_t;
typedef std::pair< offset_t, rows_cnt_t > limit_pair;

//typedef std::vector< column_and_aggregate > faggregates_container;
struct select_clause_container
{
	bool distinct;
	columns_container columns;
	column_and_aggregate_container aggregates;
	column_to_filter_container filters;
	columns_container groups;
	column_to_filter_container group_filters;
	order_container order_options;
	limit_pair limit_options;
};
BOOST_FUSION_ADAPT_STRUCT(
	select_clause_container,
	(bool, distinct)
	(columns_container, columns)
	(column_and_aggregate_container, aggregates)
	(column_to_filter_container, filters)
	(columns_container, groups)
	(column_to_filter_container, group_filters)
	(order_container, order_options)
	(limit_pair, limit_options)
)

using namespace boost::spirit;
template<typename it, typename skipper>
struct action_parser : qi::grammar<it, std::string(), skipper>
{
	action_parser() : action_parser::base_type(action_parser_)
	{
		action_parser_ %= 
		'"'
		> qi::no_case[qi::lit("action")] //N.B.!!! no_case directive brings case-insensitive behavior in
		> '"'
		> qi::lit(':')
		> '"'
		> qi::no_case[qi::string("select") | qi::string("insert") | qi::string("update") | qi::string("delete")]
		> '"';
		BOOST_SPIRIT_DEBUG_NODE(action_parser_);
	}
private:
	qi::rule<it, std::string(), skipper> action_parser_;
};
template<typename it, typename skipper>
struct distinct_parser : qi::grammar<it, bool(), skipper>
{
	distinct_parser() : distinct_parser::base_type(distinct_parser_)
	{
		distinct_parser_ %= qi::lit('"') > qi::no_case["distinct"] > qi::lit('"') > qi::lit(':') > qi::bool_;
		BOOST_SPIRIT_DEBUG_NODE(distinct_parser_);
	}
private:
	qi::rule<it, bool(), skipper> distinct_parser_;
};
template <typename it, typename skipper = qi::space_type>
struct quoted_string_parser : qi::grammar<it, std::string(), skipper>
{
	quoted_string_parser() : quoted_string_parser::base_type(quoted_string)
	{
		using namespace qi;
		quoted_string %= lexeme['"' >> *~char_('"') > '"'];
		BOOST_SPIRIT_DEBUG_NODE(quoted_string);
	}
	qi::rule<it, std::string(), skipper> quoted_string;
};
template <typename it, typename skipper = qi::space_type>
struct columns_container_parser : qi::grammar<it, columns_container(), skipper>
{
    columns_container_parser() : columns_container_parser::base_type(columns_parser_)
    {
        using namespace qi;
        columns_parser_ %= '[' > quoted_string % ',' > ']';  
        BOOST_SPIRIT_DEBUG_NODE(columns_parser_);
    }
  private:
    qi::rule<it, columns_container(), qi::space_type> columns_parser_;
	quoted_string_parser<it,skipper> quoted_string;
};
template <typename it, typename skipper = qi::space_type>
struct columns_parser : qi::grammar<it, columns_container(), skipper>
{
    columns_parser() : columns_parser::base_type(columns_parser_)
    {
        using namespace qi;
        columns_parser_ %= '"' >> qi::no_case[qi::lit("columns")] > '"' > qi::lit(':') > columns_container_parser_;  
        BOOST_SPIRIT_DEBUG_NODE(columns_parser_);
    }
  private:
    qi::rule<it, columns_container(), qi::space_type> columns_parser_;
	quoted_string_parser<it,skipper> quoted_string;
	columns_container_parser<it,skipper> columns_container_parser_;
};
template <typename it, typename skipper = qi::space_type>
struct aggregate_parser : qi::grammar<it, column_and_aggregate(), skipper>
{
    aggregate_parser() : aggregate_parser::base_type(agg_pair)
    {
        using namespace qi;
        agg_pair %= quoted_string > ':' >> int_[_pass = (qi::_1 >= AVG && qi::_1 <= SUM)];
        BOOST_SPIRIT_DEBUG_NODE(agg_pair);
    }
  private:    
	qi::rule<it, column_and_aggregate(), skipper> agg_pair;
	quoted_string_parser<it,skipper> quoted_string;
};
template <typename it, typename skipper = qi::space_type>
struct aggregates_parser : qi::grammar<it, column_and_aggregate_container(), skipper>
{
    aggregates_parser() : aggregates_parser::base_type(aggregates_parser_)
    {
        using namespace qi;
        aggregates_parser_ = '"' >> qi::lit("aggregates") > '"' > ':' > '{' > aggr_pair % ',' > '}';
        BOOST_SPIRIT_DEBUG_NODE(aggregates_parser_);
    }
  private:    
	aggregate_parser<it, skipper> aggr_pair;
    qi::rule<it, column_and_aggregate_container(), skipper> aggregates_parser_;
};
template <typename it, typename skipper = qi::space_type>
struct value_parser : qi::grammar<it, value_t(), skipper>
{
    value_parser() : value_parser::base_type(value_parser_)
    {
        using namespace qi;
		value_parser_ = aggregate | quoted_string | /*(int_ >> !lit('.'))*/real_parser<double,strict_real_policies<double>>() | int_ | bool_;
        BOOST_SPIRIT_DEBUG_NODE(value_parser_);
    }
  private:
    qi::rule<it, value_t(), skipper> value_parser_;
	quoted_string_parser<it,skipper> quoted_string;
	aggregate_parser<it,skipper> aggregate;
};
template <typename it, typename skipper = qi::space_type>
struct filter_container_parser : qi::grammar<it, column_to_filter_container(), skipper>
{
    filter_container_parser() : filter_container_parser::base_type(flt_container_start)
    {
		using namespace qi;
		interval_parser %= '"' >> qi::no_case[qi::lit("interval")] >> '"' >> ':' 
				>> '{'
				>> qi::int_[qi::_pass = (qi::_1 >= GRT && qi::_1 <= NEQ)] >> ':' >> value >> ','
				>> qi::int_[qi::_pass = (qi::_1 >= GRT && qi::_1 <= NEQ)] >> ':' >> value >> ','
				>> '"' >> qi::no_case[qi::lit("logic")] >> '"' >> ':' >> qi::int_[qi::_pass = (qi::_1 >= and_ && qi::_1 <= or_)]
				>> '}';
		set_parser %= '"' > qi::no_case[qi::lit("in")] > '"' > ':' > qi::lit('[') > value % ',' > ']';
		col_filter %= interval_parser|set_parser;
		col_name_to_filter %= quoted_string > ':' > '{' > col_filter > '}';
		flt_container_start %= '{' > col_name_to_filter % ',' > '}';
    }
  private:
	qi::rule<it,column_to_filter_container(),skipper> flt_container_start;
	qi::rule<it,set(),skipper> set_parser;
	qi::rule<it,interval(),skipper> interval_parser;
	qi::rule<it,column_filter(),skipper> col_filter;
	qi::rule<it,column_to_filter(),skipper> col_name_to_filter;
	quoted_string_parser<it,skipper> quoted_string;
	value_parser<it,skipper> value;
};
template <typename it, typename skipper = qi::space_type>
struct filter_options_parser : qi::grammar<it, column_to_filter_container(), skipper>
{
	filter_options_parser() : filter_options_parser::base_type(filters_parser)
	{
		using namespace qi;
		filters_parser %= '"' >> qi::no_case[qi::lit("filter")] > '"' > ':' > flt_container;	
		BOOST_SPIRIT_DEBUG_NODE(filters_parser);
	}
private:
	qi::rule<it,column_to_filter_container(),skipper > filters_parser;
	filter_container_parser<it,skipper> flt_container;
};
template <typename it, typename skipper = qi::space_type>
struct groups_parser : qi::grammar<it, columns_container(), skipper>
{
    groups_parser() : groups_parser::base_type(groups)
    {
		using namespace qi;
		groups %= '"' >> qi::lit("groups") > '"' > ':' > columns_container_parser_;
        BOOST_SPIRIT_DEBUG_NODE(groups);
    }
  private:
	  columns_container_parser<it,skipper> columns_container_parser_;
	  qi::rule<it,columns_container(),skipper > groups;
};
template <typename it, typename skipper = qi::space_type>
struct group_filter : qi::grammar<it, column_to_filter_container(), skipper>
{
    group_filter() : group_filter::base_type(group_filter_psr_start)
    {
    	using namespace qi;
		group_filter_psr_start %= '"' >> qi::lit("group_filter") > '"' > ':' > flt_container;
        BOOST_SPIRIT_DEBUG_NODE(group_filter_psr_start);
    }
  private:
	  qi::rule<it,column_to_filter_container(),skipper > group_filter_psr_start;
	  filter_container_parser<it,skipper> flt_container;
};
template <typename it, typename skipper = qi::space_type>
struct order_options_parser : qi::grammar<it, order_container(), skipper>
{
    order_options_parser() : order_options_parser::base_type(order_options)
    {
		using namespace qi;
		order_options %= '"' >> qi::lit("order") > '"' > ':' > qi::lit('[') > columns_container_parser_ > ',' > qi::int_[qi::_pass = (qi::_1 >= asc && qi::_1 <= desc)] > ']';
        BOOST_SPIRIT_DEBUG_NODE(order_options);
    }
  private:
	  qi::rule<it,order_container(),skipper> order_options;
	  quoted_string_parser<it,skipper> quoted_string;
	  columns_container_parser<it,skipper> columns_container_parser_;
};
template <typename it, typename skipper = qi::space_type>
struct limit_parser : qi::grammar<it, limit_pair(), skipper>
{
    limit_parser() : limit_parser::base_type(limit)
    {
		using namespace qi;
		limit %= '"' >> qi::lit("limit") > '"' > ':' > '[' > qi::int_ > ',' > qi::int_ > ']';
        BOOST_SPIRIT_DEBUG_NODE(limit);
    }
  private:
	  qi::rule<it,limit_pair(),skipper> limit;
};

template <typename it, typename skipper = qi::space_type>
struct select_parser : qi::grammar<it, select_clause_container(), skipper>
{
	select_parser() : select_parser::base_type(select_psr)
	{
		using namespace ::boost::spirit;
		using namespace qi;
		select_psr %= 
			'[' 
				> qi::omit[action_psr] 
				> ','
				> distinct_psr
				> ','
				> columns_psr 
				> ','
				> (aggrs_psr > ',' | attr(column_and_aggregate_container()))
				> (filter_psr > ',' | attr(column_to_filter_container()))
				> (grp_psr > ',' | attr(columns_container()))
				> (grp_filter_psr > ',' | attr(column_to_filter_container()))
				> (order_psr > ',' | attr(order_container()))
				> (limit_psr | attr(limit_pair())) > 
			']';
		BOOST_SPIRIT_DEBUG_NODE(select_psr);
	}
private:
	qi::rule<it,select_clause_container(),skipper> select_psr;
	action_parser<it,skipper> action_psr;
	distinct_parser<it,skipper> distinct_psr;
	columns_parser<it,skipper> columns_psr;
	aggregates_parser<it,skipper> aggrs_psr;
	filter_options_parser<it,skipper> filter_psr;
	groups_parser<it,skipper> grp_psr;
	group_filter<it,skipper> grp_filter_psr;
	order_options_parser<it,skipper> order_psr;
	limit_parser<it,skipper> limit_psr;
};

bool parse_select_clause(std::string const& select_clause)
{
    auto f(begin(select_clause)), l(end(select_clause));
    static const select_parser<std::string::const_iterator> p;

    bool ok = qi::phrase_parse(
            f, l,
            p,
            qi::space);

    return ok && (f == l);
}

bool select_clause_basic_test()
{
    /////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// SELECT PARSER
	bool ok = 1;
	try
	{
		ok = parse_select_clause("[\
									\"action\" : \"select\",\
									\"distinct\" : false,\
									\"columns\" : [ \"bosom\", \"Angelina\", \"Angela\", \"Mary\"],\
									\"aggregates\" : { \"Angelina\" : 3, \"Angela\" : 4, \"Mary\" : 0 },\
									\"filter\" : {\
													\"hip\" : { \"interval\" : { 2 : 87, 3 : 91.5, \"logic\" : 1 } },\
													\"waist\" : { \"in\" : [57.5, 62] }\
												 },\
									\"groups\" : [ \"bosom\" ],\
									\"group_filter\" : { \"bosom\" : { \"interval\" : { 2 : 87, 3 : 91.5, \"logic\" : 1 } } },\
									\"order\" : [ [ \"bosom\" ], 0 ],\
									\"limit\" : [ 0, 100 ]\
								]");
		ok = parse_select_clause("[\
									\"action\" : \"select\",\
									\"distinct\" : false,\
									\"columns\" : [ \"bosom\", \"Angelina\", \"Angela\", \"Mary\"],\
									\"aggregates\" : { \"Angelina\" : 3, \"Angela\" : 4, \"Mary\" : 0 },\
									\"filter\" : {\
													\"hip\" : { \"interval\" : { 2 : 87, 3 : 91.5, \"logic\" : 1 } },\
													\"waist\" : { \"in\" : [57.5, 62] }\
												 },\
									\"groups\" : [ \"bosom\" ],\
									\"order\" : [ [ \"bosom\" ], 0 ],\
									\"limit\" : [ 0, 100 ]\
								]");
	}
	catch ( std::exception & e )
	{
		std::cout << e.what();
	}
	return ok;
}
int main()
{
    /////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// INITIALIZATION OF DSU
	//set_default_tables("device\tmodule\tcountry\tdominant_leg\tdominant_arm");
	bool ok = 0;
	//ok = subparsers_basic_test();
	ok = select_clause_basic_test();
    return ok? 0 : 255;
}
