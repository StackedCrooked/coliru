#include <list>
#include <memory>

struct IBaseType
{
};

class Type1 : public IBaseType
{
};

class Type2 : public IBaseType
{
};

template <typename... T>
class CreateTypes
{
public:
    CreateTypes()
    {
        [](...){ }((m_types.push_back(std::unique_ptr<T>(new T())))...);
    }

private:
    std::list<std::unique_ptr<IBaseType>> m_types;
};

int main()
{
    CreateTypes<Type1, Type2> createTypes;
    return 0;
}
