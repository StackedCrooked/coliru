#include <map>
#include <string>

using namespace std;

using Map = map<string, int>;

Map worker(Map&& data)
{
    for (auto& el : data)
        el.second *= -1;

    return std::move(data);
}

#include <cassert>
#include <iostream>
#include <future>

int main()
{
    Map global
            { { "one", 1 },
              { "two", 2 },
              { "three", 3 } };

    auto background = async(worker, std::move(global));
    
    assert(global.empty());    // data now owned by the worker thread!

    global = background.get(); // await the result from the worker

    for (auto const& el: global) // now the data is owned by the main thread
        std::cout << el.first << ": " << el.second << "\n";
}
