#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template <typename T>
class ClassName
{
    static inline bool CheckInherit()
    {
        return true;
    }
    
    template<typename S>
    inline bool IsInherit()
    {
        return ClassName::CheckInherit();
    }
};

template<typename T, typename S>
bool IsInherit()
{
    return 
}

class IELunaObject
{
};

template<typename T>
class UserData
{
    UserData()
    {
        ClassName<T> *pTmp;
        if ( pTmp->IsInherit<IELunaObject>() )
        {
        }
    }
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
