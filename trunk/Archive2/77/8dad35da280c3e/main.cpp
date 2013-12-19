#include <iostream>

struct node {
    node * next{nullptr};
    int digit;
    node(int digit) : digit{digit} {}
    ~node() {
        delete next;
    }
};

void appendList(node * & list, int newDigit) {
    if (list == nullptr) {//create first element if not present
        list = new node{newDigit};
    } else {//walk through to the end of the list and append
        appendList(list->next, newDigit);
    }
}

void reverseList(node * & current) {
    if (current != nullptr) {
        node * previous = nullptr;//last link shall be null
        while (current->next != nullptr) {//valid link
            node * const nextElement = current->next;//backup link
            current->next = previous;//link backwards
            previous = current;//backup current element pointer
            current = nextElement;//move forward in list
        }
        current->next = previous;//link backwards for last element/new start
    }
}

void print(const node * list) {
    if (list == nullptr) {
        std::cout << "empty list" << std::endl;
    } else {
        std::cout << "{" << list->digit << " ";
        while (list->next != nullptr) {
            list = list->next;
            std::cout << list->digit << " ";
        }
        std::cout << "}" << std::endl;
    }
}

void linkedListTest() {
    node * list = nullptr;
    print(list);
    std::cout << "↔";
    reverseList(list);
    print(list);
    for (const auto & elem : {1,2,3,4,5}) {
        appendList(list, elem);
        print(list);
        std::cout << "↔";
        reverseList(list);
        print(list);
    }
}

int main() {
    linkedListTest();
}