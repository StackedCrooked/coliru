#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>

struct device_id_t
    : private boost::multiprecision::uint128_t
{
	typedef boost::multiprecision::uint128_t base_t;
	
	device_id_t()
		: base_t(0) {};
	
	explicit device_id_t(const base_t x)
		: base_t(x) {};
    
	const base_t& base() const
	{
		return static_cast<const base_t&>(*this);
	}
    
    friend bool operator==(const device_id_t& lhs, const device_id_t& rhs)
    {
        return lhs.base() == rhs.base();
    }
    
    friend bool operator!=(const device_id_t& lhs, const device_id_t& rhs)
    {
        return lhs.base() != rhs.base();
    }
    
    friend bool operator<(const device_id_t& lhs, const device_id_t& rhs)
    {
        return lhs.base() < rhs.base();
    }
    
    friend bool operator>(const device_id_t& lhs, const device_id_t& rhs)
    {
        return lhs.base() > rhs.base();
    }
    
    friend bool operator<=(const device_id_t& lhs, const device_id_t& rhs)
    {
        return lhs.base() <= rhs.base();
    }
    
    friend bool operator>=(const device_id_t& lhs, const device_id_t& rhs)
    {
        return lhs.base() >= rhs.base();
    }
	
    /**
     * Inserts a fixed-width, zero-padded, 128-bit, lower-case hexadecimal
     * string representing the given %device_id into %os.
	 * 
	 * Does not persistently alter any format flags on %os.
     * 
     * Example:
     *   device_id_t id(12);
     *   std::stringstream ss;
     *   ss << id;
     *   assert(ss.str() == "0000000000000000000000000000000c");
     * 
     * Can be written almost directly into a MySQL BINARY(16) field:
     *   query_bit << "UPDATE `Table` SET `Id` = UNHEX('" << id << "')";
     */
    friend std::ostream& operator<<(std::ostream& os, const device_id_t& device_id)
	{
		const std::ios_base::fmtflags new_flags
			= std::ios_base::hex
			| std::ios_base::right;
		
		const std::ios_base::fmtflags flags_mask
			= std::ios_base::hex
			| std::ios_base::right
			| std::ios_base::showbase
			| std::ios_base::uppercase;
		
		const std::ios_base::fmtflags original_flags = os.setf(new_flags, flags_mask);
		
		os << std::setw(32) << std::setfill('0') << device_id.base();
		os.setf(original_flags, flags_mask);
		
		return os;
	}
	
    /**
     * Extracts a %device_id from hexadecimal values up to 128 bits from %is
     * into %device_id.
	 * 
	 * Does not persistently alter any format flags on %is.
     * 
     * Example:
     *   std::stringstream ss("80000000000000000000000000000000");
     *   device_id_t id;
     *   ss >> id;
     *   
     *   device_id_t::base_t cmp = 1; cmp <<= 127;
     *   assert(id == cmp);
     * 
     * Can interpret a MySQL BINARY(16) field almost directly:
     *   query_bit << "SELECT HEX(`Id`) AS `Id` FROM `Table`";
     *   // ..
     *   device_id_t id = boost::lexical_cast<device_id_t>(result["Id"]);
     */
	friend std::istream& operator>>(std::istream& is, device_id_t& device_id)
	{
		const std::ios_base::fmtflags new_flags
			= std::ios_base::hex;
		
		const std::ios_base::fmtflags original_flags = is.setf(new_flags);
		
		is >> static_cast<base_t&>(device_id);
		is.setf(original_flags);
		
		return is;
	}
};

template <typename T1, typename T2>
T1 lexical_cast(const T2& x)
{
    return T1();//boost::lexical_cast<T1>(x);
    // commented out to demonstrate that this function is being called,
    // and NOT the one below. -.-
}

// work dammit
template <>
device_id_t lexical_cast<device_id_t>(const std::string& str)
{
    device_id_t x;
    
    std::stringstream ss(str);
    if (!(ss >> x))
        throw boost::bad_lexical_cast(typeid(std::string), typeid(device_id_t));
    
    return x;
}

template <>
std::string lexical_cast<std::string>(const device_id_t& x)
{
    std::stringstream ss;
    if (!(ss << x))
        throw boost::bad_lexical_cast(typeid(device_id_t), typeid(std::string));
    
    return ss.str();
}

int main()
{
    device_id_t a;
    assert(a.base() == 0);
    std::cout << "A=" << lexical_cast<std::string>(a) << std::endl;
    assert(lexical_cast<std::string>(a) == "00000000000000000000000000000000");
    assert(lexical_cast<device_id_t>("00000000000000000000000000000000") == a);
    
    device_id_t b(1);
    assert(b.base() == 1);
    std::cout << "B=" << lexical_cast<std::string>(b) << std::endl;
    assert(lexical_cast<std::string>(b) == "00000000000000000000000000000001");
    assert(lexical_cast<device_id_t>("00000000000000000000000000000001") == b);
    
    device_id_t::base_t val = 1;
    val <<= 127;
    
    device_id_t c(val);
    assert(c.base() == val);
    std::cout << "C=" <<lexical_cast<std::string>(c) << std::endl;
    assert(lexical_cast<std::string>(c) == "80000000000000000000000000000000");
    assert(lexical_cast<device_id_t>("80000000000000000000000000000000") == c);
    
    device_id_t d(12);
    assert(d.base() == 12);
    std::cout << "D=" << lexical_cast<std::string>(d) << std::endl;
    assert(lexical_cast<std::string>(d) == "0000000000000000000000000000000c");
    assert(lexical_cast<device_id_t>("0000000000000000000000000000000c") == d);
}
