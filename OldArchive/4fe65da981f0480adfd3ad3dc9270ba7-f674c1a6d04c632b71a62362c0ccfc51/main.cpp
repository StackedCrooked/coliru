#include <future>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

using namespace std;

// sample: return the largest integer value or 42
int some_background_worker(vector<string> data)
{
    if (ref_data.empty()) return 42;

    vector<int> values(ref_data.size());
    transform(begin(ref_data), end(ref_data), begin(values), 
            [](string const& s) { return stoi(s); });
    return *max_element(begin(values), end(values));
}

struct Parser
{
    future<int> parse(string const& msg) const
    {
        istringstream iss(msg);
        istream_iterator<string> f(iss), l;

        const vector<string> data { f, l };

        // now dispatch a thread to do the work
        return async(some_background_worker, std::move(data));
    }
};

int main()
{
    const std::vector<string> fifoQueue { "1 3 9 -1 2", "32389 3102 -34 -888", "-42 -889", "" };

    vector<future<int>> results;

    {
        Parser parser;
        for(auto& msg : fifoQueue)
            results.push_back(parser.parse(msg));
    }

    // all parser data has been throroughly destroyed, before we might even
    // start the workers
    for(auto& fut: results)
        std::cout << "result of worker: " << fut.get() << "\n";
}
