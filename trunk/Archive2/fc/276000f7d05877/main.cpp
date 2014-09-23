#include <iostream>

namespace san {

    enum class week { // scoped enum
        Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
    };

    enum colour { // unscoped enum
        Red, Green, Blue, Black, Grey, White
    };
}

namespace san2 {

    enum class week { // scoped enum
        Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
    };
    std::ostream& operator<< ( std::ostream& stm, week w )
    {
        static const char* const names[] = {
            "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Undefined"
        };
        std::size_t pos = std::size_t(w) ;
        if( pos > std::size_t(week::Sunday) ) pos = std::size_t(week::Sunday) + 1 ;
        return stm << names[pos] ;
    }

    enum colour { // unscoped enum
        Red, Green, Blue, Black, Grey, White
    };
    std::ostream& operator<< ( std::ostream& stm, colour c )
    {
        static const char* const names[] = {
            "Red", "Green", "Blue", "Black", "Grey", "White", "Undefined"
        };

        std::size_t pos = c ;
        if( pos > White ) pos = White + 1 ;
        return stm << names[pos] ;
    }
}

int main()
{
    {
        san::week today = san::week::Tuesday ;
        std::cout << int(today) << '\n' ; // 1

        san::colour cloudy = san::Grey ;
        std::cout << cloudy << '\n' ; // 4
    }
    {
        san2::week today = san2::week::Tuesday ;
        std::cout << today << '\n' ; // Tuesday

        san2::colour cloudy = san2::Grey ;
        std::cout << cloudy << '\n' ; // Grey
    }

}
