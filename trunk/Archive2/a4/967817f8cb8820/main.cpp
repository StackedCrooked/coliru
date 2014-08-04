#include <iostream>
#include <string>

struct node {
    int info;
    node* next;
};

void print_list(const node * const list) {
    if (list == nullptr) return;
    std::cout << list->info;
    if (list->next != nullptr)
        std::cout << " > ";
    else std::cout << '\n';
    print_list(list->next);
}

node* reverse(node* head) {
    if (head->next == nullptr) return head;
    auto* r = reverse(head->next);
    head->next->next = head;
    head->next = nullptr;
    return r;
}

int main() {
    node* d = new node { 103, nullptr };
    node* c = new node { 102, d };
    node* b = new node { 101, c };
    node* a = new node { 100, b };

    print_list(a);
    print_list(reverse(a));
}