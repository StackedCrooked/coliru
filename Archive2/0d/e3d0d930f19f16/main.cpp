#include <vector>
#include <algorithm>

template <typename T>
struct SimpleVector {
    std::vector<T> data;

    virtual ~SimpleVector() {}
};


template <typename T>
struct SortableVector : public SimpleVector<T> {
    void sort() {
        std::sort(this->data.begin(), this->data.end());
    }
};

#include <iostream>

int main()
{
    SortableVector<std::string> sv;
    sv.data = {"one","two","three","four"};

    sv.sort();
    for(auto& s : sv.data)
        std::cout << s << ' ';
}
