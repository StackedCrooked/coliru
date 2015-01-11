#include <boost/algorithm/string/replace.hpp>
#include <boost/locale.hpp>
#include <iostream>
#include <locale>
#include <set>
#include <string>

const std::set<std::string> badwords =
{
    "<not nice word>", 
    "<another not nice word>" 
};

namespace detail {
    template <typename CharT>
    struct is_primcoll_equal
    {
        is_primcoll_equal(const std::locale& Loc=std::locale()) :
            m_Loc(Loc), comp(Loc, boost::locale::collator_base::primary) {}

        template< typename T1, typename T2 >
            bool operator()(const T1& Arg1, const T2& Arg2) const {
                // assert(0 == comp(L"<not nice word>", L"<nót Nićę wórd>"));
                // TODO use `do_compare` methods on the collation itself that
                // don't construct basic_string<> instances
                return 0 == comp(std::basic_string<CharT>(1, Arg1), std::basic_string<CharT>(1, Arg2));
            }

      private:
        std::locale m_Loc;
        boost::locale::comparator<CharT> comp;
    };

    template<typename SequenceT, typename Range1T, typename Range2T>
        inline void collate_replace_all( 
                SequenceT& Input,
                const Range1T& Search,
                const Range2T& Format,
                const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format_all( 
                    Input, 
                    ::boost::algorithm::first_finder(Search, is_primcoll_equal<typename SequenceT::value_type>(Loc)),
                    ::boost::algorithm::const_formatter(Format) );
        }
}

void FilterBadWords(std::string& s) {
    using namespace boost::locale::conv;

    std::wstring widened = utf_to_utf<wchar_t>(s, stop);

    for (auto& badword : badwords) {
        detail::collate_replace_all(widened, badword, L"*"/*, loc*/);
    }

    s = utf_to_utf<char>(widened, stop);
}

static_assert(sizeof(wchar_t) == sizeof(uint32_t), "Required for robustness (surrogate pairs, anyone?)");

int main()
{
    auto loc = boost::locale::generator().generate("en_US.utf8");
    std::locale::global(loc);

    std::string a("hello you <not nice word> person");
    std::string b("hęlló you <nót Nićę wórd> person");

    FilterBadWords(a);
    FilterBadWords(b);
    std::cout << a << "\n";
    std::cout << b << "\n";
}
