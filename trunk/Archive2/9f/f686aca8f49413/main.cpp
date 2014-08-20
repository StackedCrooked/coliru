#include <string>
#include <utility>

struct MySQLRow
{
    int GetInt(std::size_t index) const
    {
        switch (index)
        {
        case 3:
            return 42;
            
        default:
            return {};
        }
    }
    
    std::string GetString(std::size_t index) const
    {
        switch (index)
        {
        case 1:
            return "A. N. Onim";
            
        case 2:
            return "Male";
            
        default:
            return {};
        }
    }
};

#define DEFINE_GET_FOR_TYPE(Type, TypeName) \
void Get(Type& arg, const MySQLRow& row, std::size_t index) \
{ \
    arg = row.Get##TypeName(index); \
}

DEFINE_GET_FOR_TYPE(int, Int)

DEFINE_GET_FOR_TYPE(std::string, String)


struct Iterate
{
    Iterate(...) {}
};

template <typename... Types, std::size_t... indices>
void GetResultImpl(const MySQLRow& row, Types&... args, std::index_sequence<indices...>)
{
    Iterate{(Get(atgs, row, indices + 1), 0)...};
}

template <typename... Types>
void GetResult(const MySQLRow& row, Types&... args)
{
    GetResultImpl(row, args..., std::make_index_sequence<sizeof...(Types)>())
}


int main()
{
    MySQLRow row;
    std::string name;
    std::string sex;
    int age;
    
    GetResult(row, name, sex, age);
    
    std::cout
        << "Name: " << name << std::endl
        << "Sex: " << sex << std::endl
        << "Age:" << age << std::endl;
}
