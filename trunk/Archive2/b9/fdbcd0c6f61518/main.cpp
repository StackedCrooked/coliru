#include <iostream>

template<typename Type, typename = std::ostream&>
class implement_ostream : public std::false_type {};

template<typename Type>
struct implement_ostream<Type, decltype(std::declval<std::ostream&>() << std::declval<Type>())> : public std::true_type {};

template<typename Type, typename = std::istream&>
class implement_istream : public std::false_type {};

template<typename Type>
struct implement_istream<Type, decltype(std::declval<std::istream&>() >> std::declval<Type>())> : public std::true_type {};

template <typename T> class AbstractCollection{

    static_assert    (  
						(
							std::is_arithmetic<T>::value 
							|| (
								std::is_pointer<T>::value && 
								std::is_arithmetic<typename std::remove_pointer<T>::type>::value
							) || (
                                implement_ostream<T>::value &&
                                implement_istream<T>::value
                            )
                    	),
                		"Bad type given, must implement in and out stream."
					);
    template<typename e_T,size_t e_size,bool e_w_prt>
    friend class TemplateSizedCollection;
    
protected:
    virtual size_t getSize() const = 0;
    virtual const T getItem(const size_t i) const = 0; 
    
public:
	template <typename Ty>
    friend std::ostream& operator << (std::ostream& out, const AbstractCollection<Ty> & toPrint) ; 
    template <typename Ty>
    friend std::istream& operator >> (std::istream& in, AbstractCollection<Ty> & toFill) ;
   // virtual ~AbstractCollection()=0;
};

template <typename T>
class NumericCollection : public AbstractCollection<T> { // Si ce test au dessus est False, pas de spécialisation
template<typename,size_t,bool,class>
friend class TemplateSizedCollection;
protected:
    NumericCollection()=default;
    virtual size_t getSize() const = 0;
    virtual const T getItem(const size_t i) const override = 0;
public:
    
    virtual NumericCollection& operator- (const NumericCollection & other) const =0;
    
    virtual NumericCollection& operator+ (const NumericCollection& other) const =0;
		
    virtual NumericCollection& operator- () const =0;
	
	virtual NumericCollection& operator+ () const =0;
    
    virtual NumericCollection& operator* (const int scalar) const =0;
    
    template <typename e_T>
    friend NumericCollection<e_T> & operator* (const int scalar,const NumericCollection<e_T> &other);
    
    virtual ~NumericCollection() = default;
};

template<typename T,bool with_pointer> class ConstructorSizedCollection;

template<typename T,size_t size,bool with_pointer,class enable = void> class TemplateSizedCollection;

template<typename T, size_t size,bool with_pointer> 
class TemplateSizedCollection<
    T,
    size,
    with_pointer,
    typename std::enable_if<
        (!std::is_arithmetic<T>::value) &&
        (std::is_pointer<T>::value ||
        (!with_pointer))
    >::type
