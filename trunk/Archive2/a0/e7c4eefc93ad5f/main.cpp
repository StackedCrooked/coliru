#include <sstream>
#include <iostream>
#include <cctype>

void execute(std::istream& in)
{
    char ch;
    int repeat = 1;
    while (in >> ch)
    {
        if (std::isdigit(ch))
        {
            in.unget();
            in >> repeat;
        }
        else
        {
            for (int i = 0; i < repeat; ++i)
                switch (ch)
                {
                    case 'p' : std::cout << 'p'; break;
                    case 'l' : std::cout << 'l'; break;
                    case 'g' : std::cout << 'g'; break;
                    case 'd' : std::cout << 'd'; break;
                }
        
            repeat = 1;
        }
    }
}

int main()
{
    std::istringstream in("p p p l 3 d 5 p 2 l");
    execute(in);
}
