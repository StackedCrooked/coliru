#include <iostream>
#include <vector>
using namespace std;

template <typename U, typename T>
vector<T> append_vec(const std::initializer_list<U> & lst1, const vector<T> &lst2) {
    vector<T> inner (lst1.begin(), lst1.end());
    inner.insert(inner.end(), lst2.begin(), lst2.end());
    return inner;
}

int main() {
        
    vector<string> suffix {{"1", "2", "3"}};
    vector<vector<string>> v;
    v = {{
        append_vec({"a", "b", "c"}, suffix),
        {"aa", "bb"},
        append_vec({"xyz", "yzx", "zxy"}, suffix),
        {}
    }};
    
    for (const auto &c : v){
        cout << "*    ";
        for(const auto &d : c){
            cout << d << ' ';
        }
        cout << endl;
    }
    
    return 0;
}