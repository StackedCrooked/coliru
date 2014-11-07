#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

template<typename It, typename Acc>
auto my_accumulate(It first, It last, Acc acc) {
    for (; first != last; ++first) {
        acc += *first;
    }
    return acc;
}

class WordCounter {
public:
    WordCounter() = default;
    WordCounter(const WordCounter&) = default;
    WordCounter(WordCounter&&) = default;
    WordCounter& operator=(WordCounter&&) = default;

    WordCounter& operator+=(const string& s) { ++m_counts[s]; return *this; }

    auto begin() const { return std::begin(m_counts); }
    auto end() const { return std::end(m_counts); }
private:
    unordered_map<string, int> m_counts;
};

WordCounter operator+(WordCounter acc, const string& s) { acc += s; return acc; }

int main() {
    auto wordCounts = accumulate(istream_iterator<string>{cin}, istream_iterator<string>{}, WordCounter{});
    for_each(begin(wordCounts), end(wordCounts), [](const auto& entry) {
        cout << entry.first << ": " << entry.second << endl;
    });
    cout << endl;
}
