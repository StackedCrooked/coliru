#include <iostream>
#include <stdint.h>


void encode(std::ostream& os, char c)
{
    switch (c)
    {
        case '!' : os.write("%21", 3u); return;
        case '#' : os.write("%23", 3u); return;
        case '$' : os.write("%24", 3u); return;
        case '%' : os.write("%25", 3u); return;
        case '&' : os.write("%26", 3u); return;
        case '\'': os.write("%27", 3u); return;
        case '(' : os.write("%28", 3u); return;
        case ')' : os.write("%29", 3u); return;
        case '*' : os.write("%2A", 3u); return;
        case '+' : os.write("%2B", 3u); return;
        case ',' : os.write("%2C", 3u); return;
        case '/' : os.write("%2F", 3u); return;
        case ':' : os.write("%3A", 3u); return;
        case ';' : os.write("%3B", 3u); return;
        case '=' : os.write("%3D", 3u); return;
        case '?' : os.write("%3F", 3u); return;
        case '@' : os.write("%40", 3u); return;
        case '[' : os.write("%5B", 3u); return;
        case ']' : os.write("%5D", 3u); return;
        default  :
        {
            os.put(*reinterpret_cast<uint8_t*>(&c));
            break;
        }
    }
}


int main()
{
    char c;
    while (std::cin.read(&c, 1))
    {
        encode(std::cout , c);
    }
}
