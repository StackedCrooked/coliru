#include <iostream>

template<class T>
    class Node
    {
        public:
            T t;
            Node<T>* next;
            Node<T>() : next(0) {}
            Node<T>(T t) : t(t), next(0) {}
    };
    
template<class T>
class List
{
    private:
        Node<T>* first;
    public:
        List<T>() : first(0) {}
        void add(T t);
};

template<class T>
void List<T>::add(T t)
{
    first = _add(first, new Node<T>(t));
}


template<class T>
Node<T>* _add(Node<T>* first, Node<T>* t)
{
    if (!first)
        first = t;
    else
        first->next = _add(first->next, t);

    return first;
}      

struct Vertex
{
    Vertex(int inf) : information(inf) {}
    int information;
    List<Vertex*>* Edges;
};

    int main()
    {
        List<Vertex*>* head = new List<Vertex*>();
        Vertex *vertex = new Vertex(1);
        Vertex *vertex2 = new Vertex(2);
        vertex->Edges->add(vertex2);// <------------------------- This is the line with the problem

        head->add(vertex);
        head->add(vertex2);
        getchar();
        return 0;
    }
