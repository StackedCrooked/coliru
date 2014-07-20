#include <string>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/adapted.hpp>

int main()
{
    namespace spirit = boost::spirit;
    namespace qi = spirit::qi;
    namespace phoenix = boost::phoenix;

    using qi::rule;
    using qi::int_;
    using qi::_1;
    using qi::_val;
    using qi::phrase_parse;
    using boost::shared_ptr;
    using boost::make_shared;

    shared_ptr<int> x = make_shared<int>(123);

    std::cout << *x << std::endl;

    rule<
        std::string::const_iterator
        , shared_ptr<int>()
    > int_rule_ = int_[_val = new int(_1)];

    shared_ptr<int> subject_;

    std::string text_ = "12345";

    auto result_ = phrase_parse(text_.begin(), text_.end(), int_rule_, subject_);

    std::cout << *subject_ << std::endl;
}
