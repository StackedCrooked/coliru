#include <future>
#include <vector>
#include <iostream>

int fct(int i) { return i; }
void processResult(int value) { std::this_thread::sleep_for(std::chrono::milliseconds(100));  std::cout << value; }

void processResult_async(std::future<int>& f) { return processResult(f.get()); }

void bar(const std::vector<int>& container)
{
    std::vector<std::future<int>> futureList;
    for (auto elem : container)
    {
        futureList.push_back(std::async(fct, elem));
    }

    // start remaining processes

    // use the results
    std::vector<std::future<void>> results;
    for (auto& elem : futureList)
    {
        results.push_back(std::async(std::launch::async, processResult_async, std::ref(elem)));
    }
}

int main()
{
    const auto start = std::chrono::system_clock::now();
    bar({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    const auto end = std::chrono::system_clock::now();
    const auto diff = end - start;
    std::cout  << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " milliseconds" << std::endl;
    return 0;
}
