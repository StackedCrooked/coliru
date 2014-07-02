#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct s
{
    std::string one;
    std::string two;
    int         int_;
    
    s(std::string o, std::string t, int i)
    : one(o),two(t),int_(i)
    {}
    s(){}

};

std::ostream& operator << (std::ostream& os, s const& val)
{
    os << val.one << " " << val.two << " " << val.int_;
    return os;
}

/*Макрос для генерации функций*/
#define COPY_FUNC(FIELD_NAME)                                       \
template<typename T, typename Val = std::string>                    \
std::vector<T> copy_func_ ## FIELD_NAME(std::vector<T> const&  vec, \
                                        Val const& val)             \
{                                                                   \
    std::vector<T> res;                                             \
    for (auto const& a : vec)                                       \
    {                                                               \
        if ( a.FIELD_NAME == val)                                   \
            res.push_back(a);                                       \
    }                                                               \
    return res;                                                     \
}

/*Здесь генерируются функции с именами copy_func_one и copy_func_two соответсвенно
 Поле в имени функции. Вторым параметром идет ее значение или объект-значение*/
COPY_FUNC(one)
COPY_FUNC(two)


int main()
{
    std::vector<s> vec = 
            { 
              s("smoke","lock",10), 
              s("smoke","lose",5),
              s("s","by_value",11),
              s("s3","by_value",12)
            };
    

    std::string bval = "by_value";
    std::vector<s> by_value = std::move(copy_func_two(vec,bval));
    std::vector<s> on_char = std::move(copy_func_one(vec, "smoke"));
    
    std::cout << "by_value :\n";
    for (auto& a : by_value)
        std::cout << a << "\n";
    
    std::cout << "char :\n";
    for (auto& a : on_char)
        std::cout << a << "\n";
    
}
