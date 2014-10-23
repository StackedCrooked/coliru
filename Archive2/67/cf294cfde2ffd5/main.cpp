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

// for logging or debugging
std::string to_string(const gui_ntf_t& ntf)
{
  std::stringstream ss;
  ss  << "time_point(" << time_point(ntf)                            << "), "
      << "location("   << x(location(ntf))<< "," << y(location(ntf)) << "), "
      << "msg(\""      << msg(ntf)                                   << "\")";

  return ss.str();
}

//=============================================================================
// test 01 
namespace test_01
{

// Sample functions for DB emulate 01.
db_rows_t make_sample_01()
{
  static const std::string table[4][3] = {
    {"2014-10-22 17:20:43", "<32,41>", "hello" },
    {"2014-10-22 17:25:43", "<1,,22>", "c++",  },
    {"2014-10-22 17;26:43", "<25,65>", "hello",},
    {"2014-10-22 17:27:43", "<23,87>", "c++",  },
  };

  std::function<db_row_t(const std::string[3])> convert = 
    [](const std::string strs[3]) -> db_row_t 
    {
      db_row_t row;
      std::copy(&strs[0], &strs[3], std::back_inserter(row));
      return row;
     };

  db_rows_t rows;
  std::transform(begin(table), end(table), std::back_inserter(rows), convert);  
  return rows; 
}

db_rows_t db_select_emulate_01() 
{
  return  make_sample_01();
}

// "2014-10-22 17:20:43"
std::time_t to_time_point(int year, int month, int day, 
                          int hour, int minute, int second)
{
  std::tm t = {second, minute, hour, 0, month-1, year-1900, 0, 0, 0};
  return  std::mktime(&t);
}

// "2014-10-22 17:20:43"
std::time_t to_time_point(const std::string& cell)
{
  int year, month, day, hour, minuite, second;

  std::sscanf(cell.c_str(), "%d-%d-%d %d:%d:%d", 
             &year, &month, &day, &hour, &minuite, &second);
  
  return  to_time_point(year, month, day, hour, minuite, second);  
}; 

// "<234,567>"

location_t to_location(int x, int y) { return location_t(x, y);}; 
location_t to_location(const std::string& cell) 
{
  int x, y;
  std::sscanf(cell.c_str(), "<%d,%d>", &x, &y);
  return to_location(x, y);
};

// "hello"
std::string to_msg(const std::string& cell) 
{ 
  return cell; 
}

template<typename Logger, typename LineSeperator>
void main(Logger& logger, LineSeperator& endl)
{
  // ["<3,0>", "1413899956", "hello"] 
  auto to_ntf_log = [&](const db_row_t& dbrow) -> gui_ntf_t
  {
    return gui_ntf_t( to_time_point(field<0>(dbrow)),
                      to_location  (field<1>(dbrow)),
                      to_msg       (field<2>(dbrow)));
  };

  const auto db_rows =  db_select_emulate_01();
  std::vector<gui_ntf_t> gui_ntfs;

  std::transform(begin(db_rows), end(db_rows), std::back_inserter(gui_ntfs), 
                 to_ntf_log);

  logger << "---------------------------------" << endl; 
  logger << "test 01"                           << endl; 
  logger << ""                                  << endl; 
  logger << "print all gui notification infos"  << endl; 

  auto logging = [&](const gui_ntf_t& ntf){ logger << to_string(ntf) << endl; };

  std::for_each(begin(gui_ntfs), end(gui_ntfs), logging);  
}

} // end of  namespace test_01
//------------------------------------------------------------------------------


//=============================================================================
// maybe Util for error/uninitialize state check 

static const auto kUnInitString = std::make_shared<std::string>("uninitialized"); 

template <typename T>
struct maybe_t : public std::pair<T, std::shared_ptr<std::string>>
{
  typedef typename std::pair<T, std::shared_ptr<std::string>> basetype_t; 

  // constructor with uninitialized value
  maybe_t() : basetype_t(T(), kUnInitString) {};

  // coverting constructor
  maybe_t(const T& val) : basetype_t(val, nullptr) {}; 

  // implicit conversion  function. in haskell just.
  operator T() const { return value(); };

  // explicit get
  T value() const { return basetype_t::first; };

