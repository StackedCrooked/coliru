bool filter(char* text, bool(*pred)(char)) {
    char* out = text;
    while (*text)
    {
        if (pred(*text))
        {
            ++text;           // just skip
        } else
        {
            *out++ = *text++; // copy out
        }
    }
    *out = '\0';
    return (out != text); // true if characters were filtered
}

#include <cctype>
#include <cstring>
#include <cstdio>

bool foo(char c)
{
    return isalpha((int)(unsigned char)c);
}

void test(const char* input)
{
    char* s = strdup(input);
    printf("%s -> ", s);
    bool b = filter(s, foo);

    printf("%s (%s)\n", s, b?"true":"false");
}

int main()
{
    test("12346  234890-98 .");
    test("12a46  awesome-98!");
}