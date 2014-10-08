#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<string> allPossibleWrods(const string & original)
{
    // count amout of '?'
    vector<unsigned> positions;
    
    for (unsigned pos = 0; pos < original.size(); ++pos)
    {
        if (original[pos] == '?') positions.push_back(pos);
    }
    
    unsigned counter = positions.size();
    
    // make 2^counter amount of copies and make replacement
    cout << (2 << counter) << endl;
    
    vector<string> results;
    for (unsigned i = 0; i < (2 << counter) - 1; ++i)
    {
        results.push_back(original);
        for (unsigned j = 0; j < counter; j++)
            results[i][positions[j]] = (i& (2 << j)) ? '0' : '1';
    }
    
    return results;
    
}

int main()
{
    auto results = allPossibleWrods("?gah??k?");
    for (auto word: results)
        cout << word << " ";
    cout << endl;
    
    priority_queue<int, vector<int>, less<int>> s;
    for (auto i : {1, 2, 4, 5, 6})
        s.push(i);
        
    while(!s.empty())
        { cout << s.top() << " "; s.pop(); }
   
   return 0;
}
