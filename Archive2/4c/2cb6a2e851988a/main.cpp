#include <cstddef>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string::const_iterator> find_conscutive_sequences(const std::string &text, const char c) {
    std::vector<std::string::const_iterator> positions{};
    std::size_t idx = 0UL;
    while (idx != std::string::npos && idx < text.length()) {
        const auto first = text.find_first_of(c, idx);
        if (first == std::string::npos)
            break;
        positions.push_back(text.cbegin() + first);
        idx = text.find_first_not_of(c, first);
    }
    return positions;
}

std::string::const_iterator get_random_consecutive_sequence(const std::string &text, const char c,
                                                            std::default_random_engine &prng) {
    const auto positions = find_conscutive_sequences(text, c);
    if (positions.empty())
        throw std::invalid_argument{ "string does not contain any sequence" };
    std::uniform_int_distribution<std::size_t> rnddist{ 0UL, positions.size() - 1UL };
    const auto idx = rnddist(prng);
    return positions.at(idx);
}

std::string mark_sequence(const std::string &text, const std::string::const_iterator start) {
    const auto c = *start;
    const std::size_t first = start - text.cbegin();
    std::size_t last = text.find_first_not_of(c, first);
    if (last == std::string::npos)
        last = text.length();
    std::string marked{};
    marked.reserve(text.length() + 2UL);
    marked += text.substr(0UL, first);
    marked += '(';
    marked += text.substr(first, last - first);
    marked += ')';
    marked += text.substr(last, text.length() - last);
    return marked;
}

#include <chrono>
#include <map>
#include <iomanip>

int main() {
    std::random_device rnddev{};
    std::default_random_engine rndengine{ rnddev() };

    for (std::string example : {
            "----",
            "A--TG-DF----GR--",
            //"",        // not supported
            //"ATGDFGR", // not supported
            "--A--B-CD----E-F---",
        })
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::string result;
        std::map<std::string, size_t> histo;

        for (int i = 0; i < 1000000; ++i) {
            const auto pos = get_random_consecutive_sequence(example, '-', rndengine);
            histo[mark_sequence(example, pos)]++;
        }

        std::cout << histo.size() << " unique results for '" << example << "'"
                  << " in " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count() << "ms\n";

        std::multimap<size_t, std::string, std::greater<size_t> > ranked;
        for (auto& entry : histo)
            ranked.emplace(entry.second, entry.first);

        int count = 10;
        for (auto& rank : ranked)
        {
            std::cout << std::setw(8) << std::right << rank.first << ": " << rank.second << "\n";
            if (0 == --count)
                break;
        }
    }
}
