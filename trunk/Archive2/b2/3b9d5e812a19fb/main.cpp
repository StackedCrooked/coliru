#include <string>
#include <iostream>

using namespace std; 

class DoublyLinkedList;
class Node
{
    friend DoublyLinkedList;
    public:
        Node* next;
        Node* prev;
        string* data;
        Node(){next = NULL; prev = NULL; data = NULL;}
        ~Node(){if(next!=NULL)delete next; if(data!=NULL)delete data;}
};
class DoublyLinkedList {
    Node *begin = NULL;
    Node *end = NULL;
public:
    ~DoublyLinkedList() {
        if(begin!=NULL)delete begin;    
    }
    bool find(const string&);
    
    bool empty() {
        return begin == end;
    }
    
    void add(string* a) {
        if(end!=NULL){
        end->next = new Node();
        end->next->data = a;
        end = end->next;
        }
        else {
            begin = new Node();
            begin->data = a;
            end = begin;
        }
    }
  
};
bool DoublyLinkedList::find(const string& s)
{
    if(empty())
        return false;
    else
    {
        Node* tempNode = begin;
        do{
            if(*(tempNode->data) == s)
            {
                return true;
            }
            tempNode = tempNode->next;
        } while(tempNode != NULL);
        return false;
    }
}


int main() {
    DoublyLinkedList l;
    l.add(new string("ABC"));
    l.add(new string("DEF"));
    l.add(new string("GHI"));
    
    cout << l.find("DEF");
}