    #include <iostream>
    using namespace std;
     
    #ifndef PRIORITY_QUEUE_H_
    #define PRIORITY_QUEUE_H_
     
    #ifndef NULL
    #define NULL ((void *) 0)
    #endif
    using std::cout;
    using std::ostream;
     
     template<class P, class T>
    class PriorityQueue;
     
     template<class P, class T>
    class PriorityQueueElement {
    public:
    T data;
    P priority;
    friend class PriorityQueue<P,T>;
    PriorityQueueElement() {
    }
    PriorityQueueElement(const T& data, const P& priority) :
    data(data), priority(priority) {
     
    }
     
    //...
     
    };
     
    template<class P, class T>
    class PriorityQueue {
    class Node;
     
    //...
     
    public:
    class Iterator; //TODO make this class
     
    //...
     
    Iterator begin() const;
    Iterator end() const;
    };
    template<class P, class T>
    typename PriorityQueue<P, T>::Iterator PriorityQueue<P, T>::begin() const {
    //TODO make this function
    return NULL;
    }
     
    template<class P, class T>
    typename PriorityQueue<P, T>::Iterator PriorityQueue<P, T>::end() const {
    //TODO make this function
    return NULL;
    }
     
    template<class P, class T>
    class PriorityQueue<P, T>::Iterator {
     
    //...
     
    friend class PriorityQueue<P, T> ;
    public:
    Iterator() /*:
    PQ(NULL), index(0)*/ {
    }
     
    //...
     
    Iterator& operator++();
     
    //...
     
    };
     
    template<class P, class T>
    auto PriorityQueue<P, T>::Iterator::operator++() -> Iterator& {
    //TODO make this function
    return *this;
    }
     
    template<class P, class T>
    class PriorityQueue<P, T>::Node {
    friend class PriorityQueue;
    friend class Iterator;
    PriorityQueueElement<P,T> item;
    PriorityQueue<P, T>::Node* nextNode;
    Node() :
    nextNode(NULL) {
    }
     
    //...
     
    };
     
    //...
     
    #endif /* PRIORITY_QUEUE_H_ */
     
     
     
    int main() {
    return 0;
    }