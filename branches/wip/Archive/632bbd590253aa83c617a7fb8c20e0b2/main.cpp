#include <iostream>
#include <algorithm>
#include <cassert>

template <typename In, typename Out, size_t N>
void doencode(In f, In l, const char (&from)[N], const char (&to)[N], char escape, Out out)
{
    using namespace std;
    assert(end(from) == find(begin(from), end(from), escape));
    assert(end(to)   == find(begin(to),   end(to),   escape));

    for (In it = f; it!=l; ++it)
    {
        auto const match = find(begin(from), end(from), *it);

        if (*it == escape) *out++ = escape;
        if (end(from) == match)
            *out++ = *it;
        else
        {
            *out++ = escape;
            *out++ = to[match-from];
        }
    }
}

template <typename In, typename Out, size_t N>
void dodecode(In f, In l, const char (&to)[N], const char (&from)[N], char escape, Out out)
{
    using namespace std;
    assert(end(from) == find(begin(from), end(from), escape));
    assert(end(to)   == find(begin(to),   end(to),   escape));

    for (In it = f; it!=l; ++it)
    {
        if (*it == escape) 
        {
            ++it;
            assert(it != l);
            if (*it == escape)
                *out++ = *it;
            else
            {
                auto const match = find(begin(from), end(from), *it);
                assert(end(from) != match);

                *out++ = to[match-from];
            }
        } else
        {
            *out++ = *it;
        }
    }
}

static char const from[] = { '\t', '\0' };
static char const to  [] = { 't',  'z'  };
#if 1
    static char const escape = '\\';
#   define ESC "\\"
#else
    static char const escape = '~';
#   define ESC "~"
#endif

std::string encode_copy(const std::string& s)
{
    std::string out;
    doencode(begin(s), end(s), from, to, escape, std::back_inserter(out));
    return out;
}

std::string decode_copy(const std::string& s)
{
    std::string out;
    dodecode(begin(s), end(s), from, to, escape, std::back_inserter(out));
    return out;
}

void check(const std::string plain, const std::string encoded)
{
    auto actual_enc = encode_copy(plain);
    auto actual_dec = decode_copy(encoded);
    std::cout << "'" << actual_enc << "' (should have been '" << encoded << "')\n";
    assert(actual_enc == encoded);
    assert(actual_dec == plain);
}

int main()
{
    check(std::string("\t"  ),      std::string(ESC "t"));
    check(std::string(ESC  ),       std::string(ESC ESC));
    check(std::string(ESC "t" ),    std::string(ESC ESC "t"));
    check(std::string(ESC "\t"),    std::string(ESC ESC ESC "t"));
    check(std::string(ESC "0" ),    std::string(ESC ESC "0"));
    check(std::string("\0" ESC, 2), std::string(ESC "z" ESC ESC));
}
