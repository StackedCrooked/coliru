#include  <sstream>
#include  <string>
#include <functional>
#include <regex>
#include <memory>
#include <algorithm>
#include <tuple>
#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

//=============================================================================
// DB query :  typedef and util function
typedef  std::string             db_field_t;
typedef  std::vector<db_field_t> db_row_t;
typedef  std::vector<db_row_t>   db_rows_t;

std::size_t field_count(const db_row_t&  row)   { return row.size();}
std::size_t row_count  (const db_rows_t& rows)  { return rows.size();}

template <int n>
db_field_t field(const db_row_t& row)
{
    return row[n];
}

//=============================================================================
// Sample type for gui notify message

// locatoin_t := <x,y>
typedef std::tuple<int, int> location_t;
int x(const location_t& p) { return std::get<0>(p); };
int y(const location_t& p) { return std::get<1>(p); };

// gui_ntf_t :=<time_point, location, msg>,
typedef std::tuple<std::time_t, location_t, std::string> gui_ntf_t;
time_t      time_point (const gui_ntf_t& row) { return std::get<0>(row); };
location_t  location   (const gui_ntf_t& row) { return std::get<1>(row); };
std::string msg        (const gui_ntf_t& row) { return std::get<2>(row); };

template <typename T>
std::string to_string(const T& data)
{
    std::stringstream ss;
    ss << data;
    return ss.str();
}

template <>
std::string to_string <gui_ntf_t>(const gui_ntf_t& ntf)
{
    std::stringstream ss;
    ss  << "time_point(" << time_point(ntf)                            << "), "
    << "location("   << x(location(ntf))<< "," << y(location(ntf)) << "), "
    << "msg(\""      << msg(ntf)                                   << "\")";
    
    return ss.str();
}

int main()
{
    gui_ntf_t test(000000, location_t(58,99), "hello");
    std::cout << to_string(test) << std::endl;
    std::cout << to_string(4) << std::endl;
    
    int i = 4;
    long j = 5;
    short k = 6;
    long long l = 7;
     std::cout << to_string(i) << to_string(j) << to_string(k) << to_string(l)  << std::endl;
    
}