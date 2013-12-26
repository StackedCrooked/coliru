#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <future>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void output_from_thread() {
    std::ostringstream os;
    os << "Thread: " << std::this_thread::get_id() \
        << " hash: " << std::hash<std::thread::id>()(std::this_thread::get_id()) << std::endl;
    std::cout << os.str();
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::vector<std::future<void>> results;
    for (int i = 0; i < 15; ++i) {
        results.emplace_back(std::async(std::launch::async, []() {output_from_thread();}));
    }
    
    for (auto &res: results) {
        res.get();
    }
}
