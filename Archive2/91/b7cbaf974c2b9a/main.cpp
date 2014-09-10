#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    int count;
    std::cin >> count;
    if (!std::cin) {
        std::cerr << "unable to read input count\n";
        return 1;
    }
    std::vector<unsigned char> vec(count-1);
    int prev;
    std::cin >> prev;
    if (!std::cin) {
        std::cerr << "unable to read input #1\n";
        return 1;
    }
    for(int i=1; i<count; ++i) {
        int cur;
        std::cin >> cur;
        if (!std::cin) {
            std::cerr << "unable to read input #" << i << "\n";
            return 1;
        }
        vec[prev<cur?cur-prev:prev-cur] = 1;
        prev = cur;
    }
    if (std::accumulate(vec.begin(),vec.end(),0)==count-1) {
        std::cout << "Jolly\n";
    } else {
        std::cout << "Not jolly\n";
    }
    return 0;
}
