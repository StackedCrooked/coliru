#include <iostream>
#include <vector>

enum class bla {
    lalala = 4, chachinga = 3, sarasa
};

int main()
{
    std::vector<bla> phrases = { bla::lalala, bla::chachinga, bla::sarasa };
    for( auto i : phrases )
        std::cout << static_cast<std::underlying_type<bla>::type>(i) << std::endl;
    
    return 0;
}
