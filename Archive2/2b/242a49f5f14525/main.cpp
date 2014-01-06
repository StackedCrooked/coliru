#include <iostream>
#include <type_traits>
 
template <typename T>
class implement_IO_methods
{
    typedef char true_;
    typedef long false_;

    template <typename TestedType> static true_ test( decltype( std::declval<std::ostream&>() << std::declval<TestedType const&>()) ) ;
    template <typename TestedType> static false_ test(...);
    
    template <typename TestedType> static true_ test2( decltype( std::declval<std::istream&>() >> std::declval<TestedType const&>()) ) ;
    template <typename TestedType> static false_ test2(...);

public:
    static const bool value = (sizeof(test<T>(0)) == sizeof(true)) && (sizeof(test2<T>(0)) == sizeof(true)) ;
};

template <typename T,bool with_pointer>
class AbstractCollection
{
    static_assert    (  
						(
							std::is_arithmetic<T>::value 
							|| (
								std::is_pointer<T>::value && 
								std::is_arithmetic<typename std::remove_pointer<T>::type>::value
							) ||
                    		implement_IO_methods<T>::value
                    	),
                		"Bad type given, must implement in and out stream."
					);
    typedef typename std::conditional<(std::is_pointer<T>::value || (! with_pointer)), T, T*>::type Storage_T;
protected:
    size_t size_;
    Storage_T* items_;
    AbstractCollection(size_t size) : size_(size), items_(new Storage_T[size]) {}
};

template <typename ,bool > class NumericCollection {};

template <typename T>
class NumericCollection<T,true> :
public AbstractCollection<T,true> {

public:
    NumericCollection(size_t size) : AbstractCollection<T,false>(size) {}

    template<typename e_T,bool e_with_pointer>
    typename std::enable_if<
        (
            (std::is_arithmetic<T>::value) && 
            (std::is_arithmetic<e_T>::value) &&
            (std::is_convertible<e_T,T>::value)
        ),
        NumericCollection<T, false>
    >::type  operator- (NumericCollection<e_T,e_with_pointer>& other) {
        if (this->size_!=other.size_) throw "Sizes must be equal.";
    	NumericCollection<T,false> res(this->size_);
		for (int i=0; i<this->size_; ++i) {
            if (e_with_pointer) {
		        res.items_[i] = this->items_[i] - *(other.items_[i]);	
            } else {
                res.items_[i] = this->items_[i] - other.items_[i];
            }
		}
		return res;
	}

	template<typename e_T,bool e_with_pointer>
    typename std::enable_if<
        (
            (std::is_arithmetic<T>::value) && 
            (std::is_arithmetic<e_T>::value) &&
            (std::is_convertible<e_T,T>::value)
        ),
        NumericCollection<T, false>
    >::type  operator+ (NumericCollection<e_T,e_with_pointer>& other) {
    	if (this->size_!=other.size_) throw "Sizes must be equal.";
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = this->items_[i] + other.items_[i];	
		}
		return res;
	}
		
	typename std::enable_if<
        (std::is_arithmetic<T>::value),
        NumericCollection<T, false>
    >::type  operator- () {
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = -this->items_[i];	
		}
		return res;
	}
	
	typename std::enable_if<
        (std::is_arithmetic<T>::value),
        NumericCollection<T, false>
    >::type  operator+ () {
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = +this->items_[i];	
		}
		return res;
	}
	
    
    typename std::enable_if<
        std::is_arithmetic<T>::value,
        NumericCollection<T,false>
    >::type  operator* (int scalar) {
        NumericCollection<T,false> res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = scalar * this->items_[i];	
		}
		return res;
	}
    
};

template <typename T>
class NumericCollection<T,false> :
public AbstractCollection<T,false> {

public:
    NumericCollection(size_t size) : AbstractCollection<T,false>(size) {}

    template<typename e_T,bool e_with_pointer>
    typename std::enable_if<
        (
            (std::is_arithmetic<T>::value) && 
            (std::is_arithmetic<e_T>::value) &&
            (std::is_convertible<e_T,T>::value)
        ),
        NumericCollection<T, false>
    >::type  operator- (NumericCollection<e_T,e_with_pointer>& other) {
    	if (this->size_!=other.size_) throw "Sizes must be equal.";
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = this->items_[i] - other.items_[i];	
		}
		return res;
	}

	template<typename e_T,bool e_with_pointer>
    typename std::enable_if<
        (
            (std::is_arithmetic<T>::value) && 
            (std::is_arithmetic<e_T>::value) &&
            (std::is_convertible<e_T,T>::value)
        ),
        NumericCollection<T, false>
    >::type  operator+ (NumericCollection<e_T,e_with_pointer>& other) {
    	if (this->size_!=other.size_) throw "Sizes must be equal.";
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = this->items_[i] + other.items_[i];	
		}
		return res;
	}
		
	typename std::enable_if<
        (std::is_arithmetic<T>::value),
        NumericCollection<T, false>
    >::type  operator- () {
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = -this->items_[i];	
		}
		return res;
	}
	
	typename std::enable_if<
        (std::is_arithmetic<T>::value),
        NumericCollection<T, false>
    >::type  operator+ () {
		NumericCollection res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = +this->items_[i];	
		}
		return res;
	}
	
    
    typename std::enable_if<
        std::is_arithmetic<T>::value,
        NumericCollection<T,false>
    >::type  operator* (int scalar) {
        NumericCollection<T,false> res(this->size_);
		for (int i=0; i<this->size_; ++i) {
			res.items_[i] = scalar * this->items_[i];	
		}
		return res;
	}

};
 
int main() 
{
    NumericCollection<int,false> a(10);
    NumericCollection<int,true> b(10);
    a-b;
    std::cout << "coucou" << std::endl;
    
}