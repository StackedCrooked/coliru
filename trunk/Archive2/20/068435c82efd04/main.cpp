#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>

    std::string sort_by_word_code(const std::string &src)
    {
        if (src.empty())
            return "";

        typedef std::string::const_iterator const_iterator;
        typedef std::tuple<const_iterator, const_iterator, int> WordTuple;
        std::vector<WordTuple> words;

        const_iterator i = src.begin(), j;
        int code;

        while (1)
        {
            code = 0;
            for (j = i; j != src.end() && *j != ' '; ++j)
            {
                code += *j;
            }

            words.push_back(WordTuple(i, j, code));

            if (j == src.end())
                break;

            i = j + 1;
        }

        std::sort(words.begin(), words.end(),
            [](const WordTuple &t1, const WordTuple &t2) { return std::get<2>(t1) < std::get<2>(t2); }
            );

        std::string result;
        result.reserve(src.size());

        for (auto it = words.begin(); ; )
        {
            result.insert(result.end(),
                std::get<0>(*it),
                std::get<1>(*it)
                );

            ++it;
            if (it == words.end())
                break;

            result.push_back(' ');
        }
        
        return result;
    }

int main()
{
    std::cout << sort_by_word_code("ab nn ac mm") << std::endl;
    std::cout << sort_by_word_code("acd abz") << std::endl;
}
