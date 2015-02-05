#include <iostream>
#include <vector>

template<class BrokenIt>
int sum(BrokenIt begin, BrokenIt end) {
    int tot = 0;
    while(begin != end) {
        tot += *begin++;
    }
    return tot;
}

int main() {
    std::vector<int> myints = {1,2,3,4,5,6,7,8,9};
    std::cout << sum(myints.begin(), myints.end()) << "\n";
    return 0;
}
