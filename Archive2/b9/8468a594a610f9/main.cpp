#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <algorithm>
#include <functional>
#include <random>

#include <set>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <deque>
#include <vector>
#include <array>

struct ptimer
{
    ptimer() : start_(std::chrono::system_clock::now()) { }
    ~ptimer() { std::cout << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start_).count() << "us" << std::endl; }
    const std::chrono::time_point<std::chrono::system_clock> start_;
};

static void mk_str_collection(const std::function<void(size_t, std::string&&)>& add)
{
    size_t n = 0;
    for (char i = 'A'; i <= 'Z'; i++) {
        for (char j = 'A'; j <= 'Z'; j++) {
            for (char k = 'A'; k <= 'Z'; k++) {
                add(n++, {k, j, i});
            }
        }
    }
}

template<typename T>
static void run_test(const std::string& name, const std::vector<std::string>& needles, const T& haystack, const std::function<typename T::const_iterator(const std::string&)>& find, const size_t n)
{
    std::cout << std::setw(20) << name << "(size=" << std::distance(haystack.begin(), haystack.end()) << ", searches=" << n << "): ";
    
    ptimer pt;
    std::for_each(std::begin(needles), std::begin(needles) + n, [&haystack, &find](const auto& needle)
    {
        const auto it = find(needle);
        const volatile auto found = (it != haystack.end()); // I CAN HAS NO OPTIMIZE
        (void) found;
    });
}

int main()
{
    // number of searches
    static const auto search_cnt = 1000;

    // the strings to search for
    static const auto needles = []() -> std::vector<std::string> {
        std::vector<std::string> needles;
        mk_str_collection([&](auto, auto&& s){ needles.emplace_back(s); });
        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(needles), std::end(needles), g);
        return std::move(needles);
    }();
    
    {
        std::forward_list<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace_front(s); });
        run_test("forward_list", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    {
        std::list<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace_front(s); });
        run_test("list", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    {
        std::deque<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace_front(s); });
        run_test("deque", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    {
        std::set<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace(s); });
        run_test("set", needles, coll, [&coll](auto& s){ return coll.find(s); }, search_cnt);
    }
    
    {   // slow linear search for std::set
        std::set<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace(s); });
        run_test("set linear", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    {
        std::unordered_set<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace(s); });
        run_test("unordered_set", needles, coll, [&coll](auto& s){ return coll.find(s); }, search_cnt);
    }
    
    {   // slow linear search for std::unordered_set
        std::unordered_set<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace(s); });
        run_test("unordered_set linear", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    {
        std::vector<std::string> coll;
        mk_str_collection([&coll](auto, auto&& s){ coll.emplace_back(s); });
        run_test("vector", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    {
        std::array<std::string, 26 * 26 * 26> coll;
        mk_str_collection([&coll](auto n, auto&& s){ coll[n] = s; });
        run_test("array", needles, coll, [&coll](auto& s){ return std::find(std::begin(coll), std::end(coll), s); }, search_cnt);
    }
    
    std::cout << "Done." << std::endl;
}
