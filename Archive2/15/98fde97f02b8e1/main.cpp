#include <boost/date_time.hpp>
#include <boost/locale.hpp>
#include <boost/format.hpp>
#include <boost/format/alt_sstream.hpp>
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

        std::cout << boost::format(translate("%s: Task runs every %s week from this %s (%s)\n"), loc) 
                        % loc_id
                        % (boost::locale::format("{1,ordinal}") % 3)
                        % (boost::locale::format("{1,ftime='A'}") % start_date)
                        % (boost::locale::format("{1,date}") % start_date)
                        ;
        
        std::cout << boost::format(translate("First period (%s) bill is %s\n"), loc) 
                        % (format("{1,ftime='%B'}") % aug)
                        % (format("{1,currency}") % 42);
    }
} 
