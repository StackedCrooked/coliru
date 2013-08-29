#include <iostream>
#include <algorithm>

struct Point
{
    Point() { }
    ~Point() { }
    
    Point(int x_arg, int y_arg) : x(x_arg), y(y_arg) { }
    int x;
    int y;
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

std::string parse_format_flag(std::string flag, int value, const std::string& s)
{
    std::string output = s;

    auto it = std::search(output.begin(), output.end(), flag.begin(), flag.end());

    while (it != output.end())
    {
        output.erase(it);
        std::replace(it, it+1,
            flag[1], std::to_string(value)[0]);
        it = std::search(output.begin(), output.end(), flag.begin(), flag.end());
    }
    
    return output;
}

void operator<<(const Point& p, const std::string& format)
{
    std::string output = format;
    output = parse_format_flag("%x", p.x, output);
    output = parse_format_flag("%y", p.y, output);
    std::cout << output << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")" << std::endl;
    return os;
}

int main(int argc, char* argv[])
{
    Point(4, 5) << "(%x, %y)";
    std::cout << Point(4, 5) << "(%x, %y)" << std::endl;
    return 0;
}