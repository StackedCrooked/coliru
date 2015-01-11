#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <iostream>
#include <locale>
#include <map>
#include <string>

const std::vector<std::string> badwords = { "badword1", "loophole", "badword3", "badword4" };

//actual filtering
void FilterBadWords(std::string& s)
{
    //preconstruct our array, we love speed gain by paying startup time
    static auto const& Mapping_CP852 = [] {
        std::cout << "PRECONSTRUCT: " << __PRETTY_FUNCTION__ << "\n";

        static uint8_t mappings[0x100];
        for(unsigned i = 0; i < sizeof(mappings); ++i)
            mappings[i] = static_cast<uint8_t>(i); 

        mappings[0x88 /* ł */] = 'l';
        mappings[0xa5 /* ą */] = 'a';
        mappings[0xa9 /* ę */] = 'e';
        mappings[0x86 /* ć */] = 'c';
        mappings[0xbe /* ż */] = 'z';
        mappings[0xab /* ź */] = 'z';
        mappings[0xa2 /* ó */] = 'o';
        mappings[0x98 /* ś */] = 's';
        mappings[0xe4 /* ń */] = 'n';
        mappings[0x9d /* Ł */] = 'L';
        mappings[0xa4 /* Ą */] = 'A';
        mappings[0xa8 /* Ę */] = 'E';
        mappings[0x8f /* Ć */] = 'C';
        mappings[0xbd /* Ż */] = 'Z';
        mappings[0x8d /* Ź */] = 'Z';
        mappings[0xe0 /* Ó */] = 'O';
        mappings[0x97 /* Ś */] = 'S';
        mappings[0xe3 /* Ń */] = 'N';

        return mappings;
    }();

    std::string sc(s); // bit redundant work here
    for (auto& character : sc) character = Mapping_CP852[(uint8_t)character];

    for (auto &badword : badwords) {
        size_t pos = sc.find(badword);
        size_t size = badword.size();

        while (pos != std::string::npos)
        {
            s.replace ( s.begin() + pos,  s.begin() + pos + size, "*");
            sc.replace(sc.begin() + pos, sc.begin() + pos + size, "*");

            pos = sc.find(badword);
        }
    }
}

int main() {
    std::string a("hello you badword1 person");

    // std::string b("hęlló you łoophołe person");
    //
    // following CP852 line obtained using 
    //    iconv --to-code=852 <<< "hello you łoophołe person" | xxd -i
    std::string b {
        0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x79, 0x6f, 0x75, 0x20,
        (char) 0x88, 0x6f, 0x6f, 0x70, 0x68, 0x6f, (char) 0x88, 0x65,
        0x20, 0x70, 0x65, 0x72, 0x73, 0x6f, 0x6e
    };

    FilterBadWords(a);
    FilterBadWords(b);

    std::cout << a << "\n";
    std::cout << b << "\n";
}
