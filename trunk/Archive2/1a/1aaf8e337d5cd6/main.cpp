    #include <iostream>
    #include <tuple>

    using namespace std;

    using byte = char;

    void print(const byte *p) {
       cout << reinterpret_cast<const void*>(p) << endl;
    }

    template<typename T>
    T extract(const byte *&p_current) {
       print(p_current);
       const byte *p = p_current;
       p_current += sizeof(T);
       return T();
       //return *reinterpret_cast<const T*>(p);
    }

    template<typename... T>
    std::tuple<T...> Extract(const byte *&p_current)
    {
       return std::tuple<T...>{extract<T>(p_current)...};
    }

    int main ()
    {
       const byte *p = nullptr;
       Extract<int, double, float, char, long>(p);
       print(p);
    }
