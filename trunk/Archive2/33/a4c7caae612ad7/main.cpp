#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cxxabi.h>


std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}

template<typename T>
const std::string& GetTypeName()
{
    static std::string fCache = Demangle(typeid(T).name());
    return fCache;
}



template <typename T>
struct TaggedPtr
{

    explicit TaggedPtr(T* p) : data_(reinterpret_cast<uintptr_t>(p))
    {
    }

    uint16_t get_metadata() const { return data_ >> 48; }

    void set_metadata(uint16_t v)
    {
        uintptr_t ip = reinterpret_cast<uintptr_t>(get());
        ip |= static_cast<uintptr_t>(v) << 48;
        data_ = ip;
    }

    T* get() const
    {
        return reinterpret_cast<T*>(data_ & ((1ULL << 48) - 1));
    }

    T* operator->() { return get(); }
    const T* operator->() const { return get(); }

    friend bool operator==(TaggedPtr lhs, TaggedPtr rhs)
    {
        return lhs.get() == rhs.get();
    }

    uintptr_t data_;
};
using Index = std::int16_t;



template<typename T>
struct UniqueIndex
{
    UniqueIndex(T* t) : mTaggedPtr(t)
    {
        mTaggedPtr.set_metadata(AllocateIndex());
    }

    ~UniqueIndex()
    {
        DeallocateIndex(getIndex());
        delete mTaggedPtr.get();
    }

    UniqueIndex(const UniqueIndex&) = delete;
    UniqueIndex& operator=(const UniqueIndex&) = delete;

    T* operator->()
    {
        return mTaggedPtr.get();
    }

    T& operator*()
    {
        return *mTaggedPtr.get();
    }

    Index getIndex() const
    {
        return mTaggedPtr.get_metadata();
    }

private:
    using Indices = std::vector<Index>;

    static Indices& GetIndices()
    {
        static Indices fIndices;
        return fIndices;
    }

    static Index& GetMaxIndex()
    {
        static Index fIndex;
        return fIndex;
    }

    static Index AllocateIndex()
    {
        auto& indices = GetIndices();
        if (indices.empty())
        {
            return GetMaxIndex()++;
        }

        auto result = indices.back();
        indices.pop_back();
        return result;
    }

    static void DeallocateIndex(Index index)
    {
        GetIndices().push_back(index);
    }

    TaggedPtr<T> mTaggedPtr;
};


template<typename T, typename U>
struct Map
{
    using MappedType = std::vector<U>;

    MappedType& operator[](UniqueIndex<T>& t)
    {
        if (mMappedType.size() <= t.getIndex())
        {
            mMappedType.resize(t.getIndex() + 1);
        }
        return mMappedType[t.getIndex()];
    }

    std::vector<MappedType> mMappedType;
};


int main()
{
    UniqueIndex<std::string> hello(new std::string("Hello"));
    UniqueIndex<std::string> goodbye(new std::string("Goodbye"));

    std::cout << hello.getIndex() << std::endl;
    std::cout << goodbye.getIndex() << std::endl;


    Map<std::string, std::string> map;
    map[hello].push_back("World");
    map[hello].push_back(" ...");
    map[goodbye].push_back("Cruel World!");

    std::cout << *goodbye << ' ' << map[hello].back() << ' ';
    std::cout << map[goodbye].front();
}
