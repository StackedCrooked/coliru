#include <vector>
#include <functional>

struct ArbitraryCollection_Entry
{
};

struct ArbitraryIterator {
    ArbitraryCollection_Entry* operator()() {return nullptr;}
};

struct StateType {
    ArbitraryIterator* iter;
};

int main() {
    StateType* state = nullptr;
    
    
    
    
    ArbitraryIterator *iter = (ArbitraryIterator *) state->iter;

    ArbitraryCollection_Entry *result;
    
    result = (ArbitraryCollection_Entry *) (*iter)();
}
