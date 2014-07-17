#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>

inline void cgiDebug (const bool v)
{
    if (!v) throw;
}

template< class T, unsigned BLOCK = 128 >
class block_iterator :
    	public std::iterator< std::bidirectional_iterator_tag, T >
{
	static_assert (BLOCK != 0, "BLOCK must be greater than 0");
	static_assert ((BLOCK & (BLOCK - 1)) == 0, "BLOCK must be a power of 2");
	static_assert (BLOCK % sizeof (T) == 0, "BLOCK must fit multiples of T");
	
public:
							block_iterator (T* other = 0);
							block_iterator (const block_iterator& other);

	block_iterator&			operator= (const block_iterator& other);
						
    T&						operator*();
    T*						base();

	bool					operator== (const block_iterator& other) const;
	bool					operator!= (const block_iterator& other) const;
	bool					operator< (const block_iterator& other) const;
	bool					operator> (const block_iterator& other) const;
	bool					operator<= (const block_iterator& other) const;
	bool					operator>= (const block_iterator& other) const;

	block_iterator&			operator++();
	block_iterator&			operator--();
	block_iterator			operator++ (int);
	block_iterator			operator-- (int);

	class range
	{
	public:
								range (T* begin,
										T* end);
								range (block_iterator& begin,
										block_iterator& end);
								range (range& other);
								range (range& other, bool split);

		const block_iterator&	begin() const;
		const block_iterator&	end() const;
		std::size_t				size() const;
		std::size_t				approx_size() const;
		bool					is_valid() const;
		bool					can_split() const;
		
	private:

		block_iterator		begin_;
		block_iterator		end_;
	};

//private:

	std::uintptr_t&			global_address();
	unsigned				local_address() const;
	unsigned				block_alignment() const;
	unsigned				stride_alignment() const;
	void					next_block();

	T*						iterator_;
	unsigned				stride_;
};


template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >::block_iterator (T* other)
		: iterator_ (other), stride_ (1)
{}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >::block_iterator (const block_iterator& other)
		: iterator_ (other.iterator_), stride_ (other.stride_)
{}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >& block_iterator< T, BLOCK >::operator=
		(const block_iterator& other)
{
	iterator_ = other.iterator_;
	stride_ = other.stride_;
	return *this;
}

template< class T, unsigned BLOCK >
inline T& block_iterator< T, BLOCK >::operator*()
{
	return *iterator_;
}

template< class T, unsigned BLOCK >
inline T* block_iterator< T, BLOCK >::base()
{
	return iterator_;
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::operator==
		(const block_iterator& other) const
{
	return iterator_ == other.iterator_;
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::operator!=
		(const block_iterator& other) const
{
	return iterator_ != other.iterator_;
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::operator<
		(const block_iterator& other) const
{
	return iterator_ < other.iterator_;
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::operator>
		(const block_iterator& other) const
{
	return iterator_ > other.iterator_;
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::operator<=
		(const block_iterator& other) const
{
	return iterator_ <= other.iterator_;
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::operator>=
		(const block_iterator& other) const
{
	return iterator_ >= other.iterator_;
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >& block_iterator< T, BLOCK >::operator++()
{
	++iterator_;
	global_address() += block_alignment() ? 0 : BLOCK * (stride_ - 1);
	return *this;
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >& block_iterator< T, BLOCK >::operator--()
{
	global_address() -= block_alignment() ? 0 : BLOCK * (stride_ - 1);
	--iterator_;
	return *this;
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK > block_iterator< T, BLOCK >::operator++ (int)
{
	block_iterator tmp (*this);
	this->operator++();
	return tmp;
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK > block_iterator< T, BLOCK >::operator-- (int)
{
	block_iterator tmp (*this);
	this->operator--();
	return tmp;
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >::range::range (T* begin, T* end)
		: begin_ (begin), end_ (end)
{
	cgiDebug (is_valid());
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >::range::range (block_iterator& begin,
		block_iterator& end) : begin_ (begin), end_ (end)
{
	cgiDebug (is_valid());
}

template< class T, unsigned BLOCK >
inline block_iterator< T, BLOCK >::range::range (range& other)
		: begin_ (other.begin_), end_ (other.end_)
{
	cgiDebug (is_valid());
}

template< class T, unsigned BLOCK >
block_iterator< T, BLOCK >::range::range (range& other, bool split)
		: begin_ (other.begin_), end_ (other.end_)
{
	cgiDebug (split);
	cgiDebug (is_valid());
	cgiDebug (can_split());
	begin_.next_block();
	end_.next_block();
	begin_.stride_ = end_.stride_ =
			other.begin_.stride_ = other.end_.stride_ *= 2;
	if (begin_.stride_alignment() != end_.stride_alignment()) {
		std::swap (end_, other.end_);
	}
	cgiDebug (is_valid());
	cgiDebug (other.is_valid());
}

template< class T, unsigned BLOCK >
inline const block_iterator< T, BLOCK >&
		block_iterator< T, BLOCK >::range::begin () const
{
	return begin_;
}

template< class T, unsigned BLOCK >
inline const block_iterator< T, BLOCK >&
		block_iterator< T, BLOCK >::range::end () const
{
	return end_;
}

template< class T, unsigned BLOCK >
inline std::size_t block_iterator< T, BLOCK >::range::size () const
{
	return (end_.iterator_ - begin_.iterator_) / begin_.stride_;
}

template< class T, unsigned BLOCK >
inline std::size_t block_iterator< T, BLOCK >::range::approx_size () const
{
	std::size_t size = end_.iterator_ - begin_.iterator_;
	std::cerr << size << ' ';
	std::cerr << begin_.stride_ << ' ';
	size /= begin_.stride_;
	std::cerr << size << ' ';
	std::cerr << size << std::endl;
	return (end_.iterator_ - begin_.iterator_) / (begin_.stride_ * 2 - 1);
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::range::is_valid () const
{
	return begin_.iterator_ <= end_.iterator_ &&
			begin_.stride_ == end_.stride_ &&
			begin_.stride_alignment() == end_.stride_alignment();
}

template< class T, unsigned BLOCK >
inline bool block_iterator< T, BLOCK >::range::can_split() const
{
	cgiDebug (is_valid());
	return begin_.stride_ < std::numeric_limits<unsigned>::max() / 2;
}

template< class T, unsigned BLOCK >
inline std::uintptr_t& block_iterator< T, BLOCK >::global_address()
{
	return reinterpret_cast< std::uintptr_t& > (iterator_);
}

template< class T, unsigned BLOCK >
inline unsigned block_iterator< T, BLOCK >::local_address() const
{
	return static_cast<unsigned>
			(reinterpret_cast< std::uintptr_t > (iterator_));
}

template< class T, unsigned BLOCK >
inline unsigned block_iterator< T, BLOCK >::block_alignment() const
{
	return local_address() % BLOCK;
}

template< class T, unsigned BLOCK >
inline unsigned block_iterator< T, BLOCK >::stride_alignment() const
{
	return (local_address() / BLOCK) % stride_;
}

template< class T, unsigned BLOCK >
inline void block_iterator< T, BLOCK >::next_block()
{
	global_address() += stride_ * BLOCK - block_alignment();
}

int main()
{
    static const int size = 100;
    int data[size];
    typedef block_iterator< int, 128 >::range range;
    
    std::cerr << "done\n";
}
