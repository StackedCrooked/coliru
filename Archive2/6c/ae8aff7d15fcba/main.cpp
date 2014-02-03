struct ListElement {
    ListElement * next;
};

void joinLast1(ListElement * & l1, ListElement * & l2) {
    if (l1->next == nullptr) {//end of first list
        l1->next = l2;//glue lists
        l2 = l1;//reset beginning of second list
        l1 = nullptr;//cut connection from last element of first list
    } else {
        joinLast1(l1->next, l2);//walk through first list
    }
}

void joinLast2(ListElement * & l1, ListElement * & l2) {
    if (l1->next == nullptr) {
        l1->next = l2;
        l2 = l1;
        l1 = nullptr;
    } else {
        ListElement * help = l1;
        while (help->next->next != nullptr) {
            help = help->next;
        }
        help->next->next = l2;
        l2 = help->next;
        help->next = nullptr;
    }
}

void joinLast3(ListElement * & l1, ListElement * & l2) {
    ListElement * * help = &l1;
    while ((*help)->next != nullptr) {
        help = &(*help)->next;
    }
    (*help)->next = l2;
    l2 = *help;
    *help = nullptr;
}

#include <functional>

void joinLast4(ListElement * & l1, ListElement * & l2) {
    std::reference_wrapper<ListElement *> help = l1;
    while (help.get()->next != nullptr) {
        help = help.get()->next;
    }
    help.get()->next = l2;
    l2 = help.get();
    help.get() = nullptr;
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

int main() {
    {
        ListElement help4{nullptr};
        ListElement help3{&help4};
        ListElement help2{nullptr};
        ListElement help{&help2};
        ListElement * l1{&help};
        ListElement * l2{&help3};
        std::cout << *l1 << " : " << *l2 << std::endl;
        joinLast1(l1, l2);
        std::cout << *l1 << " : " << *l2 << std::endl;
    }
    {
        ListElement help4{nullptr};
        ListElement help3{&help4};
        ListElement help2{nullptr};
        ListElement help{&help2};
        ListElement * l1{&help};
        ListElement * l2{&help3};
        std::cout << *l1 << " : " << *l2 << std::endl;
        joinLast2(l1, l2);
        std::cout << *l1 << " : " << *l2 << std::endl;
    }
    {
        ListElement help4{nullptr};
        ListElement help3{&help4};
        ListElement help2{nullptr};
        ListElement help{&help2};
        ListElement * l1{&help};
        ListElement * l2{&help3};
        std::cout << *l1 << " : " << *l2 << std::endl;
        joinLast3(l1, l2);
        std::cout << *l1 << " : " << *l2 << std::endl;
    }
    {
        ListElement help4{nullptr};
        ListElement help3{&help4};
        ListElement help2{nullptr};
        ListElement help{&help2};
        ListElement * l1{&help};
        ListElement * l2{&help3};
        std::cout << *l1 << " : " << *l2 << std::endl;
        joinLast4(l1, l2);
        std::cout << *l1 << " : " << *l2 << std::endl;
    }
}