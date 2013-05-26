#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>


typedef std::unordered_set<std::string> Words;
typedef std::vector<std::string> WordVector;


bool split(const std::string& text, std::string::size_type offset, const Words& word_list, Words& output, WordVector& vector_output)
{
    for (std::string::size_type i = 0; i + offset != text.size(); ++i)
    {
        std::string word = text.substr(offset, text.size() - offset - i);
        if (word_list.count(word))
        {
            if (split(text, offset + word.size(), word_list, output, vector_output))
            {
                output.insert(word);
                vector_output.push_back(word);
                return true;
            }
        }
    }
    return offset == text.size();
}


WordVector split(const std::string& text, const Words& input)
{
    Words result;
    WordVector wv;
    split(text, 0, input, result, wv);
    return wv;
}



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
    // A small set of words.
    const Words word_list = {
        "a", "aa", "ab", "b", "aab", "abb", "aba", "aabb"
    };
    
    std::cout << "The wordt list is: " << word_list << std::endl;

    const std::string text = "ababbbbbbabbaaababbbaabbaaaaaabaaabbbaaabbbabaabbbbababbbaaababbbbbbbabbabbbbabbbabbbabbaaabbaaababa";
    
    
    std::cout << "Let's try to split \"" << text << "\" into individual words." << std::endl;
    
    
    // Try to split the gibberish into words.
    auto result = split(text, word_list);
    
    if (!result.empty())
    {
        std::cout << "We found " << result.size() << " words: ";
        for (const std::string& w : result)
        {
            std::cout << w << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Not splittable." << std::endl;
    }
}
