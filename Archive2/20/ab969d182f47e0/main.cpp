#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
class implement_IO_methods
{
    typedef char true_;
    typedef long false_;

    template <typename TestedType> static true_ test( decltype( std::declval<std::ostream&>() << std::declval<T const&>()) ) ;
    template <typename TestedType> static false_ test(...);
    
    template <typename TestedType> static true_ test2( decltype( std::declval<std::istream&>() >> std::declval<T const&>()) ) ;
    template <typename TestedType> static false_ test2(...);

public:
    static const bool value = (sizeof(test<T>(0)) == sizeof(true)) && (sizeof(test2<T>(0)) == sizeof(true)) ;
};

template <typename T>
class AbstractCollection
{
 //   static_assert(  (std::is_arithmetic<T>::value or 
 //                   (std::is_pointer<T>::value && std::is_arithmetic<typename std::remove_pointer<T>::type>::value) or
  //                  implement_IO_methods<T>::value
  ////                "Bad type given, must implement in and out stream.");
};


template <typename T, bool checkNumeric = std::is_arithmetic<T>::value> 
class NumericCollection :
public AbstractCollection<T> {
};

template <typename T> 
class NumericCollection <T, true> : 
public AbstractCollection<T> 
{
public :
	
	NumericCollection& operator- (NumericCollection<T,true>& other) {
		if (this.size!=other.size) throw "Sizes must be equal.";
		NumericCollection res(this.size);
		for (int i=0; i<this.size; ++i) {
			res.items_[i] = this.items_[i] - other.items_[i];	
		}
		return res;
	}

	NumericCollection& operator+ (NumericCollection<T,true>& other) {
		if (this.size!=other.size) throw "Sizes must be equal.";
		NumericCollection res(this.size);
		for (int i=0; i<this.size; ++i) {
			res.items_[i] = this.items_[i] + other.items_[i];	
		}
		return res;
	}
	
	NumericCollection& operator- () {
		NumericCollection res(this.size);
		for (int i=0; i<this.size; ++i) {
			res.items_[i] = -this.items_[i];	
		}
		return res;
	}
	
	NumericCollection& operator+ () {
		NumericCollection res(this.size);
		for (int i=0; i<this.size; ++i) {
			res.items_[i] = +this.items_[i];	
		}
		return res;
	}
	
	
};

template<typename T,size_t size, bool with_pointer>
class TemplateSizedCollection : NumericCollection<T> {
    
template<typename extern_T, bool extern_with_pointer> 
friend class ConstructorSizedCollection;

typedef typename std::conditional<(std::is_pointer<T>::value || (! with_pointer)), T, T*>::type Storage_T;
    size_t size_;
    Storage_T* items_;
public:
    explicit TemplateSizedCollection() : 
    size_(size), 
    items_(new Storage_T[size])
    {}
    
    virtual ~TemplateSizedCollection() {
        delete[] items_;
    }

    TemplateSizedCollection(const TemplateSizedCollection& other) : 
    size_(size), 
    items_(new Storage_T[size]) {
        for (size_t i=0; i<size; ++i) {
            this->items_[i] = other.items_[i];
        }
    }
 
    TemplateSizedCollection (typename std::enable_if<std::is_pointer<Storage_T>::value,TemplateSizedCollection>::type && other):
    size_(size), 
    items_(other.items_)
     {
        other.items_ = new Storage_T[size];
    }


    TemplateSizedCollection& operator= (const TemplateSizedCollection& other){
        if (this!=&other) {
            if (size!=other.size_) throw "Sizes must be equal.";
            for (size_t i=0; i<size ; ++i) {
                delete this->items_[i];
                this->items_[i] = other.items_[i];
            }
        }
        return *this;
    }

    TemplateSizedCollection& operator= (typename std::enable_if<std::is_pointer<Storage_T>::value,TemplateSizedCollection>::type && other){
        if (this!=&other) {
            delete[] this->items_;
            this->items_ = other.items_;
            other.items_ = NULL;
        }
    }

};

template<typename T, bool with_pointer> 
class ConstructorSizedCollection : public NumericCollection<T*> {
    
template<typename extern_T, size_t extern_size, bool extern_with_pointer>
friend class TemplateSizedCollection;

typedef typename std::conditional<(std::is_pointer<T>::value || (! with_pointer)), T, T*>::type Storage_T;
    size_t size_;
    Storage_T* items_;

public:
    explicit ConstructorSizedCollection(size_t size) : 
    size_(size), 
    items_(new Storage_T[size]) 
    {}
    
    ConstructorSizedCollection(const TemplateSizedCollection<> & other) : 
    size_(size),
    items_(new Storage_T[size])
    {
        for (size_t i=0; i<other.size_; ++i) {
            this->items_[i] = other.items_[i];
        }
    }

    
    virtual ~ConstructorSizedCollection() {
        delete[] items_;
    }
};

int main() {
    ConstructorSizedCollection<int*, false> d(10);
    
    return 0;
}