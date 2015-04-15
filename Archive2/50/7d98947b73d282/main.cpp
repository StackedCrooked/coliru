#include <vector>
#include <iostream>
#include <cassert>

struct TypeWithMember
{
    unsigned _a[5];
};

struct IContainer
{
    virtual ~IContainer(void) {}
    virtual unsigned Count(void) const = 0;
    virtual void const* GetValue(void) const = 0;
    virtual void Add(void*) = 0;
    virtual void Next(void) = 0;
    virtual bool IsValid(void) = 0;
    virtual void SetContainer(void* data) = 0;
};

template<typename TYPE, typename ALLOCATOR>
class VectorContainer : public IContainer
{
    public:
        typedef std::vector<TYPE, ALLOCATOR> Container;
        VectorContainer(void) {}
        virtual unsigned Count(void) const { assert(_container); return _container->size(); }
        virtual void const* GetValue(void) const { assert(_container); assert(_it != _container->end()); return &(*_it); }
        virtual void Add(void* data) { assert(_container); _container->push_back(*(TYPE*)data); }
        virtual void Next(void) { assert(_container); assert(_it != _container->end()); ++_it; }
        virtual bool IsValid(void) { assert(_container); return _it != _container->end(); }
        virtual void SetContainer(void* data) { assert(data); _container = (Container*)data; _it = _container->begin(); }
    private:
        typename Container::iterator _it;
        Container* _container;
};

template<typename TYPE, size_t SIZE>
class ArrayContainer : public IContainer
{
    public:
        ArrayContainer(void) : _pos(0) {}
        virtual unsigned Count(void) const { return SIZE; }
        virtual void const* GetValue(void) const { assert(_container); assert(_pos < SIZE); return _container + _pos; }
        virtual void Add(void* data) { assert(_container); assert(_pos < SIZE); _container[_pos++] = *(TYPE*)data; }
        virtual void Next(void) { assert(_container); assert(_pos < SIZE); ++_pos; }
        virtual bool IsValid(void) { assert(_container); return _pos < SIZE; }
        virtual void SetContainer(void* data) { _container = (TYPE*)data; }
    private:
        unsigned _pos;
        TYPE* _container;
};
 
struct Name
{
    explicit Name(char const* name) : _hash(0), _text(name) {}
    unsigned _hash;
    char const* _text;
};
 
struct Field
{
    template<typename TYPE, typename ALLOCATOR, typename OBJECT_TYPE>
    Field(char const* szName, std::vector<TYPE, ALLOCATOR>(OBJECT_TYPE::*)) :
    _name(szName)
    {
        _pContainer = new VectorContainer<TYPE, ALLOCATOR>();
    }
    template<typename FIELD_TYPE, typename OBJECT_TYPE, size_t SIZE>
    Field(char const* szName, FIELD_TYPE(OBJECT_TYPE::*)[SIZE]) : _name(szName)
    {
        _pContainer = new ArrayContainer<FIELD_TYPE, SIZE>();
    }
    Name _name;
    IContainer* _pContainer;
};


struct Dummy
{
    std::vector<int> _member;
};
 
int main()
{
    Field fields[] = { Field("_member", &Dummy::_member) };
    std::cout << "fields[0]._name._text: " << fields[0]._name._text << std::endl;
    std::vector<int> intVector;
    fields[0]._pContainer->SetContainer(&intVector);
    
    Field fields_2[] = { Field("_a", &TypeWithMember::_a) };
    std::cout << "fields_2[0]._name._text: " << fields_2[0]._name._text << std::endl;
    unsigned array[5] = { 0, 1, 2, 3, 4 };
    fields_2[0]._pContainer->SetContainer(array);
    IContainer* pContainer = fields_2[0]._pContainer;
    while(pContainer->IsValid())
    {
        std::cout << *reinterpret_cast<unsigned const*>(pContainer->GetValue()) << std::endl;
        pContainer->Next();
    }
}