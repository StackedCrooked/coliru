#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using boost::lexical_cast;

struct device_id_t
    : private boost::multiprecision::uint128_t
{
	typedef boost::multiprecision::uint128_t base_t;
	
	device_id_t()
		: base_t(0) {};
	
	explicit device_id_t(const base_t x)
		: base_t(x) {};
    
    explicit operator base_t&()
    {
        return *this;
    }
    
	const base_t& base() const
	{
		return static_cast<const base_t&>(*this);
	}
	
    /**
     * Inserts a fixed-width, zero-padded, 128-bit hexadecimal string representing
     * the given %device_id into %os.
     * 
     * Example:
     *   device_id_t id(1);
     *   std::stringstream ss;
     *   ss << id;
     *   assert(ss.str() == "00000000000000000000000000000001");
     * 
     * Can be written almost directly into a MySQL BINARY(16) field:
     *   query_bit << "UPDATE `Table` SET `Id` = UNHEX('" << id << "')";
     */
	friend std::ostream& operator<<(std::ostream& os, const device_id_t& device_id)
	{
		return (os << std::hex << std::setw(32) << std::setfill('0') << device_id.base());
	}
	
    /**
     * Extracts a %device_id from hexadecimal values up to 128 bits from %is
     * into %device_id.
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
		return (is >> std::hex >> static_cast<base_t&>(device_id));
	}
};

int main()
{
    device_id_t a;
    assert(a.base() == 0);
    std::cout << "A=" << lexical_cast<std::string>(a) << std::endl;
    assert(lexical_cast<std::string>(a) == "00000000000000000000000000000000");
    
    device_id_t b(1);
    assert(b.base() == 1);
    std::cout << "B=" << lexical_cast<std::string>(b) << std::endl;
    assert(lexical_cast<std::string>(b) == "00000000000000000000000000000001");
    
    device_id_t::base_t val = 1;
    val <<= 127;
    
    device_id_t c(val);
    assert(c.base() == val);
    std::cout << "C=" <<lexical_cast<std::string>(c) << std::endl;
    assert(lexical_cast<std::string>(c) == "80000000000000000000000000000000");
}
