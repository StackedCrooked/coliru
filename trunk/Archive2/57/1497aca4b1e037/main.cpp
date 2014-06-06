#include <boost/locale.hpp>
#include <string>

int main()
{
    std::wstring aResult;

    boost::locale::generator gen;
    std::locale::global(gen("C"));

    std::wcout.imbue(std::locale());

    boost::locale::date_time aTime;

    std::wcout << std::endl << boost::locale::as::date_full   << aTime;
    std::wcout << std::endl << boost::locale::as::date_short  << aTime;
    std::wcout << std::endl << boost::locale::as::date_medium << aTime;
}
