#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;
template<typename ObjectType>
class SmartVector
{
public:
    typedef std::vector<std::shared_ptr<ObjectType>> StorageType;

    void push_back(ObjectType* object)
    {
        // TODO: insert pointer to element at objects_ end;
        objects_.push_back(std::make_shared<ObjectType>(object));
    }

    void push_back(const ObjectType& object)
    {
        // TODO: allocate a copy of object and insert it at the end of objects_;
		objects_.push_back(object);
    }

    size_t size() const
    {
        return objects_.size();
    }

    typename StorageType::const_iterator begin() const
    {
        return objects_.begin();
    }

    typename StorageType::const_iterator end() const
    {
        return objects_.end();
    }

    typename StorageType::iterator begin()
    {
        return objects_.begin();
    }

    typename StorageType::iterator end()
    {
        return objects_.end();
    }

    ObjectType* operator[](size_t n)
    {
        // TODO: return raw pointer to object at(n)
    }

    operator std::vector<const ObjectType*>() const
    {
        return toRawVector();
    }

    template<typename CastType = ObjectType>
    std::vector<const CastType*> toRawVector() const
    {
        std::vector<const CastType*> output;
        // TODO: Implement method that will transform vector<shared_ptrs> to vector of raw pointers.
        // Note: use an lambda expression as predicate.
        return output;
    }

    void print()
    {
        for (auto a : objects_)
        {
            cout << *a.get() << ", ";
        }
        cout << endl;
    }

    typedef std::shared_ptr<ObjectType> value_type;

private:
    StorageType objects_;
};

struct ElementType
{
    ElementType(int a, int b): a_(a), b_(b) {}
    int a_; int b_;

    // Try to implement operator==()

    friend std::ostream& operator<<(std::ostream& os, ElementType& e)
    {
        return os << e.a_ << " " << e.b_;
    }

private:
    void operator=(const ElementType& copy);
};

class SimpleClass
{
public:
    // TODO: add isEven method implementation
};

struct B
{
    B(std::string s, int bparam, int cparam)
    {
        a = s;
        b = bparam;
        c = cparam;
    }

    std::string a;
    int b;
    int c;

private:
    void operator=(const B& b);
};

int main()
{
	SmartVector<ElementType> smartVector;
    for(size_t i = 0; i < 10; ++i)
    {
        ElementType* e = new ElementType(i, i * 10);

        // TODO: Try to use SmartVector implementation to store pointers
    }

    ElementType e(10, 100);
    // push_back e to SmartVector

    //1. count elements where b < 70
    //2. find an element equal to z
    // Note: use an lambda expression
    ElementType z(3, 300);

    // 1. remove elements where a is an even value
    // Note: implement isEven method in SimpleClass and try to use it as an predicate

    return 0;
}
