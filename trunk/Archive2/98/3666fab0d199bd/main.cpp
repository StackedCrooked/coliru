#include<unordered_map>
#include<iostream>
#include<memory>
#include<iterator>

using namespace std;

class DoubleLinkedList
{
    
public:
    DoubleLinkedList()
    {
        _data = 0;
        _next = nullptr;
        _prev = nullptr;
    }
    DoubleLinkedList(int a)
    {
        _data = a;
        _next = nullptr;
        _prev = nullptr;
    }
    
    DoubleLinkedList(const DoubleLinkedList& current)
    {
        _data = current._data;
        _next = current._next;
        _prev = current._prev;
    }
    DoubleLinkedList& operator=(const DoubleLinkedList&) = delete;
    
    void nextTo(DoubleLinkedList* nextNode)
    {
        this->_next = nextNode;
        nextNode->_prev = this;
    }
    
    void prevTo(DoubleLinkedList* prevNode)
    {
        this->_prev = prevNode;
        prevNode->_next = this;        
    }
    
    DoubleLinkedList* next()
    {
        return _next;
    }
    
    DoubleLinkedList* prev()
    {
        return _prev;
    }
    
    int data()
    {
        return _data;
    }
    
    void setData(int a)
    {
        _data = a;
    }
    
    void insertAfterThis(DoubleLinkedList* newNode)
    {
        if(!newNode)
            return;
        newNode->_next = this->_next;
        newNode->_prev = this;
        this->_next  = newNode;
    }
    
    void insertBeforeThis(DoubleLinkedList* newNode)
    {
        if(!newNode)
            return;
        newNode->_next = this;
        newNode->_prev = this->_prev;
        this->_prev  = newNode;
    }
    
    friend void deleteNode(DoubleLinkedList* node);
    
private:
    int _data;
    DoubleLinkedList* _next;
    DoubleLinkedList* _prev;    
    
};

void deleteNode(DoubleLinkedList* node)
{
    if(node->_prev)
        node->_prev->_next = node->_next;
    if(node->_next)
        node->_next->_prev = node->_prev;
    node->_next = nullptr;
    node->_prev = nullptr;
    node->_data = 0;
    delete node;
}

class DoubleLinkedCache
{    
public:
    DoubleLinkedCache() = delete;
    DoubleLinkedCache(int val)
    {
        _start = new DoubleLinkedList(val);
        _end = _start;
        lookup.insert(make_pair(val, _start));
        _currentSize = 1;
    }
        
    void addElement(int val)
    {
        cout<<"cache before addition"<<endl;
        display();
        auto itr = lookup.find(val);
        if(itr == lookup.end())
        {
            if(_currentSize == _maxCap)
            {
                
                DoubleLinkedList* temp = _end;
                _end = _end->prev();
                lookup.erase(lookup.find(temp->data()));
                deleteNode(temp);
                _currentSize--;
            }
            DoubleLinkedList* temp = new DoubleLinkedList(val);
            _start->insertBeforeThis(temp);
            _start = temp;
            lookup.insert(make_pair(val, _start));
            _currentSize++;
        }
        else
        {
            DoubleLinkedList* temp = new DoubleLinkedList(*(itr->second));
            _start->insertBeforeThis(temp);
            _start = temp;
            if(_end == itr->second)
                _end = _end->prev();
            deleteNode(itr->second);
            lookup.erase(itr);
            lookup.insert(make_pair(val, _start));
            }
        cout<<"cache after addition"<<endl;
        display();
    }
    
    void display()
    {
        DoubleLinkedList* temp = _start;
        cout<<"cache at the moment ----> ";
        while (temp != _end)
        {
            cout<<temp->data()<<"<-->";
            temp = temp->next();
        }
        cout<<temp->data();
        cout<<endl;
            
    }
    
private:
    DoubleLinkedList* _start;
    DoubleLinkedList* _end;
    unordered_map<int, DoubleLinkedList* > lookup;
    int _currentSize;
    static const int _maxCap = 100;  
};


int main()
{   
    DoubleLinkedCache my(10);
    my.addElement(1);
    my.addElement(19);
    my.addElement(14);
    my.addElement(16);
    my.addElement(19);
    my.addElement(197);
    my.addElement(199);
    my.addElement(123);
    my.addElement(19321);
    my.addElement(1231542);
    my.addElement(123813);
    my.addElement(19);
    my.addElement(1);
    my.addElement(10); 
    return 0;
}