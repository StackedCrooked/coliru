#include <stdexcept>
#include <deque>

#include <array>
#include <bitset>
#include <utility>
#include <iostream>
#include <iostream>
#include <cmath>
#include <cassert>

namespace sob {

template<class T>
struct vector {
    T x;
    T y;

    vector() {
        x = 0;
        y = 0;
    }

    vector(T a_x, T a_y) {
            x = a_x;
            y = a_y;
    }

    vector<T>& operator+=(const vector<T>& a_v) {
        x += a_v.x;
        y += a_v.y;
            return (*this);
    }

    vector<T>& operator-=(const vector<T>& a_v) {
        x -= a_v.x;
        y -= a_v.y;
            return (*this);
    }

    vector<T>& operator*=(T a_c) {
        x *= a_c;
        y *= a_c;
            return (*this);
    }

    vector<T>& operator/=(T a_c) {
        x /= a_c;
        y /= a_c;
            return (*this);
    }

    vector<T>& operator*=(const vector<T>& a_v) {
        x *= a_v.x;
        y *= a_v.y;
            return (*this);
    }

    vector<T>& operator/=(const vector<T>& a_v) {
        x /= a_v.x;
        y /= a_v.y;
            return (*this);
    }

};

template<class T>
vector<T> operator+(const vector<T>& a_1, const vector<T>& a_2) {
    return { a_1.x + a_2.x, a_1.y + a_2.y };
}

template<class T>
vector<T> operator-(const vector<T>& a_1, const vector<T>& a_2) {
    return { a_1.x - a_2.x, a_1.y - a_2.y };
}

template<class T> 
vector<T> operator*(const vector<T>& a_v, T a_c) {
        return { a_v.x * a_c, a_v.y * a_c };
}

template<class T> 
vector<T> operator/(const vector<T>& a_v, T a_c) {
        return { a_v.x / a_c, a_v.y / a_c };
}

template<class T> 
vector<T> operator*(const vector<T>& a_1, const vector<T>& a_2) {
        return { a_1.x * a_2.x, a_1.y * a_2.y };
}

template<class T> 
vector<T> operator/(const vector<T>& a_1, const vector<T>& a_2) {
        return { a_1.x / a_2.x, a_1.y / a_2.y };
}

template<class T> 
bool operator==(const vector<T>& a_1, const vector<T>& a_2) {
        return ((a_1.x == a_2.x) && (a_1.y == a_2.y));
}

template<class T> 
bool operator!=(const vector<T>& a_1, const vector<T>& a_2) {
        return !(a_1 == a_2);
}

template<class T>
T magnitude(const vector<T>& a_v) {
    return sqrt(pow(a_v.x, 2) + pow(a_v.y, 2));
}

template<class T>
vector<T> normalized(const vector<T> a_v) {
    if (magnitude(a_v) == 0) return {};
    return a_v / magnitude(a_v);
}

// debugging
template<class T>
std::ostream& operator<<(std::ostream& a_o, const vector<T>& a_v) {
    a_o << "(" << a_v.x << ", " << a_v.y << ")";
    return (a_o);
}

}

namespace sob {

template<std::size_t R, std::size_t C>
class bitboard {
private:
    std::array<std::bitset<C>, R> _cells;
public:
	using 	cell 		= 			sob::vector<std::size_t>;
	using 	proxy		= typename 	std::bitset<C>;
	using 	reference 	= typename 	std::bitset<C>::reference;

	proxy& 			operator[](std::size_t);
	const proxy&	operator[](std::size_t) const;
	bitboard<R, C>& operator&=(const bitboard<R, C>&);
	bitboard<R, C>& operator|=(const bitboard<R, C>&);

	reference 		at(cell);
	bool 			at(cell) const;
	std::size_t 	columns();
	std::size_t 	rows();
};

template<std::size_t R, std::size_t C>
typename bitboard<R, C>::proxy& bitboard<R, C>::operator[](std::size_t row) {
	return _cells[row];
}

template<std::size_t R, std::size_t C>
const typename bitboard<R, C>::proxy& bitboard<R, C>::operator[](std::size_t row) const {
	return _cells[row];
}

template<std::size_t R, std::size_t C>
bitboard<R, C>& bitboard<R, C>::operator&=(const bitboard<R, C>& rhs) {
	(*this) = (*this) & rhs;
	return (*this);
}

template<std::size_t R, std::size_t C>
bitboard<R, C>& bitboard<R, C>::operator|=(const bitboard<R, C>& rhs) {
	(*this) = (*this) | rhs;
	return (*this);
}

template<std::size_t R, std::size_t C>
typename bitboard<R, C>::reference bitboard<R, C>::at(bitboard<R, C>::cell c) {
	return _cells[c.x][c.y];
}

template<std::size_t R, std::size_t C>
bool bitboard<R, C>::at(bitboard<R, C>::cell c) const {
	return _cells[c.x][c.y];
}

template<std::size_t R, std::size_t C>
std::size_t	bitboard<R, C>::columns() {
	return C;
}

template<std::size_t R, std::size_t C>
std::size_t bitboard<R, C>::rows() {
	return R;
}

template<std::size_t R, std::size_t C> 
const bitboard<R, C> operator&(const bitboard<R, C>& lhs, const bitboard<R, C>& rhs) {
	bitboard<R, C> ret;
	for (std::size_t r = 0; r < R; ++r) {
		ret[r] = lhs[r] & rhs[r];
	}
	return ret;
}

template<std::size_t R, std::size_t C> 
const bitboard<R, C> operator|(const bitboard<R, C>& lhs, const bitboard<R, C>& rhs) {
	bitboard<R, C> ret;
	for (std::size_t r = 0; r < R; ++r) {
		ret[r] = lhs[r] | rhs[r];
	}
	return ret;
}

template<std::size_t R, std::size_t C>
std::ostream& operator<<(std::ostream& os, const bitboard<R, C>& bb) {
	for (std::size_t r = 0; r < R; ++r) {
		for (std::size_t c = 0; c < C; ++c)
			std::cout << bb.at({r, c});
		if (r != R - 1) std::cout << '\n';
	}
	return os;
}

}

