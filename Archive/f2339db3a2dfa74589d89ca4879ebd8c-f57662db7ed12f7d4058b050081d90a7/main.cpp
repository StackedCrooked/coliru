#include <map>
#include <iostream>

std::map<char, size_t> histogram(std::string const& input)
{
    std::map<char, size_t> freq;
    for (auto ch : input)
        freq[ch]++;

    return freq;
}

int main()
{
    std::string input = "hello world (or read this from a large file";

    auto frequencies = histogram(input);

    for (auto& entry : frequencies)
        std::cout << "'" << entry.first << "': " << entry.second << "\n";
}
