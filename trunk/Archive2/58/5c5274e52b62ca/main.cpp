#include <iostream>

template <class T>
class LinkedList;

template <class T>
class ListElement
{
    friend LinkedList<T>;
private:
    ListElement(T const&, ListElement<T>*);
    T datum;
    ListElement<T>* next;
};

template <class T>
ListElement<T>::ListElement(T const& datum, ListElement<T>* next)
    : datum(datum)
    , next{next}
{ }

template <class T>
class LinkedList
{
public:
    LinkedList() = default;
    LinkedList(LinkedList const&);
    LinkedList& operator=(LinkedList const&);
    
    bool empty() const { return !head; }
    void push_front(T const&);
    void push_back(T const&);
    void clear();
    
    void left_sibling(T const&) const;
    void right_sibling(T const&) const;
    
    void display() const;
    std::size_t size() const { return m_size; }
private:
    ListElement<T> *head {nullptr}, *tail {nullptr};
    std::size_t m_size{0};
};

template <class T>
LinkedList<T>::LinkedList(LinkedList<T> const& other)
    : head{nullptr}
    , tail{nullptr}
{
    for (auto ptr = &other.head; *ptr; ptr = &(*ptr)->next)
        push_back((*ptr)->datum);
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> const& other)
{
    if (this != &other)
    {
        clear();
        for (auto ptr = &other.head; *ptr; ptr = &(*ptr)->next)
            push_back((*ptr)->datum);
    }
    return *this;
}

template <class T>
void LinkedList<T>::push_front(T const& datum)
{
    ListElement<T>* temp = new ListElement<T> {datum, head};

    if (!head)
        tail = temp;
    head = temp;
    
    ++m_size;
}

template <class T>
void LinkedList<T>::push_back(T const& datum)
{
    ListElement<T>* temp = new ListElement<T> {datum, nullptr};
    
    if (!head)
        head = temp;
    else
        tail->next = temp;
    tail = temp;
    
    ++m_size;
}

template <class T>
ListElement<T>* LinkedList<T>::right_sibling(T const& datum) const
{
    ListElement<T>* ptr = head;
    while (ptr && ptr->datum == datum)
    {
        ptr = ptr->next;
    }
    
    return !ptr ? ptr : ptr->next;
}

template <class T>
ListElement<T>* LinkedList<T>::left_sibling(T const& datum) const
{
    if (is_empty())
        return nullptr;
    else if (size() == 1)
        return head;
    
    ListElement<T>* ptr = head, prev = nullptr;
    while (ptr && ptr->datum == datum)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    
    return prev;
}

template <class T>
void LinkedList<T>::clear()
{
    while (head)
    {
        ListElement<T>* temp {head->next};
        delete head;
        head = temp;
        
        --m_size;
    }
}

template <class T>
void LinkedList<T>::display() const
{
    if (!empty())
    {
        ListElement<T>* const* ptr {&head};
        while (*ptr)
        {
            std::cout << (*ptr)->datum << " ";
            ptr = &(*ptr)->next;
        }
        std::cout << '\n';
    }
}

int main()
{
    LinkedList<int> list1, list2;
    for (int i = 1; i <= 5; ++i) list1.push_front(i);
    list1.display();
    
    list2 = list1;
    list2.display();
}