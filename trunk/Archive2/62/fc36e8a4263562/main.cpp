#include <numeric>
#include <cstddef>
#include <limits>
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

template <typename Num>
class counting_iterator{

    typedef Num value_type;
	typedef const Num& reference;
	typedef const Num* pointer;
	typedef counting_iterator<Num> iter;
	typedef std::ptrdiff_t difference_type;

	static_assert(std::is_integral<Num>::value, "Counting_iterator accepts only integral types.");

	public:
		/*
		* Constructors
		*/
		//Default -- sets internal state to Num::max, if applicable
		counting_iterator() noexcept(std::is_nothrow_default_constructible<Num>::value):
		  current_(std::numeric_limits<Num>::max()){}
		//Value
		counting_iterator(Num val) noexcept(std::is_nothrow_constructible<Num>::value):
		  current_(val){}
		//Copy constructor
		counting_iterator(const iter& rhs) noexcept(std::is_nothrow_copy_constructible<Num>::value):
		  current_(rhs.current_){}
		//Move constructor
		counting_iterator(iter&& rhs) noexcept(std::is_nothrow_move_constructible<Num>::value):
		  current_(std::move(rhs.current_)){}
		
		//Copy assignment operator
		iter& operator=(const iter& rhs){
			current_ = rhs.current_;
			return *this;
		}
		//Move assignment operator
		iter& operator=(iter&& rhs){
			current_(std::move(rhs.current_));
			return *this;
		}

		//"Math" operators
		//On other iterators
		iter operator-(const iter& rhs) const {
			difference_type temp = current_ - rhs.current_;
			return temp;
		}
		//On value
		iter& operator+=(const difference_type& offset){
			current_ += offset;
		}
		iter operator+(const difference_type& offset) const {
			iter temp(*this);
			temp += offset;
			return temp;
		}
		iter& operator-=(const difference_type& offset){
			current_ -= offset;
		}
		iter operator-(const difference_type& offset) const {
			iter temp(*this);
			temp -= offset;
			return temp;
		}
		

		/*
		* Increments/Decrements
		*/
		iter& operator++(){ //Predecrement
			++current_;
			return *this;
		}
		iter operator++(int){ //Postdecrement
			iter temp(*this);
			++current_;
			return temp;
		}
		iter& operator--(){ //Predecrement
			--current_;
			return *this;
		}
		iter operator--(int){ //Postdecrement
			iter temp(*this);
			--current_;
			return temp;
		}




		/*
		* Comparison operators.
		*/
		bool operator<(const iter& rhs) const {
			return current_ < rhs.current_;
		}
		bool operator>(const iter& rhs) const {
			return rhs < *this;
		}
		bool operator<=(const iter& rhs) const {
			return !(rhs < *this);
		}
		bool operator>=(const iter& rhs) const {
			return !(*this < rhs);
		}
		bool operator==(const iter& rhs) const {
			return current_ == rhs.current_;
		}
		bool operator!=(const iter& rhs) const {
			return !(*this == rhs);
		}

		/*
		* Other operators. ([], *, ->)
		*/
		value_type operator[](difference_type offset) const {
			return current_ + offset;
		}
		reference operator*() const {
			return current_;
		}
		pointer operator->() const {
			return &current_;
		}


	private:
		Num current_;


};

template <typename Num>
inline counting_iterator<Num> operator+(const typename counting_iterator<Num>::difference_type& offset, const counting_iterator<Num> iter){
	return iter + offset;
}

int main(){
    std::transform(counting_iterator<int>(1),
                   counting_iterator<int>(101),
                   std::ostream_iterator<std::string>(std::cout, "\n"),
                   [](int i){
                        bool mod3 = i % 3 == 0;
                        bool mod5 = i % 5 == 0;
                        std::string response;
                        if (mod3){
                            response += "Fizz";
                        }
                        if (mod5){
                            response += "Buzz";
                        }
                        if (!mod3 && !mod5){
                            response = std::to_string(i);
                        }
                        return response;
                   });
}