#include <iostream>
#include <stdexcept>
#include <string>

template <typename Ch, typename Traits = std::char_traits<Ch>>
class basic_string_view {
public:

    typedef Traits         traits_type;
	typedef Ch             value_type;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;

	typedef       value_type* pointer;
	typedef const value_type* const_pointer;
	typedef       value_type& reference;
	typedef const value_type& const_reference;

	static constexpr size_type npos = size_type(-1);

	constexpr basic_string_view() noexcept
		: m_data("") // initialize with an implementation defined non-null string
		, m_size(0)
	{
	}

	constexpr basic_string_view(const basic_string_view& view) = default;
	basic_string_view& operator=(const basic_string_view& view) = default;

	template <typename Allocator>
	basic_string_view(const std::basic_string<Ch, Traits, Allocator>& s) noexcept
		: m_data(s.data())
		, m_size(s.size())
	{
	}

	constexpr basic_string_view(const Ch* s)
		: m_data(s)
		, m_size(Traits::length(s))
	{
	}
    
    constexpr size_type size() const noexcept { return m_size; }
    
	constexpr const_reference at(size_type pos) const
	{
		return (pos < size()) ? data()[pos] :
			throw std::range_error("index out of bounds");
	}

	constexpr const_pointer data() const noexcept { return m_data; }

private:
	const_pointer m_data;
	size_type     m_size;
};

typedef basic_string_view<char> string_view;

int main()
{
    string_view view("0123");
    view.at(0);
}