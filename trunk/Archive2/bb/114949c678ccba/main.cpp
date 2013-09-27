template<typename T>
class id_type
{
    public:
        id_type(T data)
        {
        }
        
        static int getID()
        {
            static int id = 0;
            return ++id;
        }
        
        int id = getID();
        T data;
};

#include <tuple>
#include <string>

template<typename... types>
class Variant
{
    public:
        Variant(types... args)
        : data(std::make_tuple(id_type<types>(args)...))
        {
        }
        
        
        
    const int active_member;
    std::tuple<id_type<types>...> data;
};

template<typename... types>
Variant<types...> make_variant(types... args)
{
    return Variant<types...>(args...);
}

int main()
{
    Variant<int, float, std::string> variant = make_variant(2, 2.4f, std::string("lol"));
}