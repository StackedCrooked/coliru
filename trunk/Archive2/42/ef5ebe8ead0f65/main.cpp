#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <string>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace boost { namespace spirit { namespace traits 
{ 
    namespace detail {
        template <typename T>
        struct transform_to_sharedptr : boost::static_visitor<boost::shared_ptr<T> > {
            boost::shared_ptr<T> operator()(boost::shared_ptr<T>  const& v) const { return v; }

            template <typename U>
            boost::shared_ptr<T> operator()(boost::shared_ptr<U>  const& v) const { return v; }

            template <typename... Ts>
            boost::shared_ptr<T> operator()(boost::variant<Ts...> const& v) const { return boost::apply_visitor(*this, v); }

            template <typename U>
            boost::shared_ptr<T> operator()(U                     const& v) const { return make_shared<T>(v); }
        };
    }

    template<typename T, typename U>
        struct assign_to_attribute_from_value<boost::shared_ptr<T>, U> {
            static void call(U const& v, boost::shared_ptr<T>& attr) {
                std::cout << __PRETTY_FUNCTION__ << "\n"; 
                attr = detail::transform_to_sharedptr<T>()(v);
            }
        };
}}}

struct Base {
    virtual ~Base() = default;
    virtual std::string show() = 0;
};

struct A : Base {
    std::string text;
    A(std::string t = "") : text(std::move(t)) {}
    std::string show() override { return "A"; }
};

struct B : Base {
    double value;
    B(double x = 0) : value(x) {}
    std::string show() override { return "B"; }
};

typedef boost::shared_ptr<A> A_ptr;
typedef boost::shared_ptr<B> B_ptr;
typedef boost::shared_ptr<Base> Base_ptr;

int main()
{
    namespace qi     = boost::spirit::qi;
    namespace ascii  = boost::spirit::ascii;

    using It = std::string::const_iterator;
    qi::rule<It, A(),        ascii::space_type> A_rule_;
    qi::rule<It, B(),        ascii::space_type> B_rule_;
    qi::rule<It, Base_ptr(), ascii::space_type> Base_rule_;

    {
        using namespace qi;
        A_rule_ = qi::as_string [(char_("a-zA-Z") > *char_("a-zA-Z0-9")) ] ;
        B_rule_ = double_ ;

        Base_rule_ = A_rule_ | B_rule_;
    }

    std::string const text_ = "12345.023";

    Base_ptr subject_ = boost::make_shared<A>("dummy");
    auto result_ = phrase_parse(text_.begin(), text_.end(), Base_rule_, ascii::space, subject_);

    std::cout << (result_ ? "passed" : "failed") << subject_->show()
              << std::endl;
}
