#include <iostream>
#include <string>
#include <vector>

struct Node {
    int Value;
    Node* next;
    Node* prev;
};

void Invert(Node* head) {
    Node* node = head;
    while(node->next!=NULL) {
        Node* temp = node->next;
        node->next = node->prev;
        node->prev = temp;
        node = temp;
    };
        Node* temp = node->next;
        node->next = node->prev;
        node->prev = temp;
        node = temp;
}

int main()
{
    Node* node1 = new Node;
    Node* node2 = new Node;
    Node* node3 = new Node;
    Node* node4 = new Node;
    node1->Value = 0;
    node1->prev=NULL;
    node1->next = node2;
    node2->Value = 1;
    node2->prev=node1;
    node2->next = node3;
    node3->Value = 2;
    node3->prev=node2;
    node3->next = node4;
    node4->Value = 3;
    node4->prev=node3;
    node4->next = NULL;
    
    Node* temp = node1;
    while(temp->next!=NULL) {
        std::cout<<temp->Value;
        temp = temp->next;
    };
    std::cout<<temp->Value;
    std::cout<<"\n";
    
    Invert(node1);
    
    temp = node4;
    while(temp->next!=NULL) {
        std::cout<<temp->Value;
        temp = temp->next;
    };
    std::cout<<temp->Value;
}