  // test 
  bool valid()   const { return basetype_t::second == nullptr;}
  bool invalid() const { return !valid();}

  void set_errmsg(const std::string& errmsg ) 
  { 
    basetype_t::second = std::make_shared<std::string>(errmsg); 
  }

  std::string error() const
  {
    auto p = basetype_t::second;
    return  p != nullptr ? *p : "";
  }
};

template <typename T>
maybe_t<T> make_error(const std::string& errmsg = *kUnInitString ) 
{ 
  maybe_t<T> t; 
  t.set_errmsg(errmsg);
  return t;
};

//=============================================================================
// Sample functions for DB emulate 01.
maybe_t<db_rows_t> make_sample_02()
{
  return test_01::make_sample_01();
}

std::shared_ptr<db_rows_t> db_select_emulate_02() 
{
  auto result = make_sample_02();
  if (result.invalid())
    return nullptr;

  return std::make_shared<db_rows_t>(result);
}

//=============================================================================
// test 02 

namespace test_02
{

int to_int(std::smatch& m, int i) { return std::atoi(m[i].str().c_str()); }

// "2014-10-22 17:20:43"
maybe_t<std::time_t> to_time_point(const std::string& cell) 
{
  const std::regex pattern("\\s*(\\d+)-(\\d+)-(\\d+)\\s+(\\d+):(\\d+):(\\d+)\\s*");
  std::smatch m;
  if (!std::regex_match(cell, m, pattern))
      return make_error<time_t>("invalid datetime pattern");

  auto toi = [&](int i) { return  to_int(m, i);};

  return test_01::to_time_point(toi(1), toi(2), toi(3), toi(4), toi(5), toi(6));
}

// "<234,567>"
maybe_t<location_t> to_location(const std::string& cell)
{
  const std::regex pattern("<(\\d+),(\\d+)>");
  std::smatch m;
  if (!std::regex_match(cell, m, pattern))
    return make_error<location_t>("invalid location pattern");

  auto toi = [&](int i) { return  to_int(m, i);};

  return location_t(toi(1), toi(2));
};

// "hello"
maybe_t<std::string> to_msg(const std::string& cell)
{ 
  if (cell.size() == 0)
    return make_error<std::string>("invalid message. empty");

  return  test_01::to_msg(cell); 
};

template<typename Logger, typename LineSeperator>
void main(Logger& logger, LineSeperator& endl)
{
  // ["2014-10-22 17:20:43", "<32,41>", "hello"] 
  auto to_ntf_log = [&](const db_row_t& dbrow) -> maybe_t<gui_ntf_t>
  {
    auto error = [](const std::string& msg){return make_error<gui_ntf_t>(msg);};

    if (field_count(dbrow) < 3)
      return error("result set's field size is less than 3");

    const auto time_point  = to_time_point(field<0>(dbrow));
    const auto location    = to_location  (field<1>(dbrow));
    const auto msg         = to_msg       (field<2>(dbrow));

    if (location.invalid())
      return error("reading location field fail. " + location.error());
    if (time_point.invalid())
      return error("reading time_point field fail. " + time_point.error());
    if (msg.invalid())
      return error("reading msg field fail. " + msg.error());

    return gui_ntf_t(time_point.value(), location.value(),  msg.value()); 
  };

  const auto result =  db_select_emulate_02();
  if (result == nullptr)
  {
    logger << "error";
    return;
  }

  const auto& db_rows = *result; 
  std::vector<maybe_t<gui_ntf_t>> gui_ntfs;
  std::transform(begin(db_rows), end(db_rows), std::back_inserter(gui_ntfs), 
                 to_ntf_log);

  logger << "---------------------------------" << endl; 
  logger << "test 02"                           << endl; 
  logger << ""                                  << endl; 
  logger << "print all gui notification infos"  << endl; 

  auto logging = [&](const maybe_t<gui_ntf_t>& ntf)
  { 
    logger << (ntf.valid() ? to_string(ntf) : "error!! " + ntf.error()) << endl;
  };

  std::for_each(begin(gui_ntfs), end(gui_ntfs), logging);  

} // end of main
}// end of namespace test_02




int main()
{
  test_01::main(std::cout, "\n");
  test_02::main(std::cout, "\n");

}
