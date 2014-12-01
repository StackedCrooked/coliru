#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <map>
    
const int max_draw = 49;

template <typename T, typename Validation>
T read_valid_input(std::string const& prompt, Validation validate) {
    do {
        std::cout << prompt;
        T v;

        if (std::cin >> v && validate(v))
            return v;

        if (std::cin.eof())
            exit(255);

        std::cin.clear();
        std::cin.ignore(1ul<<10, '\n');
    } while (true);
}

template <typename T>
T read_valid_input(std::string const& prompt) {
    return read_valid_input<T>(prompt, [](T const&) { return true; });
}

void Frequency() {
    // initialize histogram data
    struct entry { int draw; size_t frequency; };
    std::vector<entry> histogram(max_draw + 1);

    for (auto i = 0ul; i < histogram.size(); ++i)
        histogram[i] = { int(i), 0ul };

    // read loop count
    auto const num = read_valid_input<size_t>("Enter loop count: ");

    // random draws
    std::mt19937 engine(time(0));
    std::uniform_int_distribution<int> dist(0, max_draw);

    for (auto i = 0ul; i < num * 6; ++i)
        histogram[dist(engine)].frequency += 1;

    // output full histogram data
    for (auto& e: histogram)
        std::cout << e.draw << " found " << e.frequency << " times\n";

    // partial sort for 6th highest
    auto b = histogram.begin(),
         m = b + std::min(6ul, histogram.size()),
         e = histogram.end();

    std::partial_sort(b, m, e, [](entry a, entry b) { return a.frequency > b.frequency; });
    for (auto it = b; it != m; ++it)
        std::cout << it->draw << "=" << it->frequency << "\t";
}

int main() {

    read_valid_input<unsigned>("Enter password: ", [](unsigned pwd) {
            if (pwd != 210201012) {
                std::cout << "Password is incorrect. ";
                return false;
            }
            return true;
        });

    std::cout << "Access obtained\n";
    Frequency();
}