> :
public AbstractCollection<T>
{

size_t size_;
T* items_; 

template<typename e_T, bool e_w_ptr>
friend class ConstructorSizedCollection;
template<typename e_T, size_t e_size, bool e_w_ptr, class en>
friend class TemplateSizedCollection;

size_t getSize() const override {
    return this->size_;    
}

const T getItem(const size_t i) const override {
    return this->items_[i];	
}

public:
    explicit TemplateSizedCollection() :
    size_(size), items_(new T[size])
    {}
    
    // Constructeur de copie
    template <typename e_T>
    TemplateSizedCollection(const AbstractCollection<e_T>  & other) :
    size_(other.getSize()), items_(new T[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItem(i);
        }
    }
	
    /* / Constructeur de conversion
    template<typename e_T, size_t e_size,bool e_w_ptr>
    TemplateSizedCollection(const ConstructorSizedCollection<e_T, e_w_ptr>  & other) :
    size_(other.getSize()), items_(new T[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItems(i);
        }
    }*/
    
    
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(TemplateSizedCollection<e_T, e_size, e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && (!e_w_ptr || std::is_pointer<e_T>::value)  ),
            "Type Error : Cannot be converted."
        );
        other.items_ = new T[this->size_];
    }
    
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(ConstructorSizedCollection<e_T ,e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && ((!e_w_ptr) || std::is_pointer<e_T>::value)),
            "Type Error : Cannot be converted."
        );
        other.items_ = new e_T[this->size_];
    }
	
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const TemplateSizedCollection<e_T, e_size, e_w_ptr> & other){
        static_assert(
                std::is_convertible<e_T, T>::value,
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItem(i);
        }
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const ConstructorSizedCollection<e_T, e_w_ptr> & other){
        static_assert(
                std::is_convertible<e_T, T>::value,
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItems(i);
        }
        return *this;
    }

    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (TemplateSizedCollection<e_T, e_size, e_w_ptr> && other){
        static_assert(
                (std::is_convertible<e_T, T>::value && ((!e_w_ptr) || std::is_pointer<e_T>::value)),
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T[this->size_];
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (ConstructorSizedCollection<e_T, e_w_ptr> && other){
        static_assert(
                (std::is_convertible<e_T, T>::value && ((!e_w_ptr) || std::is_pointer<e_T>::value)),
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T[this->size_];
        return *this;
    }
    
	virtual ~TemplateSizedCollection() {
		delete[] items_;
	} 
    
    void test() {
        std::cout << "1" << std::endl;
    }
}; 

template<typename T,size_t size,bool with_pointer> 
class TemplateSizedCollection<
    T,
    size,
    with_pointer,
    typename std::enable_if<
        (!std::is_pointer<T>::value) &&
        with_pointer &&
        (!std::is_arithmetic<T>::value)
    >::type
> :
public AbstractCollection<T>
{

size_t size_;
T** items_; 

template<typename e_T, bool e_w_ptr>
friend class ConstructorSizedCollection;
template<typename e_T, size_t e_size, bool e_w_ptr,class en>
friend class TemplateSizedCollection;

size_t getSize() const{
    return this->size_;    
}

T getItem(size_t i) const {
    return *(this->items_[i]);	
}

public:
    explicit TemplateSizedCollection() :
    size_(size), items_(new T*[size])
    {
        for (size_t i=0; i<size; ++i)
            this->items_[i] = new T;
    }
    
    // Constructeur de copie
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(TemplateSizedCollection<e_T, e_size, e_w_ptr> const & other) :
    size_(other.getSize()), items_(new T*[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = new T;
            *(this->items_[i]) = other.getItem(i);
        }
    }
	
    // Constructeur de conversion
    template<typename e_T, size_t e_size,bool e_w_ptr>
    TemplateSizedCollection(ConstructorSizedCollection<e_T, e_w_ptr> const & other) :
    size_(other.getSize()), items_(new T*[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            *(this->items_[i]) = other.getItems(i);
        }
    }
    
    
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(TemplateSizedCollection<e_T, e_size, e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        other.items_ = new e_T*[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            other.items_[i] = new e_T;
        }
    }
    
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(ConstructorSizedCollection<e_T,e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        other.items_ = new e_T*[this->size_];
        for (size_t i = 0; i<this->size_; ++i) {
            other.items_[i] = new e_T;
        }
    }
	
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const TemplateSizedCollection<e_T, e_size, e_w_ptr> & other){
        static_assert(
                std::is_convertible<e_T, T>::value,
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T*[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = new T;
            *(this->items_[i]) = other.getItem(i);
        }
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const ConstructorSizedCollection<e_T, e_w_ptr> & other){
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T*[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            *(this->items_[i]) = other.getItems(i);
        }
        return *this;
    }

    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (TemplateSizedCollection<e_T, e_size, e_w_ptr> && other){
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T*[this->size_];
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (ConstructorSizedCollection<e_T, e_w_ptr> && other){
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T*[this->size_];
        return *this;
    }
    
	virtual ~TemplateSizedCollection() {
		delete [] *items_;
	} 
    
    void test() {
        std::cout << "2" << std::endl;
    }
};

template<typename T, size_t size,bool with_pointer> 
class TemplateSizedCollection<
    T,
    size,
    with_pointer,
    typename std::enable_if<
        std::is_arithmetic<T>::value &&
        (std::is_pointer<T>::value ||
        (!with_pointer))
    >::type
> :
public NumericCollection<T>
{

size_t size_;
T* items_; 

template<typename e_T, bool e_w_ptr>
friend class ConstructorSizedCollection;
template<typename e_T, size_t e_size, bool e_w_ptr, class en>
friend class TemplateSizedCollection;

size_t getSize() const override {
    return this->size_;    
}

const T getItem(const size_t i) const override {
    return this->items_[i];    
}

public:
    explicit TemplateSizedCollection() :
    size_(size), items_(new T[size])
    {}
    
    // Constructeur de copie
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(const TemplateSizedCollection<e_T, e_size, e_w_ptr>  & other) :
    size_(other.getSize()), items_(new T[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItem(i);
        }
    }
    
    // Constructeur de conversion
    template<typename e_T, size_t e_size,bool e_w_ptr>
    TemplateSizedCollection(const ConstructorSizedCollection<e_T, e_w_ptr>  & other) :
    size_(other.getSize()), items_(new T[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItems(i);
        }
    }
    
    
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(TemplateSizedCollection<e_T, e_size, e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && (!e_w_ptr || std::is_pointer<e_T>::value)  ),
            "Type Error : Cannot be converted."
        );
        other.items_ = new T[this->size_];
    }
    
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(ConstructorSizedCollection<e_T ,e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && ((!e_w_ptr) || std::is_pointer<e_T>::value)),
            "Type Error : Cannot be converted."
        );
        other.items_ = new e_T[this->size_];
    }
	
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const TemplateSizedCollection<e_T, e_size, e_w_ptr> & other){
        static_assert(
                std::is_convertible<e_T, T>::value,
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItem(i);
        }
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const ConstructorSizedCollection<e_T, e_w_ptr> & other){
        static_assert(
                std::is_convertible<e_T, T>::value,
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = other.getItems(i);
        }
        return *this;
    }

    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (TemplateSizedCollection<e_T, e_size, e_w_ptr> && other){
        static_assert(
                (std::is_convertible<e_T, T>::value && ((!e_w_ptr) || std::is_pointer<e_T>::value)),
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T[this->size_];
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (ConstructorSizedCollection<e_T, e_w_ptr> && other){
        static_assert(
                (std::is_convertible<e_T, T>::value && ((!e_w_ptr) || std::is_pointer<e_T>::value)),
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T[this->size_];
        return *this;
    }
    
	virtual ~TemplateSizedCollection() {
		delete[] items_;
	}
    
    NumericCollection<T>& operator- (const NumericCollection<T> & other) const override {
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
		for (int i=0; i<this->size_; ++i) {
            res->items_[i] = this->items_[i] - other.getItem(i);
		}
		return *res;
	}
    
    NumericCollection<T>& operator+ (const NumericCollection<T> & other) const override {
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
    	for (int i=0; i<this->size_; ++i) {
            res->items_[i] = this->items_[i] - other.getItem(i);
		}
		return *res;
	}
    
    NumericCollection<T>& operator-() const override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
    	for (int i=0; i<this->size_; ++i) {
            res->items_[i] = - this->items_[i];
		}
		return *res;
	}
    
    NumericCollection<T>& operator+() const override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
        for (int i=0; i<this->size_; ++i) {
            res->items_[i] = + this->items_[i];
		}
		return *res;
	}
    
    NumericCollection<T>& operator*(const int scalar) const override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
        for (int i=0; i<this->size_; ++i) {
            res->items_[i] = scalar * this->items_[i];
    	}
		return *res;
	}
 
    template<typename e_T>
    friend NumericCollection<e_T>& operator* (const int scalar,const NumericCollection<e_T> &other) override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
        for (int i=0; i<other.getSize(); ++i) {
            res->items_[i] = scalar * other.getItem(i);
        }
		return *res;
    }
 
    void test() {
        std::cout << "3" << std::endl;
    }
};

