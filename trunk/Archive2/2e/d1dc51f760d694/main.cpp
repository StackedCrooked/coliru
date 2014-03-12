#include <string>
#include <tuple>
#include <functional>
#include <vector>
#include <algorithm>

// This is the query function, it compiles fine
template<typename T, typename UnaryPredicate>
T query(T const& input, UnaryPredicate&& pred)
{
    T result;
    std::copy_if(std::begin(input), std::end(input), 
                 std::back_inserter(result), std::forward<UnaryPredicate>(pred));
    return result;
}

// Define my Row, with each column having a type
using Row = std::tuple<int, float, std::string>;

int main()
{
    // Create a sample vector of Rows
    std::vector<Row> vec;
    for(size_t i = 0; i < 100; ++i)
        vec.emplace_back(i, 5.0f, "hello");

    // This is how I would perform the query 
    // **** This is the line that doesn't compile due to template arg deduction failure ****
    auto result = query(vec, [](Row const& row) -> bool { return true; });
    return 0;
}
