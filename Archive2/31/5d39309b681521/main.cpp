#include <memory>
#include <utility>
#include <unordered_set>
#include <iostream>
template<class T>
class Node
{
    
};
template<class T>
struct myHash {
    size_t operator ()(const T&) const{ return 0; }
};

template<class T>
struct myEqual {
    bool operator () (const T&, const T&) const{ return 0; }
};

using namespace std;
class A
{
    using T = long;
    unordered_set<unique_ptr<Node<T>>, myHash<unique_ptr<Node<T>>>, myEqual<unique_ptr<Node<T>>>> nodes;
    shared_ptr<A> child;

    void moveToChild()
    {
        for(auto it = nodes.begin(); it != nodes.end(); ++it) {
            if (true) {
            child->nodes.emplace(std::move(*it));
            it = nodes.erase(it); // Remove element and move iterator to next element
            --it;
            }
        }
    }
};
int main(){
    
}