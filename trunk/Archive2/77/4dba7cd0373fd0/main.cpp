#include <list>
#include <iostream>
#include <cassert>
using std::list;

typedef char fieldT;

std::ostream& operator<<(std::ostream& os, const list<char>& l)
{
    os << '{';
    for (auto el : l)
        os << el << ',';
    os << '}';
    
    return os;
}

int main()
{
    // Set up deduced from your question
    list<fieldT> activeFields{'a', 'b', 'c'};
    list<fieldT>::iterator currentField = std::next(std::begin(activeFields)); // 'b'
    
    std::cout << activeFields << '\n';
    
    // Your code
    list<fieldT>::iterator steeperField   = currentField;
    list<fieldT>::iterator shallowerField = activeFields.insert(currentField, 'd');
    
    std::cout << activeFields << '\n';
    
    // Some usual output for analysis
    std::cout << *currentField << *steeperField << *shallowerField << '\n';
    std::cout << std::distance(std::begin(activeFields), shallowerField) << '\n';
    
    // Your claims:
    // 1. steeperField should be pointing to the same location as shallowField.
    //    This does not seem to be what's happening
    assert(
        std::distance(std::begin(activeFields),    steeperField)
        != std::distance(std::begin(activeFields), shallowerField)
    );
    
    // 2. shallowerField appears to point to index 2
    assert(
        std::distance(std::begin(activeFields),    shallowerField)
        == 2
    );
}