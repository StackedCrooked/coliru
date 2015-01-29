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


struct Index
{
    using value_type = std::uint16_t;

    Index() : mValue(-1)
    {
        static_assert(std::is_nothrow_move_constructible<Index>::value, "");
        static_assert(std::is_nothrow_move_assignable<Index>::value, "");
    }

    explicit Index(value_type inValue) :
        mValue(inValue)
    {
    }

    operator value_type() const { return mValue; }

private:
    value_type mValue;
};


template<typename T>
struct IndexHelper
{
    IndexHelper() = delete;

    using Indices = std::vector<Index>;

    static Indices& GetIndices()
    {
        static Indices fIndices;
        fIndices.reserve(100);
        return fIndices;
    }

    using Objects = std::vector<T>;


    static Objects& GetObjects()
    {
        static Objects fObjects;
        fObjects.reserve(100);
        return fObjects;
    }


    static Index New()
    {
        Index result;

        auto& indices = GetIndices();
        auto it = std::find(indices.begin(), indices.end(), Index());
        if (it == indices.end())
        {
            indices.push_back(Index(indices.size()));
            result = indices.back();
        }
        else
        {
            result = *it = Index(it - indices.begin());
        }

        std::cout << GetTypeName<T>() << ": Creating index " << result << std::endl;
        return result;
    }

    static void Delete(Index inIndex)
    {
        std::cout << GetTypeName<T>() << ": Deleting index " << inIndex << std::endl;
        GetIndices()[inIndex] = Index();
    }

    static T& GetByIndex(Index i)
    {
        return GetObjects()[i];
    }
};

template<typename T>
struct Indexed;



template<typename T>
struct WithIndex
{
    using IndexedType = T;

    WithIndex() : mIndex(IndexHelper<T>::New())
    {
        static_assert(std::is_nothrow_move_constructible<WithIndex>::value, "");
        static_assert(std::is_nothrow_move_assignable<WithIndex>::value, "");
        static_assert(std::is_base_of<WithIndex<T>, T>::value || std::is_base_of<T, WithIndex<T>>::value, "");
    }

    WithIndex(const WithIndex&) = delete;
    WithIndex& operator=(const WithIndex&) = delete;

    WithIndex(WithIndex&& rhs) noexcept :
        mIndex(rhs.mIndex)
    {
        rhs.mIndex = Index();
    }

    WithIndex& operator=(WithIndex&& rhs) noexcept
    {
        if (this == &rhs) return *this;
        IndexHelper<T>::Delete(mIndex);
        mIndex = rhs.mIndex;
        rhs.mIndex = Index();
        return *this;
    }

    ~WithIndex()
    {
        IndexHelper<T>::Delete(mIndex);
    }

    operator Indexed<T>() const;

    Index getIndex() const
    {
        return mIndex;
    }

private:
    Index mIndex;
};


template<typename T>
struct Indexed
{
    explicit Indexed(Index inIndex) : mIndex(inIndex)
    {
    }

    Indexed(WithIndex<T>* t) : mIndex(t->getIndex())
    {
    }

    explicit Indexed(WithIndex<T>& t) : mIndex(t.getIndex())
    {
    }

    operator const T*() const { return get(); }
    operator T*()  { return get(); }

    operator const T&() const { return get(); }
    operator T&() { return get(); }

    const T* get() const { return &IndexHelper<T>::GetByIndex(mIndex); }
    T* get() { return &IndexHelper<T>::GetByIndex(mIndex); }

    const T& operator*() const { return *get(); }
    T& operator*() { return *get(); }

    const T* operator->() const { return get(); }
    T* operator->() { return get(); }

    Index getIndex() const
    {
        return mIndex;
    }

private:
    Index mIndex;
};



template<typename T>
WithIndex<T>::operator Indexed<T>() const
{
    return Indexed<T>(*this);
}



template<typename T>
using Vector = std::vector<Indexed<T>>;


template<typename T, typename U>
struct Map
{
    using Values = Vector<U>;

    Values& operator[](const WithIndex<T>& t)
    {
        auto i = t.getIndex();
        if (mValues.size() <= i)
        {
            mValues.resize(i + 1);
        }
        return mValues[i];
    }

    Values& operator[](const WithIndex<T>* t)
    {
        return this->operator[](*t);
    }

    void reserve(std::size_t n)
    {
        mValues.reserve(n);
    }

    std::size_t size() const { return mValues.size(); }

private:
    std::vector<Values> mValues;
};








struct Packet : WithIndex<Packet>
{
};

struct Filter : WithIndex<Filter>
{
};

struct Processor : WithIndex<Processor>
{

};


struct PacketGroup : WithIndex<PacketGroup>
{
};




struct Receiver
{
    Packet mPacket1;
    Packet mPacket2;

    Filter mFilter1;
    Filter mFilter2;
    Filter mFilter3;
    Filter mFilter4;

    Processor mProcessor1;
    Processor mProcessor2;

    Receiver()
    {
        mPackets.push_back(&mPacket1);
        mPackets.push_back(&mPacket2);

        mFilters.push_back(&mFilter1);
        mFilters.push_back(&mFilter2);
        mFilters.push_back(&mFilter3);
        mFilters.push_back(&mFilter4);

        mProcessors.push_back(&mProcessor1);
        mProcessors.push_back(&mProcessor2);

        mFiltersPerPacket[mPacket1].push_back(&mFilter1);
        mFiltersPerPacket[mPacket1].push_back(&mFilter2);
        mFiltersPerPacket[mPacket2].push_back(&mFilter3);
        mFiltersPerPacket[mPacket2].push_back(&mFilter4);

        mProcessorsPerFilter[mFilter1].push_back(&mProcessor1);
        mProcessorsPerFilter[mFilter2].push_back(&mProcessor1);
        mProcessorsPerFilter[mFilter3].push_back(&mProcessor2);
        mProcessorsPerFilter[mFilter4].push_back(&mProcessor2);
    }

    void receive_thread()
    {
        Map<Processor, Packet> processorsPerPacket;

        for (Packet* packet : mPackets)
        {
            for (Filter* filter : mFiltersPerPacket[packet])
            {
                for (Processor* processor : mProcessorsPerFilter[filter])
                {
                    processorsPerPacket[processor].push_back(packet);
                }
            }
        }

        for (Packet* packet : mPackets)
        {
            std::cout << "Packet=" << packet->getIndex() << " Processors = [";
            for (auto& processor : mFiltersPerPacket[packet])
            {
                std::cout << ' ' << processor->getIndex();
            }
            std::cout << " ]" << std::endl;
        }
    }

    Vector<Packet> mPackets;
    Vector<Filter> mFilters;
    Vector<Processor> mProcessors;
    Map<Packet, Filter> mFiltersPerPacket;
    Map<Filter, Processor> mProcessorsPerFilter;
};


int main()
{
    {
        Receiver receiver;
        receiver.receive_thread();
    }

    auto a = new Filter;
    auto b = new Filter;
    delete a;
    delete new Filter;
    delete b;
}


