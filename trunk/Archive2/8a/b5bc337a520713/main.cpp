#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>
#include <string>

template<class T>
struct MyLinkedList {
    struct MyLinkedListNode {
        MyLinkedListNode* getNext();
    };
};

template <class T>
typename MyLinkedList<T>::MyLinkedListNode* MyLinkedList<T>::MyLinkedListNode::getNext()
{
    return this -> next;
}

int main() {
	return 0;
}