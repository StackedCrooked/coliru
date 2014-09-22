#include <vector>
#include <string>
#include <iostream>

class Serializer;

template <typename ClassT> void StaticCall(Serializer& s)
{
    ClassT::Serialize(s, nullptr);
}

template <typename ClassT> void VirtualCall(ClassT& obj, Serializer& s)
{
    obj.Serialize(s);
}

template <typename ClassT> void MemberCall(ClassT& obj, Serializer& s)
{
    obj.ClassT::Serialize(s);
}

class Serializer
{
public:
    enum Mode
    {
        MODE_STRUCTURE
        , MODE_CONTENT
    } mode;

    template <typename TypeT> void DisplayStructure()
    {
        mode = MODE_STRUCTURE;
        StaticCall<TypeT>(*this);
    }

    template <typename TypeT> void DisplayContentVirtual(TypeT& obj)
    {
        mode = MODE_CONTENT;
        VirtualCall(obj, *this);
    }

    template <typename ThisT> void Type(ThisT* obj, const char* obj_name)
    {
        std::cerr << "Type: " << obj_name << std::endl;
    }

    template <typename ParentT, typename ThisT> void TypeWithBase(ThisT* obj, const char* obj_name)
    {
        std::cerr << "Parent ";
        if (mode == MODE_STRUCTURE)
            StaticCall<ParentT>(*this);

        else if (mode == MODE_CONTENT)
            MemberCall(static_cast<ParentT&>(*obj), *this);

        std::cerr << "Type: " << obj_name << std::endl;
    }

    template < typename ThisT, typename MemberT> void Member(ThisT* obj, MemberT ThisT::* member, const char* member_name)
    {
        std::cerr << "Member: " << member_name;
        if (mode == MODE_CONTENT)
            std::cerr << " : " << obj->*member;

        std::cerr << std::endl;
    }
};

// Example usage
class Parent
{
public:
    Parent(int i) : pmem_int(i), pmem_str("Hello") {}
    virtual void Serialize(Serializer& s) 
    {
        Parent::Serialize(s, this);
    }

    static void Serialize(Serializer& s, Parent * ptr)
    {
        s.Type(ptr, "Parent");
        s.Member(ptr, &Parent::pmem_int, "pmem_int");
        s.Member(ptr, &Parent::pmem_str, "pmem_str");
    }

    virtual void Thing() = 0;

    int pmem_int;
    std::string pmem_str;
};

class Child : public Parent
{
public:
    float cmem_float;
    Child() : Parent(1234), cmem_float(334.0f) {}

    virtual void Thing() {}

    virtual void Serialize(Serializer& s) 
    {
        Child::Serialize(s, this);
    }

    static void Serialize(Serializer& s, Child * ptr)
    {
        s.TypeWithBase<Parent>(ptr, "Child");
        s.Member(ptr, &Child::cmem_float, "cmem_float");
        
    }
};


int main(int argc, char* argv[])
{
    Serializer s;
    std::cerr << "Parent structure: " << std::endl;
    s.DisplayStructure<Parent>();

    std::cerr << "\nChild structure: " << std::endl;
    s.DisplayStructure<Child>();

    Child c;
    Parent* p = &c;
    std::cerr << "\nContent: " << std::endl;
    s.DisplayContentVirtual(*p);

    return 0;
}