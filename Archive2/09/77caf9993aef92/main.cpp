#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <string>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace {
    template <typename T>
    struct make_shared_f
    {
        template <typename... A> struct result 
            { typedef boost::shared_ptr<T> type; };

        template <typename... A>
        typename result<A...>::type operator()(A&&... a) const {
            return boost::make_shared<T>(std::forward<A>(a)...);
        }
    };

    template <typename T>
    using make_shared_ = boost::phoenix::function<make_shared_f<T> >;
}

struct Base
{
    Base() {}
    virtual ~Base() {}
    virtual std::string show() = 0;
};

struct A : Base
{
    std::string text;
    A() : Base(), text() {}
    A(std::string& t) : Base(), text(t) {}
    virtual ~A() {}
    virtual std::string show() override { return "A"; }
};

struct B : Base
{
    double value;
    B() : Base(), value(0) {}
    B(const double& x) : Base(), value(x) {}
    virtual ~B() {}
    virtual std::string show() override { return "B"; }
};

typedef boost::shared_ptr<A> A_ptr;
typedef boost::shared_ptr<B> B_ptr;
typedef boost::shared_ptr<Base> Base_ptr;

int main()
{
    namespace spirit = boost::spirit;
    namespace qi     = spirit::qi;
    namespace phx    = boost::phoenix;
    namespace ascii  = spirit::ascii;

    using It = std::string::const_iterator;
    qi::rule<It, A_ptr(),    ascii::space_type> A_rule_;
    qi::rule<It, B_ptr(),    ascii::space_type> B_rule_;
    qi::rule<It, Base_ptr(), ascii::space_type> Base_rule_;

    {
        using namespace qi;
        A_rule_ = qi::as_string [(char_("a-zA-Z") > *char_("a-zA-Z0-9")) ] 
            [_val = make_shared_<A>()(_1)];

        B_rule_ = double_
            [_val = make_shared_<B>()(_1)];

        /* although this is an "alternative", not in the boost::variant sense:
           instead, I want the attribute to land in a Base shared_ptr */
        Base_rule_ = A_rule_ | B_rule_;
    }

    std::string const text_ = "12345.023";

    Base_ptr subject_;
    auto result_ = phrase_parse(text_.begin(), text_.end(), Base_rule_, ascii::space, subject_);

    std::cout << (result_ ? "passed" : "failed") << subject_->show()
              << std::endl;
}