template<typename T,size_t size,bool with_pointer> 
class TemplateSizedCollection<
    T,
    size,
    with_pointer,
    typename std::enable_if<
        (!std::is_pointer<T>::value) &&
        with_pointer &&
        std::is_arithmetic<T>::value
    >::type
> : 
public NumericCollection<T>
{

size_t size_;
T** items_; 

template<typename e_T, bool e_w_ptr>
friend class ConstructorSizedCollection;
template<typename e_T, size_t e_size, bool e_w_ptr,class en>
friend class TemplateSizedCollection;

size_t getSize() const override {
    return this->size_;    
}

const T getItem(const size_t i) const override {
    return *(this->items_[i]);    
}

public:
    explicit TemplateSizedCollection() :
    size_(size), items_(new T*[size])
    {
        for (size_t i=0; i<size; ++i)
            this->items_[i] = new T;
    }
    
    // Constructeur de copie
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(TemplateSizedCollection<e_T, e_size, e_w_ptr> const & other) :
    size_(other.getSize()), items_(new T*[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = new T;
            *(this->items_[i]) = other.getItem(i);
        }
    }
    
    // Constructeur de conversion
    template<typename e_T, size_t e_size,bool e_w_ptr>
    TemplateSizedCollection(ConstructorSizedCollection<e_T, e_w_ptr> const & other) :
    size_(other.getSize()), items_(new T*[this->size_])
    {
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        for (size_t i=0; i<this->size_; ++i) {
            *(this->items_[i]) = other.getItems(i);
        }
    }
    
    
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(TemplateSizedCollection<e_T, e_size, e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        other.items_ = new e_T*[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            other.items_[i] = new e_T;
        }
    }
    
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection(ConstructorSizedCollection<e_T,e_w_ptr> && other ) :
    size_(other.size_), items_(other.items_)
    {	
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        other.items_ = new e_T*[this->size_];
        for (size_t i = 0; i<this->size_; ++i) {
            other.items_[i] = new e_T;
        }
    }
	
    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const TemplateSizedCollection<e_T, e_size, e_w_ptr> & other){
        static_assert(
                std::is_convertible<e_T, T>::value,
                "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T*[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            this->items_[i] = new T;
            *(this->items_[i]) = other.getItem(i);
        }
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (const ConstructorSizedCollection<e_T, e_w_ptr> & other){
        static_assert(
            std::is_convertible<e_T, T>::value,
            "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Error : Size must be equal.";
        delete[] this->items_;
        this->items_ = new T*[this->size_];
        for (size_t i=0; i<this->size_; ++i) {
            *(this->items_[i]) = other.getItems(i);
        }
        return *this;
    }

    template <typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (TemplateSizedCollection<e_T, e_size, e_w_ptr> && other){
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T*[this->size_];
        return *this;
    }
    
    template<typename e_T, size_t e_size, bool e_w_ptr>
    TemplateSizedCollection& operator= (ConstructorSizedCollection<e_T, e_w_ptr> && other){
        static_assert(
            (std::is_convertible<e_T, T>::value && !std::is_pointer<e_T>::value && e_w_ptr ),
            "Type Error : Cannot be converted."
        );
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        delete[] this->items_;
        this->items_ = other.items_;
        other.items_ = new e_T*[this->size_];
        return *this;
    }
    
	virtual ~TemplateSizedCollection() {
		delete [] *items_;
	} 
    
    NumericCollection<T>& operator- (const NumericCollection<T> & other) const override {
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
    	for (int i=0; i<this->size_; ++i) {
            *(res->items_[i]) = *(this->items_[i]) - other.getItem(i);
		}
		return *res;
	}
    
    NumericCollection<T>& operator+ (const NumericCollection<T> & other) const override {
        if (this->size_!=other.getSize()) throw "Sizes must be equal.";
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
    	for (int i=0; i<this->size_; ++i) {
            *(res->items_[i]) = *(this->items_[i]) - other.getItem(i);
		}
		return *res;
	}
    
    NumericCollection<T>& operator-() const override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
    	for (int i=0; i<this->size_; ++i) {
            
            
            *(res->items_[i]) = - *(this->items_[i]);
		}
		return *res;
	}
    
    NumericCollection<T>& operator+() const override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
        for (int i=0; i<this->size_; ++i) {
            *(res->items_[i]) = + *(this->items_[i]);
		}
		return *res;
	}
    
    NumericCollection<T>& operator*(const int scalar) const override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
        for (int i=0; i<this->size_; ++i) {
            *(res->items_[i]) = scalar * *(this->items_[i]);
    	}
		return *res;
	}

    /*template<typename e_T>
    friend NumericCollection<e_T>& operator* (const int scalar,const NumericCollection<e_T> &other) override {
        TemplateSizedCollection<T,size,with_pointer,void> *res = new TemplateSizedCollection<T,size,with_pointer,void>;
        for (int i=0; i<other.getSize(); ++i) {
            *(res->items_[i]) = scalar * other.getItem(i);
        }
		return *res;
    }*/
    
    void test() {
        std::cout << "4" << std::endl;
    }
};


