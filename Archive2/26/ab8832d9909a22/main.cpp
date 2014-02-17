struct ListElement {
    ListElement * next;
    //int value;//irrelevant here
};

void joinLast (ListElement *&l1, ListElement *&l2) {
    ListElement *help1 = l1 -> next;
    ListElement *help2 = l1;
    while(help1 -> next != nullptr){
        help1 = help1 -> next;
        help2 = help2 -> next;
    }
    help1 -> next = l2;
    help2 -> next = nullptr;
    l2 = help1;
}

#include <iostream>

std::ostream& operator<<(std::ostream & out, const ListElement & node) {
    out << &node;
    if (node.next != nullptr) {
        out << " " << *node.next;
    } else {
        out << " 0";
    }
    return out;
}

#include <functional>
#include <string>

void test1(const std::string & name, std::function<void(ListElement*&, ListElement*&)> func) {
    ListElement help4{nullptr};
    ListElement help3{&help4};
    ListElement help2{nullptr};
    ListElement help{&help2};
    ListElement * l1{&help};
    ListElement * l2{&help3};
    std::cout << name << *l1 << " : " << *l2 << std::endl;
    func(l1, l2);
    std::cout << name << *l1 << " : " << *l2 << std::endl;
}

void test2(const std::string & name, std::function<void(ListElement*&, ListElement*&)> func) {
    ListElement help{nullptr};
    ListElement * l1{&help};
    ListElement * l2{nullptr};
    std::cout << name << *l1 << " : " << l2 << std::endl;
    func(l1, l2);
    std::cout << name << l1 << " : " << *l2 << std::endl;
}

int main() {
    test1("schaller – ", &joinLast);
    test2("schaller – ", &joinLast);//crash
}