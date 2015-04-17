#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

struct Stats { int swaps_ = 0, compares_ = 0; };

std::ostream& operator<<(std::ostream& os, const Stats& s)
{
    return os << "{ swaps " << s.swaps_ << ", compares " << s.compares_ << " }";   
}

Stats selectionSort(std::vector<int>& a, int l, int r) {
    Stats stats;
    for (int i = l; i < r; i++) {
        int min = i;
        for (int j = i + 1; j <= r; j++) {
            if (a.at(j) < a.at(min)) min = j;
            ++stats.compares_;
        }   
        if (i != min) { swap(a.at(i), a.at(min)); ++stats.swaps_; }
    }
    return stats;
}


Stats bubbleSort(std::vector<int>& a, int l, int r) {
    Stats stats;
    bool flag = false;
    for (int i = l; i < r; i++) {
        for (int j = r; j > i; j--) {
            if (a.at(j-1) > a.at(j)) {
                if (flag == false) flag = true;
                swap(a.at(j - 1), a.at(j));
                ++stats.swaps_;
            }
            ++stats.compares_;
        }
        if (flag == false) break;
    }
    return stats;
}

int main()
{
    std::vector<int> v1{ 4, 8, 3, 8, 10, -1, 3, 20, 5 };
	
	std::vector<int> v1s = v1;
	std::cout << "sel " << selectionSort(v1s, 0, v1s.size() - 1);
	
	std::vector<int> v1b = v1;
	std::cout << ", bub " << bubbleSort(v1b, 0, v1b.size() - 1) << '\n';
	assert(v1s == v1b);
    for (int i : v1s) std::cout << i << ' ';
    std::cout << '\n';
}