#include <type_traits>
#include <utility>
#include <iostream>
#include <typeinfo>
#include <functional>

class Shibe
{
    public:
        Shibe(std::string doge) {
        }
        ~Shibe() {
        }
};

int main(int argc, char* argv[])
{
    Shibe doge(
        "░░░░░░░░░▄░░░░░░░░░░░░░░▄\n"
"░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌\n"
"░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐\n"
"░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐\n"
"░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐\n"
"░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌\n"
"░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌\n"
"░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐\n"
"░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌\n"
"░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌\n"
"▀▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒\n"
    );
    return 0;
}