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

struct Base {

    Base() {}

    virtual ~Base() {}

    virtual std::string show() = 0;
};

struct A : Base {

    std::string text;

    A() : Base(), text() {}

    A(std::string& t) : Base(), text(t) {}

    virtual ~A() {}

    virtual std::string show() override {
        return "A";
        }
};

struct B : Base {

    double value;

    B() : Base(), value(0) {}

    B(const double& x) : Base(), value(x) {}

    virtual ~B() {}

    virtual std::string show() override {
        return "B";
        }
};

typedef boost::shared_ptr<A> A_ptr;
typedef boost::shared_ptr<B> B_ptr;
typedef boost::shared_ptr<Base> Base_ptr;

int main()
{
    namespace spirit = boost::spirit;
    namespace qi = spirit::qi;
    namespace phoenix = boost::phoenix;
    namespace ascii = spirit::ascii;

    using qi::rule;
    using qi::char_;
    using qi::double_;
    using qi::_1;
    using qi::_val;
    using qi::phrase_parse;
    using boost::shared_ptr;
    using boost::make_shared;
    using boost::dynamic_pointer_cast;

    shared_ptr<int> x = make_shared<int>(123);

    std::cout << *x << std::endl;

    rule<std::string::const_iterator, A_ptr(), ascii::space_type> A_rule_
    = (char_("a-zA-Z") > *char_("a-zA-Z0-9"))[_val = new A(_1)];

    rule<std::string::const_iterator, B_ptr(), ascii::space_type> B_rule_
    = double_[_val = new B(_1)];

    /* although this is an "alternative", not in the boost::variant sense:
    instead, I want the attribute to land in a Base shared_ptr */
    rule<std::string::const_iterator, Base_ptr(), ascii::space_type> Base_rule_
    = A_ptr[_val = dynamic_pointer_cast<Base>(_1)]
    | B_ptr[_val = dynamic_pointer_cast<Base>(_1)];

    Base_ptr subject_;

    std::string text_ = "12345.023";

    auto result_ = phrase_parse(text_.cbegin(), text_.cend(), int_rule_, ascii::space, subject_);

    std::cout << (result_ ? "passed" : "failed") << subject_->show() << std::endl;
}
