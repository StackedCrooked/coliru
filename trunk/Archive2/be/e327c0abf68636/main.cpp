#include <sstream>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <tuple>
#include <forward_list>

constexpr size_t NUMBER_OF_POINTS = 2000000;

struct Point {
    float x,y;
    Point() = default;
    constexpr Point(float x,float y) : x(x), y(y) {}
};

using PointContainer = std::forward_list<Point>;
using Clock = std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

std::string generate_points(int n) {
    static auto random_generator = std::mt19937{std::random_device{}()};
    std::ostringstream oss;
    std::uniform_real_distribution<float> distribution(-1, 1);
    for (int i=0; i<n; ++i) {
        oss << distribution(random_generator) << " ," << distribution(random_generator) << "\t \n";
    }
    return oss.str();
}

PointContainer parse_points1(const char* s) {
    std::istringstream iss(s);
    PointContainer points;
    float x, y;
    char comma;
    while (iss >> x >> comma >> y)
        points.emplace_front(x,y);
    return points;
}

inline
std::tuple<Point, const char*> parse_point2(const char* x_first, const char* last) {
    auto is_whitespace = [](char c) { return std::isspace(c); };
    auto x_last  = std::find(x_first, last, ',');
    auto y_first = std::find_if_not(std::next(x_last), last, is_whitespace);
    auto y_last  = std::find_if(y_first, last, is_whitespace);
    auto x = std::strtof(x_first, (char**)&x_last);
    auto y = std::strtof(y_first, (char**)&y_last);
    auto next_x_first = std::find_if_not(y_last, last, is_whitespace);
    return std::make_tuple(Point{x, y}, next_x_first);
}

PointContainer parse_points2(const char* i, const char* last) {
    PointContainer points;
    Point point;
    while (i != last) {
        std::tie(point, i) = parse_point2(i, last);
        points.push_front(point);
    }
    return points;
}

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

template <typename OI>
static inline void parse_points(OI out, char const* it, char const* last = std::numeric_limits<char const*>::max()) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    bool ok = qi::phrase_parse(it, last,
            *(qi::double_ >> ',' >> qi::double_) [ *phx::ref(out) = phx::construct<Point>(qi::_1, qi::_2) ],
            qi::space);

    if (!ok || !(it == last || *it == '\0')) {
        throw it; // TODO proper error reporting?
    }
}

PointContainer parse_points3(const char* i, const char* last) {
    PointContainer points;
    parse_points(std::front_inserter(points), i, last);
    return points;
}

#include <iostream>
#include <fstream>

int main() {
    auto s = generate_points(NUMBER_OF_POINTS);
    //{ std::ofstream datadump("datadump.txt"); datadump << s; }

    auto time0 = Clock::now();
    auto points1 = parse_points1(s.c_str());

    auto time1 = Clock::now();
    auto points2 = parse_points2(s.data(), s.data() + s.size());

    auto time2 = Clock::now();
    try {
        auto points3 = parse_points3(s.data(), s.data() + s.size());
    } catch(char const* loc)
    {
        std::cout << "Failed at '" << std::string(loc, std::min(s.data() + s.size(), loc + 20)) << "'\n";
    }

    auto time3 = Clock::now();

    std::cout << "using stringstream: " << std::chrono::duration_cast<milliseconds>(time1 - time0).count() << '\n';
    std::cout << "using strtof: "       << std::chrono::duration_cast<milliseconds>(time2 - time1).count() << '\n';
    std::cout << "using spirit: "       << std::chrono::duration_cast<milliseconds>(time3 - time2).count() << '\n';
}
