#include <string>
#include <vector>

struct sToken
{
    std::string token;
    unsigned int lineNb;
};

int main() {
    std::vector<sToken> v;
    sToken tok;
    v.push_back(tok);
}