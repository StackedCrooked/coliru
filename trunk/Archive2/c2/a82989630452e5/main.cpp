#include <iostream>
#include <iterator>
#include <vector>

template <typename It, typename Out>
Out tokens(It f, It l, Out out) {
    std::string accum;
    auto flush = [&] { 
        if (!accum.empty()) {
            *out++ = accum;
            accum.resize(0);
        }
    };

    while (f!=l) {
        switch(*f) {
            case '\\': 
                if (++f!=l && *f==' ')
                    accum += ' ';
                else
                    accum += '\\';
                break;
            case ' ': case '\t': case '\r': case '\n':
                ++f;
                flush();
                break;
            default:
                accum += *f++;
        }
    }
    flush();
    return out;
}

int main() {
    std::string const sentence = "My dog Fluffy\\ Cake likes to jump";

    std::vector<std::string> words;

    tokens(sentence.begin(), sentence.end(), back_inserter(words));

    for (auto& w : words)
        std::cout << "\t'" << w << "'\n";
}
