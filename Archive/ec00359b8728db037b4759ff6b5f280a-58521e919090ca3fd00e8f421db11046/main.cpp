#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>
#include <codecvt>

#include <cstdint>
#include <cstdlib>

const char* handle_args(int argc, char** argv)
{
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename\n";
        std::exit(EXIT_FAILURE);
    }
    return argv[1];
}

int main(int argc, char** argv)
{
    auto filename = handle_args(argc, argv);

    using ucs4ifilestream = std::basic_ifstream<char32_t>;
    // Open as binary, as required by std::codecvt_utf16
    ucs4ifilestream file { filename, ucs4ifilestream::in | ucs4ifilestream::binary };
    file.imbue({ file.getloc(), new std::codecvt_utf16<char32_t> });

    std::stringstream arena;

    std::wbuffer_convert<std::codecvt_utf8<char32_t>, char32_t> to_bytes { arena.rdbuf() };
    std::basic_ostream<char32_t> sink { &to_bytes };
    sink.imbue(to_bytes.getloc());
    sink << file.rdbuf();

    std::wbuffer_convert<std::codecvt_utf16<char16_t>, char16_t> from_bytes { arena.rdbuf() };
    std::basic_istream<char16_t> utf16_source { &from_bytes };
    utf16_source.imbue(from_bytes.getloc());

    using Int = std::int_least16_t;
    for(char16_t c; utf16_source.get(c);)
        std::cout << std::showbase << std::hex << static_cast<Int>(c) << ' ';
    std::cout << '\n';
}