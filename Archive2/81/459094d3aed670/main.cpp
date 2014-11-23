#define BOOST_SPIRIT_USE_PHOENIX_V3
#define DATAPAIR_PAIR

#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/mpl/bool.hpp>
#include <map>
#if !defined(DATAPAIR_PAIR)
#include <vector>
#endif


static const char g_data[] = "1;2\n=1200\n3;4\n5;6\n";
typedef std::string DataTypeFirst;

#if defined(DATAPAIR_PAIR)
typedef int DataTypeSecond;//CHANGED this just to check that it works
typedef std::pair<DataTypeFirst, DataTypeSecond> DataPair;
typedef std::map<DataTypeFirst, DataTypeSecond> DataMap;
#else
typedef std::vector<DataTypeFirst> DataPair;
typedef std::map<DataTypeFirst, DataTypeFirst> DataMap;
#endif

struct MyContainer {
    DataMap data;
    double number;
};

namespace boost { namespace spirit { namespace traits {
    template<> struct is_container<MyContainer> : boost::mpl::true_ {};

    template<>
    struct container_value<MyContainer> {
        typedef boost::variant<double, DataPair> type;
    };

    template <>
    struct push_back_container<MyContainer, double> {
        static bool call ( MyContainer& parContainer, double parValue ) {
            parContainer.number = parValue;
            return true;
        }
    };

    template <>
    struct push_back_container<MyContainer, DataPair> {
        static bool call ( MyContainer& parContainer, const DataPair& parValue ) {
#if defined(DATAPAIR_PAIR)
            parContainer.data[parValue.first] = parValue.second;
#else
            parContainer.data[parValue[0]] = parValue[1];
#endif
            return true;
        }
    };
    
    //ADDED
    template <>
    struct push_back_container<MyContainer, boost::variant<double,DataPair> > {
        struct push_back_visitor:boost::static_visitor<bool>
        {
            MyContainer& cont;
            push_back_visitor(MyContainer& cont_):cont(cont_){}
            
            template <typename T>
            bool operator()(const T& val) const
            {
                return push_back_container<MyContainer,T>::call(cont,val);
            }
            
            
        };
        static bool call ( MyContainer& parContainer, const boost::variant<double,DataPair>& parValue) {
            return boost::apply_visitor(push_back_visitor(parContainer),parValue);
        }
    };
            
} } }

template <typename Iterator>
struct TestGrammar : boost::spirit::qi::grammar<Iterator, MyContainer()> {

    TestGrammar ( void );
    boost::spirit::qi::rule<Iterator, MyContainer()> start;
    boost::spirit::qi::rule<Iterator, DataPair()> data;
    boost::spirit::qi::rule<Iterator, double()> num;
};

template <typename Iterator>
TestGrammar<Iterator>::TestGrammar() :
    TestGrammar::base_type(start)
{
    using boost::spirit::qi::alnum;
    using boost::spirit::qi::lit;
    using boost::spirit::ascii::char_;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::int_;
    using boost::spirit::qi::eol;
    using boost::spirit::qi::eoi;

    start %= *((num | data) >> (eol | eoi));
    data = +alnum >> lit(";") >> int_;
    num = '=' >> double_;
}

int main() {
    std::cout << "Parsing data:\n" << g_data << "\n";

    TestGrammar<const char*> gramm;
    MyContainer result;
    boost::spirit::qi::parse(static_cast<const char*>(g_data),
        g_data + sizeof(g_data) / sizeof(g_data[0]) - 1,
        gramm,
        result
    );
    std::cout << "Parsed data:\n";
    std::cout << "Result: " << result.number << "\n";
    for (const auto& p : result.data) {
        std::cout << p.first << " = " << p.second << '\n';
    }

    return 0;
}
