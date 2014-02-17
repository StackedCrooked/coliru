#include <iostream>
#include <string>
#include <vector>


template <typename T, typename sepT = char>
void print2d(const T &data, sepT sep = ',') {
    for(auto i = std::begin(data); i < std::end(data); ++i) {
        auto& tmp = *i;
        for(auto j = std::begin(tmp); j < std::end(tmp); ++j) {
            std::cout << *j << sep;
        }
        std::cout << std::endl;
    }
}

int main(){
    std::vector<std::vector<int> > v = {{11}, {2,3}, {33,44,55}};
    print2d(v);

    int arr[2][2] = {{1,2},{3,4}};
    print2d(arr);

    return 0;
}