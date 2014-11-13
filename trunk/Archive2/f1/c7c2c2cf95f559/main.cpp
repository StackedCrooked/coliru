#include <iostream>
#include <memory>

template <typename T>
bool PointsToValidOrExpiredObject(const std::weak_ptr<T>& w) {
    return w.owner_before(std::weak_ptr<T>{}) || std::weak_ptr<T>{}.owner_before(w);
}


int main() {
    std::weak_ptr<int> wp1(std::make_shared<int>());
    std::weak_ptr<int> wp2;

    std::cout << std::boolalpha
              << PointsToValidOrExpiredObject(wp1) << '\n'
              << PointsToValidOrExpiredObject(wp2) << '\n';
}
