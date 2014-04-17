#include <type_traits>
#include <initializer_list>
#include <string>

template <typename enumT>
class EnumeratedFlags
{
public:

    typedef enumT enum_type;
    typedef typename std::underlying_type<enumT>::type store_type;

// constructors

    EnumeratedFlags()
        : m_bits(0)
    {
    }

    EnumeratedFlags(enum_type flag)
        : m_bits(static_cast<store_type>(flag))
    {
    }

    explicit EnumeratedFlags(store_type value)
        : m_bits(value)
    {
    }

    EnumeratedFlags(const std::initializer_list<enum_type> & initializers)
        : m_bits(0)
    {
        for (auto flag : initializers)
            m_bits |= static_cast<store_type>(flag);
    }

// operators

    operator std::string () const
    {
        return to_string();
    }

    bool operator [] (enum_type flag) const
    {
        return test(flag);
    }

    store_type operator * () const
    {
        return m_bits;
    }

    operator bool () const
    {
        return m_bits != store_type(0);
    }

// explicit accessors

    store_type bits() const
    {
        return m_bits;
    }

    std::string to_string() const
    {
        std::string str(size(), '0');

        for (size_t x = 0; x < size(); ++x)
            str[size() - x - 1] = (m_bits & (1 << x) ? '1' : '0');

        return str;
    }

    EnumeratedFlags & set(enum_type flag)
    {
        BitSet(m_bits, static_cast<store_type>(flag));
        return *this;
    }

    EnumeratedFlags & set_if(enum_type flag, bool set_or_clear)
    {
        BitSetIf(m_bits, static_cast<store_type>(flag), set_or_clear);
        return *this;
    }

    EnumeratedFlags & clear()
    {
        m_bits = store_type(0);
        return *this;
    }

    EnumeratedFlags & flip()
    {
        m_bits = ~m_bits;
        return *this;
    }

    EnumeratedFlags & flip(enum_type flag)
    {
        m_bits ^= static_cast<store_type>(flag);
        return *this;
    }

    size_t count() const
    {
        // http://www-graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan

        store_type bits = m_bits;
        size_t total = 0;
        for (; bits != 0; ++total)
        {
            bits &= bits - 1; // clear the least significant bit set
        }
        return total;
    }

    size_t size() const
    {
        // one character per possible bit
        return sizeof(enum_type) * 8;
    }

    bool test(enum_type flag) const
    {
        return BitTest(m_bits, static_cast<store_type>(flag));
    }

    bool any() const
    {
        return m_bits != 0;
    }

    bool none() const
    {
        return m_bits == 0;
    }

private:

    store_type m_bits;
};

template <class charT, class traits, typename enumT>
std::basic_ostream<charT, traits> & operator << (std::basic_ostream<charT, traits> & os, const EnumeratedFlags<enumT> & flags)
{
    return os << flags.to_string();
}

template <typename enumT>
EnumeratedFlags<enumT> operator & (const EnumeratedFlags<enumT>& lhs, const EnumeratedFlags<enumT>& rhs)
{
    return EnumeratedFlags<enumT>(lhs.bits() & rhs.bits());
}

template <typename enumT>
EnumeratedFlags<enumT> operator | (const EnumeratedFlags<enumT>& lhs, const EnumeratedFlags<enumT>& rhs)
{
    return EnumeratedFlags<enumT>(lhs.bits() | rhs.bits());
}

template <typename enumT>
EnumeratedFlags<enumT> operator ^ (const EnumeratedFlags<enumT>& lhs, const EnumeratedFlags<enumT>& rhs)
{
    return EnumeratedFlags<enumT>(lhs.bits() ^ rhs.bits());
}

//template <typename enumT>
//bool BitTest(const EnumeratedFlags<enumT>& lhs, const EnumeratedFlags<enumT>& rhs)
//{
//    return (lhs & rhs);
//}

template <typename enumT>
bool BitTest(const EnumeratedFlags<enumT>& lhs, 
             const EnumeratedFlags<typename EnumeratedFlags<enumT>::enum_type>& rhs)
{
    return (lhs & rhs);
}

enum class Flags { None = 0x00, CanChangeDataSources = 0x01, RequiresExclusiveAccess = 0x02 };
EnumeratedFlags<Flags> lhs(Flags::CanChangeDataSources);

int main()
{
    if (BitTest(lhs, Flags::CanChangeDataSources)) {  }
}
