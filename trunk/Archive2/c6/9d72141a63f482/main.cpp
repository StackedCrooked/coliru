#include <initializer_list>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <string>
using namespace std;

struct Record
{
    string first_name, last_name;
};

class Indexer
{
    typedef vector<Record> Container;
    typedef Record *Handle;
    Container values;
    unordered_map<string, Handle> first_name_index, last_name_index;

public:
    Indexer(Container &&x) : values(move(x))
    {
        for(auto &x : values)
        {
            first_name_index[x.first_name] = &x;
            last_name_index[x.last_name] = &x;
        }
    }
    const Record &first_name(const string &x)
    {
        return *first_name_index[x];
    }
    const Record &last_name(const string &x)
    {
        return *last_name_index[x];
    }
};

int main()
{
    vector<Record> v = {{"F1", "L1"}, {"F2", "L2"}};
    Indexer x(move(v));

    cout << x.first_name("F1").last_name << endl;
    cout << x.first_name("F2").last_name << endl;

    cout << x.last_name("L1").first_name << endl;
    cout << x.last_name("L2").first_name << endl;
}