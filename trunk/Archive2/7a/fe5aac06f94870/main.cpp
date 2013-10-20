#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>

struct dateparser
{
    dateparser(std::string fmt)
    {
        // set format
        using namespace boost::local_time;
        local_time_input_facet* input_facet = new local_time_input_facet();
        input_facet->format(fmt.c_str());
        ss.imbue(std::locale(ss.getloc(), input_facet));
    }

    bool operator()(std::string const& text)
    {
        ss.clear();
        ss.str(text);

        bool ok = ss >> pt;

        if (ok)
        {
            auto tm = to_tm(pt);
            year    = tm.tm_year;
            month   = tm.tm_mon + 1; // for 1-based (1:jan, .. 12:dec)
            day     = tm.tm_mday;
        }

        return ok;
    }

    boost::posix_time::ptime pt;
    unsigned year, month, day;

  private:
    std::stringstream ss;
};

int main(){
    dateparser parser("%d/%m/%Y"); // not thread safe
    
    // parse
    for (auto&& txt : { "05/11/1996", "30/02/1983", "29/02/2000", "29/02/2001" })
    {
        if (parser(txt))
            std::cout << txt << " -> " << parser.pt << " is the " 
                 << parser.day      << "th of "
                 << std::setw(2)    << std::setfill('0') << parser.month
                 << " in the year " << parser.year       << "\n";
        else
            std::cout << txt << " is not a valid date\n";
    }
}

