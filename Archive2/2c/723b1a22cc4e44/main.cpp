#include <memory>
#include <cassert>
#include <iostream>

template <class T>
class LinkedNode 
{
 public:
    LinkedNode(const T& newElement, std::unique_ptr<LinkedNode<T>> newNext)
    : element(newElement), next(std::move(newNext))
    {}

    T GetElement() const {return element;}

    std::unique_ptr<LinkedNode<T>> newNext() { return std::move(next); }

 private:
    T element;
    std::unique_ptr<LinkedNode<T>> next;
};

template <class T>
class CompactStack 
{
    public:
        CompactStack() {}
        bool IsEmpty() const { return head == 0; }

        T Peek() const
        {
            assert(!IsEmpty());
            return head->GetElement();
        }

        void Push(const T& x) 
        {
            std::unique_ptr<LinkedNode<T>> newhead(new LinkedNode<T>(x, std::move(head)));
            head.swap(newhead);
        }

        void Pop() 
        {
            assert(!IsEmpty());
            head = std::move(head->newNext());
        }

        void Clear() 
        {
            while (!IsEmpty())
                Pop();
        }

 private:
    std::unique_ptr<LinkedNode<T>> head;
};

int main()
{
    CompactStack<int> cs;
    cs.Push(1);
    cs.Push(2);
    cs.Push(3);

    std::cout << cs.Peek() << '\n';

    cs.Pop();
    std::cout << cs.Peek() << '\n';

    cs.Clear();
    cs.Push(4);
    std::cout << cs.Peek() << '\n';
}
