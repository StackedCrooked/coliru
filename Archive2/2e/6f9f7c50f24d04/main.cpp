#include <iostream>
#include <stdexcept>

template <class T> class Node;
template <class T> class List;

template <class T>
class Node {
public:
    Node(T t) :
        next(nullptr),
        data(t)
    {}
    
    ~Node() {}
    
    Node<T>* get_next() {return next;}
    T get_data() {return data;}
    
    void set_next(Node<T>* n) {next = n;}
    void set_data(T d) {data = d;}
private:
    Node<T>* next;
    T data;
    
    friend class List<T>;
};

template <class T>
class List {
public:
    List() :
        head(nullptr),
        size(0)
    {}
    
    ~List() {
        Node<T>* next;
        
        while (head != nullptr) {
            if (head->next != nullptr) {
                next = head->next;
                delete head;
                head = next;
            } else {
                delete head;
                break;
            }
            
        }
    }
    
    T get(unsigned int pos) const {
        if (pos >= size)
            throw std::invalid_argument("set() has an invalid pos");
        else {
            if (size == 1)
                return head->data;
            
            Node<T>* current = head;
            
            for (unsigned int i = 0; i < pos; ++i) {
                current = current->next;
            }
            
            return current->data;
        }
    }
    
    void set(unsigned int pos, T d) {
        if (pos >= size)
            throw std::invalid_argument("set() has an invalid pos");
        else {
            if (pos == 0)
                head->data = d;
            
            Node<T>* current = head;
            
            for (unsigned int i = 0; i < pos; ++i) {
                current = current->next;
            }
            
            current->data = d;
        }
    }
    
    void push_back(T d) {
        if (size == 0 && head == nullptr) {
            head = new Node<T>(d);
            ++size;
        } else {
            Node<T>* current = head;
            
            while (current->next != nullptr) {
                current = current->next;
            }
            
            current->next = new Node<T>(d);
            std::cout << "Pushback: " << current->next->data << '\n';
            ++size;
        }
    }
    
    unsigned int length() {return size;}
private:
    Node<T>* head;
    unsigned int size;
};

int main()
{
    Node<float> node(1.0);
    std::cout << "Node get: " << node.get_data() << '\n';
    node.set_data(2.5);
    std::cout << "Node get after set: " << node.get_data() << '\n';
    
    List<int> list;
    list.push_back(1);
    
    std::cout << "List set: " << list.get(0) << '\n';
    
    list.set(0,0);
    std::cout << "List[0] set to: " << list.get(0) << '\n';
    
    try {
        list.set(1,200);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << '\n';
    }
    return 0;
}