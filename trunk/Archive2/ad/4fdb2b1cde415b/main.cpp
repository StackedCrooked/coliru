#include<vector>

struct x {
    static const std::vector<int> y;
};

const std::vector<int> x::y = {1};

int main() {}