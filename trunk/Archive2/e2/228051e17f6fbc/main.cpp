#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/bind.hpp>
#include <fstream>

namespace spirit = boost::spirit;
namespace lex    = spirit::lex;

enum token_ids {
    X = lex::min_token_id + 1,
    Y,
    Z,
};

template<typename L>
class word_count_tokens : public lex::lexer<L>
{
    public:
        word_count_tokens () {
            this->self.add
                ("[^ \t\n]+", X)
                ("\n"       , Y)
                ("."        , Z);
        }
};

struct counter
{
    typedef bool result_type;

    template<typename T>
    bool operator () (const T &t, size_t &c, size_t &w, size_t &l) const {
        switch (t.id ()) {
            case X:
                ++w; c += boost::distance(t.value()); // t.value ().size ();
                break;
            case Y:
                ++l; ++c;
                break;
            case Z:
                ++c;
                break;
        }

        return true;
    }
};

int main (int argc, char **argv)
{
    std::ifstream ifs (argv[1], std::ios::in | std::ios::binary);
    ifs >> std::noskipws;
    boost::spirit::istream_iterator first(ifs), last;
    word_count_tokens<lex::lexertl::lexer<lex::lexertl::token<boost::spirit::istream_iterator>>> word_count_functor;

    size_t w = 0, c = 0, l = 0;
    bool r = lex::tokenize (first, last, word_count_functor, 
            boost::bind (counter (), _1, boost::ref (c), boost::ref (w), boost::ref (l)));

    ifs.close ();

    if (r) {
        std::cout << l << ", " << w << ", " << c << std::endl;
    }
}
