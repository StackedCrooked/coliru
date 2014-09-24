#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <queue>

class Counter
{
public:
    Counter(std::size_t size) : max_size(size) {}

    void AddWord(const std::string& word)
    {
        if (words.size() == max_size) {
            auto it = counts.find(words.front());
            --it->second;
            if (it->second == 0) {
                counts.erase(it);
            }
            words.pop();
        }
        words.push(word);
        ++counts[word];
    }

    const std::pair<const std::string, std::size_t>& getMax() const
    {
        return *std::max_element(counts.begin(), counts.end(),
        [](const std::pair<const std::string, std::size_t>& lhs, const std::pair<const std::string, std::size_t>& rhs)
        {
            return std::tie(lhs.second, rhs.first) < std::tie(rhs.second, lhs.first);
        });
    }

private:
    std::size_t max_size;
    std::queue<std::string> words;
    std::map<std::string, std::size_t> counts;
};

int main()
{
    const std::vector<std::string> v = { "hello", "hi", "who", "hi", "hi", "hello", "who", "when" };
    Counter counter(3);

    for (const auto& s : v) {
        counter.AddWord(s);
        const auto& p = counter.getMax();
        std::cout << p.first << ":" << p.second << std::endl;
    }
    return 0;
}
