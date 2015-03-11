#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_standard_wide.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <string>

namespace client
{
    namespace qi   = boost::spirit::qi;
    namespace wide = qi::standard_wide;

    ///////////////////////////////////////////////////////////////////////////////
    //  Parse roman hundreds (100..900) numerals using the symbol table.
    //  Notice that the data associated with each slot is the parser's attribute
    //  (which is passed to attached semantic actions).
    ///////////////////////////////////////////////////////////////////////////////
    struct hundreds_ : qi::symbols<wchar_t, unsigned>
    {
        hundreds_()
        {
            add
                (L"C"    , 100)
                (L"CC"   , 200)
                (L"CCC"  , 300)
                (L"CD"   , 400)
                (L"D"    , 500)
                (L"DC"   , 600)
                (L"DCC"  , 700)
                (L"DCCC" , 800)
                (L"CM"   , 900)
            ;
        }

    } hundreds;

    ///////////////////////////////////////////////////////////////////////////////
    //  Parse roman tens (10..90) numerals using the symbol table.
    ///////////////////////////////////////////////////////////////////////////////
    //[tutorial_roman_tens
    struct tens_ : qi::symbols<wchar_t, unsigned>
    {
        tens_()
        {
            add
                (L"X"    , 10)
                (L"XX"   , 20)
                (L"XXX"  , 30)
                (L"XL"   , 40)
                (L"L"    , 50)
                (L"LX"   , 60)
                (L"LXX"  , 70)
                (L"LXXX" , 80)
                (L"XC"   , 90)
            ;
        }

    } tens;
    //]

    ///////////////////////////////////////////////////////////////////////////////
    //  Parse roman ones (1..9) numerals using the symbol table.
    ///////////////////////////////////////////////////////////////////////////////
    struct ones_ : qi::symbols<wchar_t, unsigned>
    {
        ones_()
        {
            add
                (L"I"    , 1)
                (L"II"   , 2)
                (L"III"  , 3)
                (L"IV"   , 4)
                (L"V"    , 5)
                (L"VI"   , 6)
                (L"VII"  , 7)
                (L"VIII" , 8)
                (L"IX"   , 9)
            ;
        }

    } ones;

    ///////////////////////////////////////////////////////////////////////////////
    //  roman (numerals) grammar
    //
    //      Note the use of the || operator. The expression
    //      a || b reads match a or b and in sequence. Try
    //      defining the roman numerals grammar in YACC or
    //      PCCTS. Spirit rules! :-)
    ///////////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    struct roman : qi::grammar<Iterator, unsigned()>
    {
        roman() : roman::base_type(start)
        {
            using qi::lit;
            using wide::char_;

            using qi::eps;
            using qi::_val;
            using qi::_1;

            start = eps             [_val = 0] >>
                (
                    +lit(L'M')      [_val += 1000]
                    ||  hundreds    [_val += _1]
                    ||  tens        [_val += _1]
                    ||  ones        [_val += _1]
                )
            ;
        }

        qi::rule<Iterator, unsigned()> start;
    };
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int
main()
{
    typedef std::wstring::const_iterator iterator_type;
    typedef client::roman<iterator_type> roman;

    roman roman_parser; // Our grammar

    std::wstring str;
    unsigned result;
    while (std::getline(std::wcin, str))
    {
        if (str.empty() || str[0] == L'q' || str[0] == L'Q')
            break;

        std::wstring::const_iterator iter = str.begin();
        std::wstring::const_iterator end = str.end();
        bool r = parse(iter, end, roman_parser, result);

        if (r && iter == end)
        {
            std::wcout << L"-------------------------\n";
            std::wcout << L"Parsing succeeded\n";
            std::wcout << L"result = " << result << std::endl;
            std::wcout << L"-------------------------\n";
        }
        else
        {
            std::wstring rest(iter, end);
            std::wcout << L"-------------------------\n";
            std::wcout << L"Parsing failed\n";
            std::wcout << L"stopped at: \": " << rest << L"\"\n";
            std::wcout << L"-------------------------\n";
        }
    }

    std::wcout << L"Bye... :-) \n\n";
}
