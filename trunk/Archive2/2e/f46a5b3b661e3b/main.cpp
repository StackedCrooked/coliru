#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <string>
#include <map>
#include <iostream>
#include <mutex>

#include <boost/optional.hpp>
#include <boost/any.hpp>

//typedef std::map<std::string, boost::any > Row;
typedef std::map<std::string, boost::optional<boost::any> > Row;
typedef std::vector<Row> Rows;


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    
    Row row;
    //row["value"] = std::string("Hello");
    row["value"] = boost::optional<std::string>("Hello");
    
    Rows rows;
    rows.push_back(row);
    
    //std::cout << "row[\"value\"] " << boost::any_cast<std::string>( row["value"] ) << "\n";
    //std::cout << "rows[0][\"value\"] " << boost::any_cast<std::string>(  rows[0]["value"] ) << "\n";
    //std::cout << "row[\"value\"] " << row["value"] << "\n";
    //std::cout << "rows[0][\"value\"] " << rows[0]["value"] << "\n";
    
    boost::optional<std::string> blah = rows[0]["value"];
    
    
    std::cout << words << std::endl;
}

