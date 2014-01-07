namespace Herbs {
    template <typename T>
    struct Stringbase {
        typedef const char16_t* const_iterator;
        const_iterator begin() const { return nullptr; }
    };
    using String = Stringbase<char16_t>;

template<class T> T toInt(const char16_t*);
double toDouble(const char16_t*);

template<class T>
T fromString(const String& str)
    {
    return toInt<T>(str.begin());
    }

template<>
inline
const String& fromString<const String&>(const String& str)
    {return str;}

template<>
inline
double fromString<double>(const String& str)
    {return toDouble(str.begin());}

template<>
inline
const char16_t* fromString<const char16_t*>(const String& str)
    {return str.begin();}

struct someclass {
    String m_items[1];

    template<class T>
    T itemFirstGet() const
        {return fromString<T>(m_items[0]);}
};
}

int main() {
    Herbs::someclass s;
    s.itemFirstGet<const Herbs::String&>(); // calls fromString<const String&>()
    s.itemFirstGet<Herbs::String>();        // calls fromString<String>()
}
