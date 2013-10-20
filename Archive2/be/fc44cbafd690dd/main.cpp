#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>

struct Game { 
    std::string _date;
    std::string date() const { return _date; }
};

int main()
{
    for (Game game : std::vector<Game> { {"01/02/1999"}, {"24/10/2013"}})
    {
        std::istringstream stm (game.date());
        int day, month, year;
        char delim = '/';

        std::cout << "Date before: " << game.date();

        stm >> month >> delim;
        assert(stm && '/' == delim);

        stm >> day >> delim;
        assert(stm && '/' == delim);

        stm >> year;

        std::cout << " Date after: " << " | " << month << "/" << day << "/" << year << std::endl;
    }
}
