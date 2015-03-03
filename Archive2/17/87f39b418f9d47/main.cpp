#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;

template<class T>
struct trait
{
    static T append(const T&, const T&);
};

template<>
struct trait<std::vector<int>>
{
    static std::vector<int> append(const std::vector<int>& a, const std::vector<int>& b)
    {
        std::vector<int> r;
        r.insert(a.end(), b.begin(), b.end());
        return r;
    }
};

template<>
struct trait<string>
{
    static string append(const string& a, const string& b)
    {
        return a + b;
    }
};

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v)
{
    out << '{';
    auto last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i)
    {
        out << v[i];
        if (i != last) 
            out << ", ";
    }
    return out << '}';
}

int main()
{
    using std::cout;
    
    cout << trait<string>::append("hello", " world") << std::endl
         << trait<vector<int>>::append( {1,2,3}, {4,5,6} ) << std::endl;
}
