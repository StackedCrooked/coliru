

// name = tabata2
// readyTime = 18*60 + 0;
// relaxTime = 8*60 + 0;

// def ::= int_ >> '˚' >> string_ >> '˚' >> int_ >> '˚' >> int_


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;


template <typename Iterator>
bool parse_training(Iterator first, Iterator last)
{
    using qi::double_;
    using qi::int_;
    using qi::phrase_parse;
    using ascii::space;

    int readyTime = 0;
    // struct simpleTraining
    // {
    //     std::string name;
    //     std::string surname;
    //     double salary;
    // };

    typedef tuple<string, string> simple_training;
    typedef tuple<int, int> dynamic_setting;

    

// 2,tabata2,18,0,8,0,20,0,10,0,10,0,0
    // 


    qi::rule<Iterator, string(), ascii::space_type> trainingNameDef;
    qi::rule<Iterator, simple_training(), ascii::space_type> trainingDef;

    trainingNameDef %= qi::lexeme['"' >> +(qi::char_ - '"') >> '"'];
    // trainingDef %= (qi::int_ >> "," >> trainingNameDef);
    trainingDef %= (trainingNameDef >> ',' >> trainingNameDef);

    // qi::rule<Iterator, simple_training(), ascii::space_type> trainingDef = qi::int_ >> "," >> trainingNameDef;
    // qi::rule<Iterator, dynamic_setting(), ascii::space_type> dynamicDef = qi::int_  >> "," >> qi::int_;
    // qi::rule<Iterator, int(), ascii::space_type> intervalDef = (qi::int_ >> "," >> qi::int_) [qi::_val = qi::_1 * 60 + qi::_2];
    
    typedef tuple<simple_training, int, int, int, int, int, dynamic_setting> complete_training;
    auto gramma = trainingDef;//>> "," >> intervalDef  >> "," >> intervalDef >> "," >> intervalDef >> "," >> intervalDef >> "," >> qi::int_ >> "," >> dynamicDef;
    
    // complete_training training;
    // string name;
    simple_training simpleTraining;

    bool r = phrase_parse(
        first,                          /*< start iterator >*/
        last,                           /*< end iterator >*/
        gramma,
        space,
        simpleTraining
    );
    if (!r || first != last)
    {
    // fail if we did not get a full match
        throw runtime_error("parsing failed");
    }
    // simple_training simple = std::get<0>(training);
    // int ready = std::get<1>(training);
    // int roundTime = std::get<2>(training);
    // int relax = std::get<3>(training);
    // int rest = std::get<4>(training);
    // int rounds = std::get<5>(training);
    // dynamic_setting dynamic = std::get<6>(training);
    cout << "training: " << std::get<0>(simpleTraining) << "-" <<  std::get<1>(simpleTraining) << endl;// << "-" << ready << "-" << roundTime << "-" << relax 
    // << "-" << rest << "-" << rounds << "-" << std::get<0>(dynamic) << "-" << std::get<1>(dynamic) <<  endl;
    // cout << "training: " << name << endl;
    return r;
}


int main()
{
    
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;

    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        if (parse_training(str.begin(), str.end()))
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " Parses OK: " << std::endl;
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    

// std::string input("1234, 6543, 42");
//    std::string::const_iterator begin = input.begin(), end = input.end();

//    qi::rule<std::string::const_iterator,
//       int(int),                    //output (_val) and input (_r1)
//       qi::locals<int>,             //local int (_a)
//       ascii::space_type>

//       intRule =
//             qi::int_[qi::_a = qi::_1]             //local = x1
//          >> ","
//          >> qi::int_[qi::_a += qi::_1]            //local = x1 + x2
//          >> ","
//          >> qi::int_
//             [
//                qi::_val = qi::_a*qi::_1 + qi::_r1 //output = local*x3 + x0
//             ];

//    int ruleValue, x0 = 10;
//    qi::phrase_parse(begin, end, intRule(x0), ascii::space, ruleValue);
   // std::cout << "rule value: " << ruleValue << std::endl;
    return 0;
}
