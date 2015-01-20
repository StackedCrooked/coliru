#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

typedef struct date { 
    unsigned int m_day;
    unsigned int m_month;
    unsigned int m_year;
    date( int d=1,  int m=1,  int y=2000) : m_day(d), m_month(m), m_year(y) {}

    friend std::ostream& operator << (std::ostream& out, date& d) {
        return out << "day: " << d.m_day << " month: " << d.m_month << " year: " << d.m_year;
    }

    void load(boost::property_tree::ptree const& pt)
    {
        m_day = pt.get("da.m_day", 1);
        m_month = pt.get("da.m_month", 1);
        m_year = pt.get("da.m_year", 2000);
    }
} date;

#include <sstream>

int main() {
    std::istringstream iss("<da>\n"
                "<m_day Type=\"int\">15</m_day>\n"
                "<m_month Type=\"int\">8</m_month>\n"
                "<m_year Type=\"int\">1947</m_year>\n"
                "</da>\n");

    boost::property_tree::ptree pt;
    read_xml(iss, pt);

    date d;
    d.load(pt);

    std::cout << d << "\n";
}
