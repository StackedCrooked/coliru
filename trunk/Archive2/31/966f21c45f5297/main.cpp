#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <vector>


namespace Relational {


using Index = std::uint16_t;


template<typename T>
using Table = std::vector<T*>;


template<typename T>
static Table<T>& GetTable()
{
    // A unique objct will be generated per instantiation of this function template.
    static Table<T> fTable;
    return fTable;
}


template<typename T>
static Index Register(T*);


template<typename T>
static Index Unregister(T*);


template<typename T>
T* FindByIndex(Index inIndex)
{
    return GetTable<T>()[inIndex];
}


template<typename T>
T& GetByIndex(Index inIndex)
{
    return *GetTable<T>()[inIndex];
}


template<typename T>
class Object
{
public:
    Index GetIndex() const
    {
        return mIndex;
    }

protected:
    Object() : mIndex(Register(static_cast<T*>(this)))
    {
        static_assert(std::is_base_of<Object<T>, T>::value, "");
    }

    ~Object()
    {
        Unregister(this);
    }

private:
    Index mIndex;
};


template<typename T>
static Index Register(T* ptr)
{
    auto& objects = GetTable<T>();
    auto it = std::find(objects.begin(), objects.end(), nullptr);
    if (it == objects.end())
    {
        auto result = objects.size();
        objects.push_back(ptr);
        return result;
    }
    else
    {
        T*& unused_ptr = *it;
        unused_ptr = ptr;
        return it - objects.begin();
    }
}


template<typename T>
static void Unregister(Object<T>* object)
{
    GetTable<T>()[object->GetIndex()] = nullptr;
}


template<typename T, typename U>
struct Map
{
    U& get(const Object<T>& t) const
    {
        auto& items = GetGlobal();
        if (items.size() <= t.GetIndex())
        {
            items.resize(t.GetIndex() + 1);
        }
        return items[t.GetIndex()];
    }

    std::vector<U>& getValues() const
    {
        return GetGlobal();
    }

private:
    // Returns the global mapping
    static std::vector<U>& GetGlobal()
    {
        // The global mapping will be created on first call to this function.
        // (This is thread-safe.)
        static auto fMapping = []{
            std::vector<U> result;
            result.reserve(GetTable<T>().capacity());
            return result;
        }();
        return fMapping;
    }
};


} // namespace Relational

