#include <functional>
#include <iostream>
#include <thread>
#include <chrono>

struct List
{
    struct Node
    {
        int data{0};
        Node* next{0};
    };

    Node* head{0};

    void insert(int n)
    {
        Node* node = new Node{n};
        node->next = head;
        head = node;
    }
};

int Count(List& list)
{
    int count = 0;
    for (List::Node* head = list.head; head != nullptr; head = head->next)
        count++;
    return count;
}

int main()
{
    List i;
    std::thread t1(&List::insert, &i, 5);
    std::thread t2(&List::insert, &i, 3);
    t1.join();
    t2.join();
    std::cout << Count(i);
}