#include <map>
#include <utility>

class Value {
public:
    Value(int value) { _value = value;}
    Value(const Value&) = delete;
    Value& operator=(const Value&) = delete;
    void* operator new(size_t) = delete;    // not on free store
private:
    int _value;
};

class Container
{

public:
    Container() {}
    Value* addToMap(int key) {
        auto ret = _map.emplace(std::piecewise_construct
                              , std::forward_as_tuple(key)
                              , std::forward_as_tuple(key));
        return &(ret.first->second);
    }

private:
    std::map<int, Value> _map;
};
 
int main()
{
    Container c;
    Value* v = c.addToMap(1);  
    (void)v;
}
