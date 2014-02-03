#include <functional>
#include <set>

struct T {
    int val;
    bool operator <(const T& other) const {
        return (this->val < other.val);
    }
};

template<class T>
bool operator<(const std::reference_wrapper<T> lhs, const std::reference_wrapper<T> rhs)
{return lhs.get()<rhs.get();}

int main() {
    std::set<std::reference_wrapper<T>> s;
    T a{5};
    s.insert(a);
}