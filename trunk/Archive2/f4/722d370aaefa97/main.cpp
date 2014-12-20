#include <iostream>

template<typename T> class List;
template<typename T> std::ostream& operator<<(std::ostream&, const List<T>&);

template<typename T>
class List {
private:
    struct Item {
        T value;
        Item *next;
        Item *prev;

        Item(const T &value, Item *next, Item *prev)
                : value(value), next(next), prev(prev) {
        }
    };

    Item *head;
    Item *tail;
    int size;
public:
    List() : head(), tail(), size() {}
    ~List() {}
    List(const List&) = delete;    
    List& operator=(const List &) = delete;    
    friend std::ostream& operator<< <>(std::ostream&, const List<T>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    typename List<T>::Item* p = list.head;
    while (p != NULL) {
        os << p->value << " ";
        p = p->next;
    }
    return os;
}

int main()
{
    List<int> x;
    std::cout << x;
}