#include <iostream>
#include <functional>
#include <vector>

template <typename T>
class eh {
private:
    std::vector<T> vec;
public:
    using block = std::function<void(T)>;
    void add(T x) { vec.push_back(x); }
    
    void traverse(block blk) {
        for (auto& i : vec)
            blk(i);
    }
    
    void traverse(block blk) const {
        for (const auto& i : vec)
            blk(i);
    }
};

int main(int, char*[]) {
    eh<int> x;
    x.add(1);
    x.add(2);
    x.add(3);
    x.traverse([](int el) {
        std::cout << el << '\n';
    });
    return 0;
}