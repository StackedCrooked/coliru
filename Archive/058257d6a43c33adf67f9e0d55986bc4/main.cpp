#include <iostream>
#include <tuple>
#include <cstring>

constexpr
const char*
    find_from(const char* begin, const char* end)
{
    return (begin == end) ? end : (begin[0] == 'F' && begin[1] == 'R' && begin[2] == 'O' && begin[3] == 'M' ? begin : find_from(begin + 1, end));
}

constexpr
std::tuple<const char*, const char*, const char*, const char*>
    parse_select(const char* begin, const char* end)
{
    return std::make_tuple(begin + 6, find_from(begin + 6, end), find_from(begin + 6, end) + 5, end);
}

constexpr
std::tuple<const char*, const char*, const char*, const char*>
    operator"" _sql(const char* begin, size_t len)
{
    return parse_select(begin, begin + len);
}

int main()
{
    constexpr auto x = "select col FROM table"_sql;
    std::cout << "SELECT " << std::string{std::get<0>(x), std::get<1>(x)} << " FROM " << std::string{std::get<2>(x), std::get<3>(x)} << std::endl;
}
