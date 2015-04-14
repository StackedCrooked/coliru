#include <iostream>

using namespace std;

struct node{
    int data;
    struct node *next, *prev;
};

class doubleLinkList{
    int i;
    int count = 0;
public:
    struct node* head;
    void insert(int data, int position){
        if(count = 0){
            head-> data = data;
            count++;
        }
        if(position = 1 && count > 0){
            struct node* new_node;
            new_node->data = data;
            new_node->next = &head;
            head->prev=&new_node;
            *head = new_node;
        }

}
};


void verifyHeadData(){
    doubleLinkList headtest;
    headtest.insert(5,1);
    int u = headtest.head->data;
    if(u = 5){
        cout<<"All's quiet on the western front. Head verified." << endl;
    }
    else{
        cout<<"Problem - head." << endl;
    }
};

void verifyInsertionFront(){
    doubleLinkList frontTest;
    frontTest.insert(5,1);
    frontTest.insert(2,1);
    int u = frontTest.head->data;
    if(u = 2){
        cout<<"All's quiet on the western front. Front verified." << endl;
    }
    else{
        cout<<"Problem - front." << endl;
    }
}



int main(){
    verifyHeadData();
    return 0;
}