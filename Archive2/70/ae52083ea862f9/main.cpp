#include <iostream>
#include <cassert>

using namespace std;

class Node {
  private:
    int data = 0;
    int next = 0;

  public:
    int getData() { return data; }
    void setData(int new_data) { data = new_data; }

    int getNext() { return next; }
    void setNext(int new_next) { next = new_next; }
};

class LinkedList {
    Node head;
    Node head2;

  public:
    bool isEmpty() {
        if (head.getData() == 0) {
            return true;
        }
        return false;
    }
};

void testNode() {
    Node aNode;
    aNode.setData(15);
    aNode.setNext(23);

    assert(aNode.getData() == 15);
    assert(aNode.getNext() == 23);
}

void testEmptyLinkedList() {
    LinkedList ll;
    assert(ll.isEmpty() == true);
}

int main() {
    testEmptyLinkedList();
}
