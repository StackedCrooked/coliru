#include <iostream>
#include <tuple>
#include <cstring>

constexpr
bool
    is_equal(const char* begin, size_t len, const char* begin2, size_t len2)
{
    return len == len2 ? (len == 0 ? true : begin[0] == begin2[0] && is_equal(begin + 1, len - 1, begin2 + 1, len2 - 1)) : false;
}

constexpr
const char*
    find_str(const char* begin, size_t len, const char* toFind, size_t lentf)
{
    return  (len < lentf) ?
            nullptr :
            (
                is_equal(begin, lentf, toFind, lentf) ?
                begin :
                find_str(begin + 1, len - 1, toFind, lentf)
            );
}

constexpr
std::tuple<const char*, size_t, const char*, size_t>
    parse_select(const char* begin, size_t len)
{
    return std::make_tuple(
        begin + 6,
        find_str(begin + 6, len - 6, "FROM", 4) - (begin + 6),
        find_str(begin + 6, len - 6, "FROM", 4) + 5,
        len - ((find_str(begin + 6, len - 6, "FROM", 4) + 5) - begin)
    );
}

constexpr
std::tuple<const char*, size_t, const char*, size_t>
    operator"" _sql(const char* begin, size_t len)
{
    return parse_select(begin, len);
}

int main()
{
    constexpr auto x = "select col FROM table"_sql;
    std::cout << "SELECT " << std::string{std::get<0>(x), std::get<1>(x)} << " FROM " << std::string{std::get<2>(x), std::get<3>(x)} << std::endl;
}
