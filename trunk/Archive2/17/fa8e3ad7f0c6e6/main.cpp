#include <cstdlib>
#include <iostream>
using namespace std;
template <typename T>
class DoublyLinkedList; // class declaration

// list node
template <typename T>
class DListNode {
private: T obj;
  DListNode *prev, *next;
  friend class DoublyLinkedList<T>;
public:
  DListNode(T object = T(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(object), prev(p), next(n) {}
  T getElem() const { return obj; }
  DListNode * getNext() const { return next; }
  DListNode * getPrev() const { return prev; }
};

// doubly linked list
template <typename T>
class DoublyLinkedList {
protected: DListNode header, trailer;
public:
  DoublyLinkedList() : header(0), trailer(0) // constructor
  { /*header.next = &trailer; trailer.prev = &header;*/ }
  DoublyLinkedList(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
};
// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

// extend range_error from <stdexcept>
template <typename T>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  header.next = &trailer; trailer.prev = &header;

  DListNode<T>* current = dll.getFirst();
  while (current != dll.getAfterLast()) {
      T newObj = current->obj;
      insertLast(newObj);
      current = current->getNext();
  }

}
// assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  delete this;

  header.next = &trailer; trailer.prev = &header;

  DListNode<T>* current = dll.getFirst();
  while (current != dll.getAfterLast()) {
      T newObj = current->obj;
      insertLast(newObj);
      current = current->getNext();
  }

  return *this;
}
// insert the object to the first of the linked list
template <typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
template <typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
// remove the first object of the list
template <typename T>
T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}
// remove the last object of the list
template <typename T>
T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}
// destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
template <typename T>
T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
template <typename T>
T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
template <typename T>
T DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  while (current != dll.getAfterLast()) {
      out << current->getElem() << '\n';
      current = current->getNext();
  }
  return out;
}