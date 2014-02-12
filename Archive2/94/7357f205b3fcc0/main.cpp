#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <queue>
#include <memory>
#include <string>
#include <boost/numeric/interval.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/qi.hpp>

template <typename T>
void myPrint(T t){
    std::cout << "parsed: " << t << std::endl;
}

template <>
void myPrint<char>(char t){
    std::cout << "parsed(char): " << t << std::endl;
}

template <typename Iterator>
void parseWord(Iterator first, Iterator last){
    using boost::spirit::qi::double_;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::ascii::space;
    using boost::spirit::qi::parse;
    phrase_parse(
        first,
        last,
        *(char_[&myPrint<char>] >> *double_[&myPrint<double>]),
        space
    );
}


int main(){
    auto line = std::string{" G01 X 100.2 Y     Z200.2"};
    parseWord(std::begin(line), std::end(line));
}
