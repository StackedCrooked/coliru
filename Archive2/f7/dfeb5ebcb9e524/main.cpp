#include <iostream>
#include <string>
#include <type_traits>

    template<typename EnumClass>
    class FlagSet
    {
        typedef typename std::underlying_type<EnumClass>::type IntegralType;

        static_assert(std::is_unsigned<IntegralType>::value,
                      "FlagSet: enum class type must be an "
                      "unsigned integral");

    public:
        FlagSet() : m_flags(0) { }
        FlagSet(IntegralType val) : m_flags(val) { }

        IntegralType value()
        {
            return m_flags;
        }

        FlagSet & operator = (FlagSet const &arg)
        {
            m_flags = arg.m_flags;
            return *this;
        }

        FlagSet operator & (EnumClass const &arg)
        {
            return FlagSet(m_flags & static_cast<IntegralType>(arg));
        }

        FlagSet operator | (EnumClass const &arg)
        {
            return FlagSet(m_flags | static_cast<IntegralType>(arg));
        }

        FlagSet operator ^ (EnumClass const &arg)
        {
            return FlagSet(m_flags ^ static_cast<IntegralType>(arg));
        }

        FlagSet operator ~ ()
        {
            return FlagSet(~m_flags);
        }

        FlagSet & operator &= (EnumClass const &arg)
        {
            m_flags &= static_cast<IntegralType>(arg);
            return *this;
        }

        FlagSet & operator |= (EnumClass const &arg)
        {
            m_flags |= static_cast<IntegralType>(arg);
            return *this;
        }

        FlagSet & operator ^= (EnumClass const &arg)
        {
            m_flags ^= static_cast<IntegralType>(arg);
            return *this;
        }

        explicit operator bool() const
        {
            return (m_flags > 0);
        }

    private:
        IntegralType m_flags;
    };

    enum class Color : uint8_t
    {
        Red         = 1 << 0,
        Green       = 1 << 1,
        Blue        = 1 << 2,
        Yellow      = 1 << 3,
        Smurple     = 1 << 4
    };

    
int main()
{
        FlagSet<Color> color_flags;
        color_flags = color_flags | Color::Red | Color::Green | Color::Yellow;
        color_flags = color_flags | Color::Smurple;
        std::cout << "has blue? " << bool(color_flags & Color::Blue) << std::endl;
        std::cout << "has green? " << bool(color_flags & Color::Green) << std::endl;
        std::cout << "has smurple? " << bool(color_flags & Color::Smurple) << std::endl;
        std::cout << "has yellow? " << bool(color_flags & Color::Yellow) << std::endl;
        std::cout << std::endl;

        FlagSet<Color> color_flags_2;
        (color_flags_2 |= Color::Red) | Color::Yellow | Color::Smurple; // won't work! deceptive!
        color_flags_2 |= Color::Blue;
        std::cout << "has red? " << bool(color_flags_2 & Color::Red) << std::endl;
        std::cout << "has yellow? " << bool(color_flags_2 & Color::Yellow) << std::endl;
        std::cout << "has smurple? " << bool(color_flags_2 & Color::Smurple) << std::endl;
        std::cout << "has blue? " << bool(color_flags_2 & Color::Blue) << std::endl;
        
        return 0;
}
