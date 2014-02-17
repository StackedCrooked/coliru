struct ListElement {
    ListElement * next;
    //int value;//irrelevant here
};

void joinLast1(ListElement * & l1, ListElement * & l2) {
    if (l1->next == nullptr) {//one element left in first list
        l1->next = l2;//link lists
        l2 = l1;//move begin of second list
        l1 = nullptr;//unlink lists
    } else {//more than one element in first list
        joinLast1(l1->next, l2);//iterate through first list
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
    test1("1 – ", &joinLast1);
    test1("2 – ", &joinLast2);
    test1("3 – ", &joinLast3);
    test1("4 – ", &joinLast4);
    test2("1 – ", &joinLast1);
    test2("2 – ", &joinLast2);
    test2("3 – ", &joinLast3);
    test2("4 – ", &joinLast4);
}