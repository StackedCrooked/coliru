#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

void function(std::string* a_s)
{
    std::ostringstream s;
    s << a_s;
    *a_s = s.str();
}

int main()
{
    std::vector<std::string> strings(4);
    std::vector<std::thread> threads(strings.size());
    int tid_idx = 0;

    for (auto& s: strings) threads[tid_idx++] = std::thread(function, &s);
    for (auto& t: threads) t.join();
    for (auto const& s: strings) std::cout << &s << ", " << s << "\n";

    return 0;
}


