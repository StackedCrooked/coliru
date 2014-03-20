struct ListElement {
    ListElement * next;
    //int value;//irrelevant here
};

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

void joinLast2(ListElement *&l1, ListElement *&l2) {
    if (l1->next == nullptr) {//l1 has only one element
        l1->next = l2;//link element with l2
        l2 = l1;//reset l2
        l1 = nullptr;//remove element from l1
    } else {
        joinLast2(l1->next, l2);//iterate over list
    }
}

void joinLast(ListElement *&l1, ListElement *&l2) {
    if (l1->next == nullptr) {//l1 has only one element
        l1->next = l2;//link element with l2
        l2 = l1;//reset l2
        l1 = nullptr;//remove element from l1
    } else {
        ListElement * last_help = l1;
        while (last_help->next != nullptr) {
            last_help = last_help->next;
        }
        //last_help->next == nullptr
        //last_help is last element of l1
        ListElement * prelast_help = l1;
        while (prelast_help->next != last_help) {
            prelast_help = prelast_help->next;
        }
        //prelast_help->next == last_help
        //prelast_help predecessor of last element of l1
        prelast_help->next = nullptr;//unlink last element from l1
        last_help->next = l2;//list previous last element of l1 with l2
        l2 = last_help;//reset l2
    }
}

int wizard(int x, int y, int z) {
    if (x+y == 2) {
        return 2 * z;
    } else if (x+y > 2) {
        return (x+y) * wizard(x+y-1, 0, z);
    } else {
        return 0;
    }
}

int main() {
    test1("test1 – ", &joinLast);
    test2("test2 – ", &joinLast);
}