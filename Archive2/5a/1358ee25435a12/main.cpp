#include <functional>
#include <regex>
#include <memory>
#include <algorithm>
#include <tuple>
#include <utility>
#include <iostream>
#include <string>
#include <ctime>


typedef  std::string             db_field_t;
typedef  std::vector<db_field_t> db_row_t;
typedef  std::vector<db_row_t>   db_rows_t;

std::size_t field_count(const db_row_t&  row)   { return row.size();}
std::size_t row_count  (const db_rows_t& rows)  { return rows.size();} 


typedef std::tuple<int, int> point_t;
int x(const point_t& p) { return std::get<0>(p); };
int y(const point_t& p) { return std::get<0>(p); };

typedef std::tuple<point_t, std::string, std::time_t> my_row_t;
point_t     point      (const my_row_t& row) { return std::get<0>(row); };
std::string msg        (const my_row_t& row) { return std::get<1>(row); };
time_t      start_time (const my_row_t& row) { return std::get<2>(row); };

/*
template <typename T> 
struct maybe_t : public std::pair<T, bool>
{
  maybe_t(std::pair<T, bool>& val) : std::pair<T, bool>(val) {};
};*/

template <typename T> 
using maybe_t = std::pair<T, bool>;

template <typename T>
bool is_nothing(const maybe_t<T>& val) { return val.second == false; };

template <typename T>
T just(const maybe_t<T>& val) { return val.first; };

template <typename T>
maybe_t<T> make_just(const T& val) { return std::make_pair(val, true);};

template <typename T>
maybe_t<T> make_nothing() { return std::make_pair(T(), true);};

maybe_t<db_rows_t> make_sample()
{
  static const std::string table[4][3] = {
    {"<0,0>", "hello", "1413871956"},
    {"<1,0>", "world", "1413881956"},
    {"<2,0>", "hello", "1413891956"},
    {"<3,0>", "c++11", "1413899956"},
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
   
  return make_just(rows); 
}

std::shared_ptr<db_rows_t> select_emulate() 
{
  auto result = make_sample();
  if (is_nothing(result))
    return nullptr;

  return std::make_shared<db_rows_t>(just(result));
}

int main()
{
  auto result =  select_emulate();
  if (result == nullptr)
  {
    std::cout << "error";
    return -1;
  }

  // "<234,567>"
  auto to_point = [](const std::string& field) -> maybe_t<point_t> 
  {
    const std::regex pattern("<(\\d+),(\\d+)>");
    std::smatch m;
    if (!std::regex_match(field, m, pattern))
      return make_nothing<point_t>();
    auto x = std::atoi(m[1].str().c_str());
    auto y = std::atoi(m[2].str().c_str());
    return make_just(point_t(x, y));
  };

  auto convert = [](const db_row_t& dbrow) -> my_row_t
  {
    my_row_t myrow;
    return myrow;
  };

  return 0;
}