#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<std::string> badDatastructure = { "B/0", "B/1", "B/2", "B/3", "C/0", "C/1", "C/2", "C/3", "D/1", "D/2" };

    auto rand = std::rand() % badDatastructure.size();
    auto album = badDatastructure[rand][0];
    std::stable_partition(std::begin(badDatastructure), std::end(badDatastructure), [album](const auto& elem) {
        return elem[0] == album;
    });
}