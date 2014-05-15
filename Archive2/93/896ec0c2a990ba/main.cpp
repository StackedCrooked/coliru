#include <cstdlib>
#include <time.h>
#include <iostream>

struct Node{
    int body;
    Node* next;
};

Node* construct(int len){
    Node *head, *ptr, *end;
    head = new Node();
    ptr = head;
    ptr->body = 0;
    for(int i=1; i<len; i++){
        end = new Node();
        end->next = NULL;
        end->body = i;

        ptr->next = end;
        ptr = end;
    }
    return head;
}

int len(Node* ptr){
    int i=1;
    while(ptr->next){
        ptr = ptr->next;
        i += 1;
    }
    return i;
}

void trim(Node* head){
    Node *last, *cur;
    cur = head;
    while(cur->next){
        last = cur;
        cur = cur->next;
    }
    last->next = NULL;
}

void tumble_trim(Node* head){ // This one uses less copies per traverse
    Node *a, *b;
    a = head;
    while(true){
        if(!a->next){
            b->next = NULL;
            break;
        }
        b = a->next;
        if(!b->next){
            a->next = NULL;
            break;
        }
        a = b->next;
    }
}

int main(){
    int start;
    Node *head;

    start = clock();
    head = construct(100000);
    for(int i=0; i<5000; i++){
        trim(head);
    }
    std::cout << clock()-start << std::endl;

    start = clock();
    head = construct(100000);
    for(int i=0; i<5000; i++){
        tumble_trim(head);
    }
    std::cout << clock()-start << std::endl;
}