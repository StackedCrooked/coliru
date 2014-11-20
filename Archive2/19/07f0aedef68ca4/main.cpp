#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

StringVector sort_example(const StringVector & input)
{
    StringVector output{ input };
    using std::begin; using std::end;
    std::sort(begin(output), end(output));
    return output;
}

int main()
{
    StringVector words{ "ak", "vj", "jhop", "vv" };
    std::cout << "Before: \n";
    for (auto && word : words) std::cout << word << "\n";

    std::cout << "After: \n";
    words = sort_example(words);
    for (auto && word : words) std::cout << word << "\n";
}
