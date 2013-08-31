#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class MakeString
{
public:
    template <typename T>
    MakeString & operator<<(const T & datum)
    {
        mBuffer << datum;
        return *this;
    }
    operator std::string() const
    {
        return mBuffer.str();
    }
private:
    std::ostringstream mBuffer;
};

using Words = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Words & words)
{
    for (const auto & word : words)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    std::vector<std::string> numbers1 = {
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
        "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
        "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
        "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
        "60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
        "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
        "80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99"
    };
    std::vector<std::string> numbers2 = {
        /*"00",*/"01", "02"/*, "03"*/, "04", "05", "06", "07", "08",/* "09",
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
        "30",*/"31", "32", "33", "34", "35", "36", "37"/*, "38", "39"*/,
        "40", "41", "42", "43", "44", "45", "46", "47",/*"48", "49",
        "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
        "60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
        "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
        "80", "81", "82", "83", "84", "85", "86", "87", "88", "89",*/
        "90", "91", "92", "93", "94", "95", "96", "97"/*, "98", "99"*/
    };
    //srand(time(0));
    //std::random_shuffle(numbers1.begin(), numbers1.end());
    //std::random_shuffle(numbers2.begin(), numbers2.end());


    auto open = "\e[";
    auto close = "\e[00m";
    auto n = 0u;
    for (auto& a : numbers1)
    {
        for (auto& b : numbers2)
        {
            std::string s(MakeString() << open << a << ";" << b << "m" << a << b << "" << close);
            std::cout << s;
            n += 4;
            if (n >= 200) {
                std::cout << std::endl;
                n = 0;
            }
        }
    }
}

