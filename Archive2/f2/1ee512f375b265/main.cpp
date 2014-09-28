#include <iostream>
#include <sstream>

template <typename T>
void MagicLog(std::ostream& o, T t)
{
    o << t << std::endl;
}

template<typename T, typename... Args>
void MagicLog(std::ostream& o, T t, Args... args) // recursive variadic function
{
    MagicLog(o, t);
    MagicLog(o, args...);
}

template<typename T, typename... Args>
void LogAll(int logType, T t, Args... args)
{
    std::ostringstream oss;
    MagicLog(oss, t);
    MagicLog(oss, args...);
    std::cout << oss.str();
}

int main()
{
  LogAll(5, "HELLO", "WORLD", 42);
}