int main()
{    

TemplateSizedCollection<int*,10,true> tscpt_0;
TemplateSizedCollection<int*,10,false> tscpf_0;
TemplateSizedCollection<int,10,true> tscnt_0;
TemplateSizedCollection<int,10,false> tscnf_0;
tscnf_0+tscnf_0;
tscnf_0-tscnf_0;
+tscnf_0;
-tscnf_0;
tscnf_0*89;
12*tscnf_0;

tscnt_0+tscnt_0;
tscnt_0-tscnt_0;
-tscnt_0;
+tscnt_0;
tscnt_0*20;
13*tscnt_0;

// Constructeurs de copie/conversion

TemplateSizedCollection<int*,10,true> tscpt_1(tscpt_0);
TemplateSizedCollection<int*,10,true> tscpt_2(tscpf_0);

TemplateSizedCollection<int*,10,false> tscpf_1(tscpt_0);
TemplateSizedCollection<int*,10,false> tscpf_2(tscpf_0);

TemplateSizedCollection<int,10,true> tscnt_1(tscnt_0);
TemplateSizedCollection<int,10,true> tscnt_2(tscnf_0);

TemplateSizedCollection<int,10,false> tscnf_1(tscnt_0);
TemplateSizedCollection<int,10,false> tscnf_2(tscnf_0);

// Constructeur de transfert

TemplateSizedCollection<int*,10,true> tscpt_3 = std::move(tscpt_1);
TemplateSizedCollection<int*,10,true> tscpt_4 = std::move(tscpf_1);

TemplateSizedCollection<int*,10,false> tscpf_3 = std::move(tscpt_1);
TemplateSizedCollection<int*,10,false> tscpf_4 = std::move(tscpf_1);

TemplateSizedCollection<int,10,true> tscnt_3 = std::move(tscnt_1);
//TemplateSizedCollection<int,10,true> tscnt_4 = std::move(tscnf_0); // impossible

//TemplateSizedCollection<int,10,false> tscnf_3 = std::move(tscnt_0); // impossible
TemplateSizedCollection<int,10,false> tscnf_4 = std::move(tscnf_1);

// Operateur d'assignation

tscpt_2 = tscpt_3;
tscpt_3 = tscpf_2;

tscpf_2 = tscpt_3;
tscpf_3 = tscpf_2;

tscnt_3 = tscnf_2;
//tscnt_2 = tscnt_3;

tscnf_2 = tscnt_3;
tscnf_0 = tscnf_2;

// Operateur de transfert

tscpt_3 = std::move(tscpt_2);
tscpt_2 = std::move(tscpf_3);

tscpf_3 = std::move(tscpt_2);
tscpf_2 = std::move(tscpf_3);

//tscnt_2 = std::move(tscnf_2); // impossible
tscnt_3 = std::move(tscnt_2);

//tscnt_2 = std::move(tscnf_1); // impossible
tscnt_3 = std::move(tscnt_2);

std::cout << "okçamarche" << std::endl;
}