#include <string>
#include <iostream>
using namespace std;

class Object {
private:
    std::string* type;
public:
    Object() {
        type = new std::string("Object");
    }
    Object(std::string* type) {
        this->type = type;
    }

    std::string* GetType() {
        return type;
    }
};

template <class T>
class Node : public Object {
private:
    Node *next;
    Node *prev;
    T value;
public:
    Node(Node* prev, T value) : Object(new std::string("Node")) {
        if (prev != NULL) {
            prev->next = this;
            this->prev = next;
        } 
        this->next = NULL;
        this->value = value;
    }
    ~Node() {
        delete next;
    }

    T GetValue() {
        return value;
    }

    Node* GetNext() {
        return next;
    }

    Node* GetPrev() {
        return prev;
    }
};

template<class T>
 class List : public Object {
private: 
    Node<T>* first;
    Node<T>* last;
    int length;
public:
    List() : Object(new std::string("List")) {
        first = NULL;
        last = NULL;
        length = 0;
    }
    ~List() {
        delete first;
        delete last;
    }

    void Add(T value) {
        if (first == NULL)
            first = new Node<T>(NULL, value);
        else if (last == NULL)
          last = new Node<T>(first, value);
        else
            last = new Node<T>(last, value);
        length++;
    }

    T Remove(T value) {
        Node<T>* temp = first;
        while(temp != NULL) {
            if(temp->GetValue() == value) {
                temp->GetPrev()->SetNext(temp->GetNext());
                temp->GetNext()->SetPrev(temp->GetPrev());
                delete temp;
                length--;
                return value;
            }
            temp = temp->GetNext();
        }
        return 0;
    }

    T Get(int index) {
        Node<T>* temp = first;
        int i = 0;
        while(temp != NULL) {
            if (i == index)
                return temp->GetValue();
            i++;
            temp = temp->GetNext();
        }
        return 0;
    }
 };

int main () {

    List<int> l;
    l.Add(5);
    l.Add(2);
    l.Add(6);
    l.Add(23);
    
    cout << "node 4 is:" << l.Get(3) << endl;
    
    return 0;
}