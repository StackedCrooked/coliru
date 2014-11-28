#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> words;
    std::string word = "";
    char prev = '\0';
    std::string sentence = "This__should_______be____split_into____seven___strings";
    for (char c : sentence)
    {
        switch (c)
        {
        case '_':
        {
            if (prev != '_')
            {
                words.push_back(word);
                word = "";
                prev = '_';
            }
            break;
        }
        default:
        {
            word += c;
            prev = c;
            break;
        }
        };
    }
    if (!word.empty())
    {
        words.push_back(word);
    }
    for (const auto &word : words)
    {
        std::cout << word << std::endl;
    }
}
