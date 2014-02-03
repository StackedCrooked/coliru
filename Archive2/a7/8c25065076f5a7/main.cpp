#include <cassert>
#include <iostream>
#include <string>

struct Node {
    std::string val;
    Node *next;
};

Node *makeListImpl() {
    std::string s;
	return (std::cin >> s) ? new Node{s, makeListImpl()} : 0;
}

Node *makeList() {
    Node *head = makeListImpl();
    return head ? head : new Node();
}

int main() {
    Node *l = makeList();
    while (l) {
        std::cout << '"' << l->val << "\"\n";
        l = l->next;
    }
}