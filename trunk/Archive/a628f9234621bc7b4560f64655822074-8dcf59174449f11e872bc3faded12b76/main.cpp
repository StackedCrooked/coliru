#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>


typedef std::unordered_set<std::string> Words;


bool split(const std::string& text, std::string::size_type offset, const Words& word_list, Words& output)
{
    for (std::string::size_type i = 0; i + offset != text.size(); ++i)
    {
        std::string word = text.substr(offset, text.size() - offset - i);
        if (word_list.count(word))
        {
            if (split(text, offset + word.size(), word_list, output))
            {
                output.insert(word);
                return true;
            }
        }
    }
    return offset == text.size();
}


Words split(const std::string& text, const Words& input)
{
    Words result;
    split(text, 0, input, result);
    return result;
}



int main()
{
    // A small set of words.
    const Words word_list = {
        "aardvark", "aardwolf", "aaron", "aback", "abacus", "abaft", "abalone", "abandon", "abandoned", "abandonment", "abandons", "abase", "abased", "abasement", "abash", "abashed", "abate", "abated", "abatement", "abates", "abattoir", "abattoirs", "abbe", "abbess", "abbey", "abbeys", "abbot", "abbots", "abbreviate", "abbreviated", "abbreviates", "abbreviating", "abbreviation", "abbreviations", "abdicate", "abdicated", "abdicates", "abdicating", "abdication", "abdomen", "abdomens", "abdominal", "abduct", "abducted", "abducting", "abduction", "abductions", "abductor", "abductors", "abducts", "abe", "abeam", "abel", "abele", "aberdeen", "aberrant", "aberration", "aberrations", "abet", "abets", "abetted", "abetting", "abeyance", "abhor", "abhorred", "abhorrence", "abhorrent", "abhors", "abide", "abided", "abides", "abiding", "abidjan", "abies", "abilities", "ability", "abject", "abjectly", "abjure", "abjured", "ablate", "ablates", "ablating", "ablation", "ablative", "ablaze", "able", "ablebodied", "abler", "ablest", "abloom", "ablution", "ablutions", "ably", "abnegation", "abnormal", "abnormalities", "abnormality", "abnormally", "aboard"
    };

    // The input words: abbess, abbey, abbeys, abbot, abbots, abbreviate, abbreviated,
    const std::string text = "abbessabbeyabbeysabbotabbotsabbreviateabbreviated";
    
    
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
