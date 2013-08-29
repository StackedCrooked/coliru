#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <bitset>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

template <typename Lambda> struct WrapAction {
    template <typename...> struct result { typedef void type; };
    template <typename... T> void operator()(T&&... t) const { _ll(std::forward<T>(t)...); }

    WrapAction(Lambda&& ll) : _ll(std::forward<Lambda>(ll)) { }
  private:
    mutable Lambda _ll;
};

template <typename Lambda> WrapAction<Lambda> make_action(Lambda&& ll) { return { std::forward<Lambda>(ll) }; }

int main()
{
    std::bitset<32> row1, row2;
    auto dump = [&] { std::cout << row1 << "\n" << row2 << "\n"; };

    if (std::cin >> row1 >> row2)
    {

        std::cin.unsetf(std::ios::skipws);
        boost::spirit::istream_iterator f(std::cin), l;

        dump();

        auto toggle  = make_action([&](int i) mutable { row1.flip(i); });
        auto toggle2 = make_action([&](int i) mutable { row1.flip(i); row2.flip(i); });
        auto toggleN = make_action([&](int i1, int i2) mutable { while (i2>=i1) toggle(i2--); });
        auto show    = make_action([&](std::string const& msg) { std::cout << "after " << msg << ":\n"; dump(); });

        std::cout << "Start\n";

        using namespace boost::spirit::qi;
        using boost::phoenix::bind;
        bool ok = phrase_parse(f, l,
                -( 
                    lit("toggle") >> ("both" >> int_)                      [ bind(toggle2, _1),     bind(show, "toggle both") ]
                  | lit("toggle") >> ("from" >> int_ >> "through" >> int_) [ bind(toggleN, _1, _2), bind(show, "toggle range") ]
                  | "toggle"      >> (int_)                                [ bind(toggle,  _1),     bind(show, "toggle") ]
                  | eps(false)
                ) % eol,
                blank);

        if (ok)
            std::cout << "Done\n";
        else
            std::cout << "Failed\n";
        if (f != l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }

}