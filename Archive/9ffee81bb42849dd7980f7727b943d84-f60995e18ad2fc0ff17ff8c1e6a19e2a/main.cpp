#include <vector>
#include <iostream>

std::vector<std::vector<int>> stuff_to_delete;

void delete_stuff(int index) {
    for(auto&& i : stuff_to_delete[index]) {
        std::cout << "deleted " << i << "\n";
    }
}

void actual_delete(std::vector<int> items) {
    // save arguments in a global varible
    stuff_to_delete.push_back(std::move(items));

    // it doesn't matter that I am passing arguments through a global variable; this is totally stateless
    int index = stuff_to_delete.size()-1;
    delete_stuff(index);
}

int main () {}
