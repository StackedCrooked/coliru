#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct point
{
    explicit point( int xx = 0, int yy = 0 ) : x(xx), y(yy) {}
    int x ;
    int y ;
};

constexpr char OPENP = '(' ;
constexpr char CLOSEP = ')' ;
constexpr char COMMA = ',' ;

std::ostream& operator<< ( std::ostream& stm, point pt )
{ return stm << OPENP << pt.x << COMMA << pt.y << CLOSEP ; }

std::istream& operator>> ( std::istream& stm, point& pt )
{
    int x, y ;
    char a, b, c ;
    if( stm >> a >> x >> b >> y >> c && a == OPENP && b == COMMA && c == CLOSEP )
    {
        pt = point{ x, y } ;
    }
    else
    {
        pt = point{} ;
        stm.clear( std::ios::failbit ) ;
    }

    return stm ;
}

struct line_segment
{
    line_segment() = default ;
    line_segment( point a, point b ) : from(a), to(b) {}
    line_segment( int x1, int y1, int x2, int y2 ) : from(x1,y1), to(x2,y2) {}

    point from ;
    point to ;
};

std::ostream& operator<< ( std::ostream& stm, const line_segment& line )
{ return stm << line.from << COMMA << ' ' << line.to ; }

std::istream& operator>> ( std::istream& stm, line_segment& line )
{
    point a, b ;
    char c ;
    if( stm >> a >> c >> b && c == COMMA )
    {
        line = line_segment{ a, b } ;
    }
    else
    {
        line = line_segment{} ;
        stm.clear( std::ios::failbit ) ;
    }

    return stm ;
}

int main()
{
    std::istringstream file
    (
        "...\n"
        "other information\n"
        "...\n"
        "physics:\n"
        "4,5,6,7\n"
        "...\n"
        "\n"
        "line:\n"
        "(4,2), (2,4)\n"
        "\n"
        "line:\n"
        "(1,2), (2,3)\n"
        "\n"
        "...\n"
        "line:\n"
        "(6,5), (7,9)\n"
        "...\n"
    );

    const std::string line_tag = "line:" ;
    const std::string physics_tag = "physics:" ;
    std::vector<line_segment> lines ;

    std::string line ;
    while( std::getline( file, line ) ) // for each line in file
    {
        if( line.find(line_tag) == 0 ) // if it is the tag for line
        {
            line_segment line ;
            if( file >> line ) lines.push_back(line) ;
            else file.clear() ;
        }
        else if( line.find(line_tag) == 0 ) // if it is the tag for physics
        {
            // likewise for physics
            // read in, add to collection etc.
        }

        // and likewise for other tags
    }

    for( const auto& ls : lines ) std::cout << ls << '\n' ;
}
