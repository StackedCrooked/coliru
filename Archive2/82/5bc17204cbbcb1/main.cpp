#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <iostream>
#include <locale>
#include <map>
#include <string>

const std::vector<std::string> badwords = { "badword1", "badword2", "badword3", "badword4" };

char PolishReplacement[0xFF];

const std::map<std::string, std::string> PolishReplacementMap = {
    { "ł","l" }, { "ą","a" }, { "ę","e" }, { "ć","c" }, { "ż","z" }, { "ź","z" }, { "ó","o" }, { "ś","s" }, { "ń","n" },
    { "Ł","L" }, { "Ą","A" }, { "Ę","E" }, { "Ć","C" }, { "Ż","Z" }, { "Ź","Z" }, { "Ó","O" }, { "Ś","S" }, { "Ń","N" }
};

//preconstruct our array, we love speed gain by paying startup time
struct CPolishReplacementInitHack
{
    CPolishReplacementInitHack()
    {
        std::cout << "TRACE: " << __PRETTY_FUNCTION__ << "\n";

        for (unsigned char c = 0; c < 0xFF; ++c) {
            std::string const tmp(1, static_cast<char>(c));

            auto replacement = PolishReplacementMap.find(tmp);

            if (replacement == PolishReplacementMap.end())
                PolishReplacement[c] = boost::to_lower_copy(tmp)[0];
            else {
                assert(false); // code is never reached :L
                PolishReplacement[c] = boost::to_lower_copy(replacement->second)[0];
            }
        }
    }
} _CPolishReplacementInitHack;

//actual filtering
void FilterBadWords(std::string& s)
{
    std::cout << "TRACE: " << __PRETTY_FUNCTION__ << "\n";

    std::string sc(s);
    for (auto& character : sc)
        character = PolishReplacement[(unsigned char)character];

    for (auto &badword : badwords)
    {
        size_t pos = sc.find(badword);
        size_t size = badword.size();
        size_t possize;

        while (pos != std::string::npos)
        {
            possize = pos + size;

            s.replace ( s.begin() + pos,  s.begin() + possize, "*");
            sc.replace(sc.begin() + pos, sc.begin() + possize, "*");

            pos = sc.find(badword);
        }
    }
}

int main() {
    //auto loc = boost::locale::generator().generate("en_US.utf8");
    //std::locale::global(loc);

    std::string a("hello you <not nice word> person");
    std::string b("hęlló you <nót Nićę wórd> person");

    FilterBadWords(a);
    FilterBadWords(b);

    std::cout << a << "\n";
    std::cout << b << "\n";
}
