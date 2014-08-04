#include <boost/date_time.hpp>
#include <boost/locale.hpp>
#include <boost/format.hpp>
#include <iostream>

int main()
{ 
    boost::locale::generator gen;
    gen.add_messages_domain("messages");
    gen.add_messages_path(".");

    for(auto loc_id : { "de_DE", "en_US", "nl_NL", "nl_BE", "fr_FR", "ru_RU" })
    {
        namespace as = boost::locale::as;
        using boost::locale::translate;
        using boost::locale::format;

        auto loc = gen.generate(std::string(loc_id) + ".UTF-8");
        std::cout.imbue(loc);
        std::cout << "---------------------------\n";

        boost::locale::date_time start_date(loc);
        start_date += boost::locale::period::day(3);
        boost::locale::date_time aug(boost::locale::period::august(), loc);

        std::cout << format(translate("{1}: Task runs every {2,ordinal} week from this {3,ftime='%A'} ({3,date})\n")) % loc_id % 3 % start_date;
        
        std::cout << format(translate("First period ({1}) bill is {2}\n")) 
                        % (format("{1,ftime='%B'}") % aug)
                        % (format("{1,currency}") % 42);
    }
} 
