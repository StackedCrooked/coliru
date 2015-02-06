#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/// returns: new array length

int main() {
    size_t arraylen = 7;
    std::string line;
    std::string *randNum = new std::string[arraylen];
    std::string *phrase  = new std::string[arraylen];

    std::ifstream randomTxt;

    randomTxt.open("random.txt");

    for (size_t i=0; getline(randomTxt, line); ++i)
    {
        std::cout << "DEBUG LINE: '" << line << "'\n";
        //nextstep = 0;

        std::stringstream ss(line);
        std::string field;
        while (getline(ss, field, ',')) {
            std::cout << "DEBUG INNER " << i << " '" << field << "'\n";

            if (i == (arraylen - 1)) {
                size_t arraylen_new = arraylen + 1;
                {
                    std::string *tmp = new std::string[arraylen_new];
                    copy(randNum, randNum + arraylen, tmp);
                    delete[] randNum;
                    randNum = tmp;
                }

                {
                    std::string *tmp = new std::string[arraylen_new];
                    copy(phrase, (phrase + arraylen), tmp);
                    delete[] phrase;
                    phrase = tmp;
                }
                arraylen = arraylen_new;
            }
        }
    }
}
