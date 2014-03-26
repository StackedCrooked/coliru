#include <sstream>
#include <iostream>
#include <cctype>

void execute(std::istream& in)
{
    char ch;
    while (in >> ch)
    {
        int repeat = 1;
        if (std::isdigit(ch))
        {
            in.unget();
            in >> repeat >> ch;
        }

        for (int i = 0; i < repeat; ++i)
            switch (ch)
            {
                case 'p' : std::cout << 'p'; break;
                case 'l' : std::cout << 'l'; break;
                case 'g' : std::cout << 'g'; break;
                case 'd' : std::cout << 'd'; break;
            }
    }
}

int main()
{
    std::istringstream in("p p p l 3 d 5 p 2 l g");
    execute(in);
}
