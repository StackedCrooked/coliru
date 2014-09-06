#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
using uint = unsigned int;

// Returns vector of indices of the closed larger element to the right
// 0 at a position means there is no larger element to the right
template <typename T> vector<uint> right_max(const vector<T>& input)
{
    vector<uint> result(input.size());
    
    stack<pair<uint,T>> s;
    
    for (uint i = 0; i < input.size(); ++i)
    {
        while (!s.empty() && s.top().second < input[i])
        {
            result[s.top().first] = i;
            s.pop();
        }
        
        s.push(make_pair(i, input[i]));
    }
    
    return result;
}

int main()
{
    vector<char> v = {'e', 'a', 'b', 'f', 'x', 'g', 'u'};
    auto r = right_max(v);
    for (auto&& e : r) cout << e << endl;
}
