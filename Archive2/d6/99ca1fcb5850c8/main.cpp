//#pragma once

template<class T>
class TLL;

template<class T>
class TLLNode{
    friend TLL<T>;
public:
    TLLNode(T data);
    //typedef TLLNode<T>* TLLPtr;
private:
    TLLNode<T> data;
    TLLNode *next;

};

template<class T>
TLLNode<T>::TLLNode(T dataIn) : data(dataIn){

}

template<class T>
using TLLPtr = TLLNode<T>*;

#include <iostream>
//#include"TLLNode.h"
using std::cout;
using std::endl;

template<class T>
class TLL{
public:
    TLL();
    TLL(const TLL&);
    void insert(T);
    void display();
    ~TLL();
private:
    TLLPtr<T> head;
    TLLPtr<T> newNode;
    TLLPtr<T> curr;
    int size;
};

template<class T>
TLL<T>::TLL() : head(NULL), size(0){

}
// Not implemented yet
template<class T>
TLL<T>::TLL(const TLL& obj){

}
template<class T>
void TLL<T>::insert(T data){
    if (head == NULL)
        head = new TLLNode<T>(data);
    else{
        newNode = new TLLNode<T>(data);
        newNode->next = head;
        head = newNode;
    }
}
template<class T>
void TLL<T>::display(){
    curr = head;
    while (curr != NULL){
        cout << curr->data << endl;
        curr = curr->next;
    }
}
template<class T>
TLL<T>::~TLL(){
    while (head != NULL){
        curr = head;
        head = head->next;
        delete curr;
    }
}

int main() {
}