#include <iostream>
#include <string>
#include <vector>

struct ListElement {
    ListElement * next;
    int value;
};

void joinLast(ListElement *&l1, ListElement *&l2) {
    if (l1->next == nullptr) {//last element in l1
        l1->next = l2;//glue lists
        l2 = l1;//set new front of l2
        l1 = nullptr;//remove link
    } else {
        joinLast(l1->next, l2);
    }
}

void joinLast2(ListElement *&l1, ListElement *&l2) {
    if (l1->next == nullptr) {//last element in l1
        l1->next = l2;//glue lists
        l2 = l1;//set new front of l2
        l1 = nullptr;//remove link
    } else {
        ListElement * help = l1;
        while (help->next->next != nullptr) {
            help = help->next;
        }
        help->next->next = l2;//glue lists
        l2 = help->next;//new l2
        help->next = nullptr;//remove link
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto& el : vec) {
        os << el << ' ';
    }
    return os;
}

int main() {
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    typedef int euro;
    euro e;
    e + 2;
}
