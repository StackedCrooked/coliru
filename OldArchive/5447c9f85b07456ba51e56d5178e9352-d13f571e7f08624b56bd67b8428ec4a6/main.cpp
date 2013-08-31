#include <iostream>
#include <algorithm>

struct Point
{
    Point() { }
    ~Point() { }
    
    Point(int x_arg, int y_arg) : x(x_arg), y(y_arg) { }
    int x;
    int y;
};

void operator<<(const Point& p, const std::string& format)
{
    std::string output = format;
    std::string xflag = "%x";
    std::string yflag = "%y";
    auto it = std::search(format.begin(), format.end(), xflag.begin(), xflag.end());
    std::string repl = std::to_string(p.x);
    if (it != format.end())
        output.replace(it, it+1, 
            repl.begin(), repl.end());
    std::cout << output << std::endl;
}

int main(int argc, char* argv[])
{
    Point(4, 5) << "(%x, %y) are this point's coordinates.";
}