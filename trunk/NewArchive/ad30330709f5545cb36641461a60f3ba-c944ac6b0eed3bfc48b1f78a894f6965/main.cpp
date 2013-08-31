#include <iostream>
#include <functional>
#include <unordered_map>

typedef std::function<int(int)> Callback;

int f(int i, Callback callback) {
    if (i <= 2) return 1;
    return callback(i-1) + callback(i-2);
}

int main(void) {

    std::unordered_map<int, int> values;

    Callback callback = [&](int i) {
        if (values.find(i) == values.end()) {
            values.emplace(i, f(i, callback));
        }
        return values.at(i);
    };

    std::cout << f(20, callback) << std::endl;
}