namespace sob {

template<std::size_t R, std::size_t C>
class snake {
private:
    unsigned										_unadded;
	std::deque<typename sob::bitboard<R, C>::cell>	_order;
	sob::bitboard<R, C>								_segments;
	const sob::bitboard<R, C>						_shape;
public:
	enum class direction { up, left, down, right };
	class no_space_error		: public std::logic_error {};
	class zero_length_error 	: public std::logic_error {};
	class twisted_error			: public std::logic_error {};

	explicit	snake(typename sob::bitboard<R, C>::cell, const sob::bitboard<R, C>& = sob::bitboard<R, C>());
	void 		move(direction);
	void 		warp(typename sob::bitboard<R, C>::cell);
	void		extend(unsigned = 1);
	void		reduce(unsigned = 1);

	typename sob::bitboard<R, C>::cell 	segment(std::size_t) noexcept;
	typename sob::bitboard<R, C>::cell 	head() const noexcept;
	typename sob::bitboard<R, C>::cell 	tail() const noexcept;
	unsigned 							length() const noexcept;
	const sob::bitboard<R, C>& 			bitboard() const noexcept;
};

template<std::size_t R, std::size_t C>
snake<R, C>::snake(typename sob::bitboard<R, C>::cell cell, const sob::bitboard<R, C>& bb) :
	_unadded(0),
	_shape(bb)
{
    assert	(	(cell.x >= 0 && cell.x < C - 1)
			&&	(cell.y >= 0 && cell.y < R - 1));
	assert(_shape.at(cell) == false);
	
	_segments.at(cell) = true;
	_order.push_front(cell);
}

template<std::size_t R, std::size_t C>
void snake<R, C>::move(snake<R, C>::direction dir) {
	typename sob::bitboard<R, C>::cell head_pos = _order.front();
	switch (dir) {
        case direction::up:     head_pos += {0, -1}; break;
        case direction::left:   head_pos += {-1, 0}; break;
        case direction::down:   head_pos += {0, +1}; break;
        case direction::right:  head_pos += {+1, 0}; break;
        default: break;
    }

    if (_unadded > 0) {
    	_unadded--;
    } else {
    	_segments.at(_order.back()) = false;
    	_order.pop_back();
    }

    _segments.at(head_pos) = true;
    _order.push_front(head_pos);
}

template<std::size_t R, std::size_t C>
void snake<R, C>::warp(typename sob::bitboard<R, C>::cell cell) {
	typename sob::bitboard<R, C>::cell old_pos = _order.front();
	_order.pop_front();
	_order.push_front(cell);
	_segments.at(old_pos) = false;
	_segments.at(cell) = true;
}

template<std::size_t R, std::size_t C>
void snake<R, C>::extend(unsigned count) {
	_unadded += count;
}

template<std::size_t R, std::size_t C>
void snake<R, C>::reduce(unsigned count) {
	if (length() - count <= 0)
		throw zero_length_error();
	for (int i = count; i > 0; --i) {
		_segments.at(_order.back()) = true;
		_order.pop_back();
	}
}

template<std::size_t R, std::size_t C>
typename sob::bitboard<R, C>::cell snake<R, C>::segment(std::size_t i) noexcept {
	return _order[i];
}

template<std::size_t R, std::size_t C>
typename sob::bitboard<R, C>::cell snake<R, C>::head() const noexcept {
	return _order.front();
}

template<std::size_t R, std::size_t C>
typename sob::bitboard<R, C>::cell snake<R, C>::tail() const noexcept {
	return _order.back();
}

template<std::size_t R, std::size_t C>
unsigned snake<R, C>::length() const noexcept {
	return _order.size();
}

template<std::size_t R, std::size_t C>
const typename sob::bitboard<R, C>& snake<R, C>::bitboard() const noexcept {
	return _segments;
}

}

int main() {
    sob::snake<5, 5> snake({0, 0});
}