#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

template< typename T >
struct Array2D {
    Array2D() = default;
    Array2D( size_t w, size_t h ) : width_(w), height_(h) {}
    
    // do not provide move semantic
    Array2D( Array2D && steal ) = delete;
    Array2D& operator=( Array2D && ) = delete;
    
    // copy semantics need to copy the data
    Array2D( Array2D const & other ) : Array2D( other.width_, other.height_ ) {
        std::copy_n( other.data_.get(), width_ * height_, data_.get() );
    }
    
    Array2D& operator=( Array2D const & other ) {
        if ( &other != this ) {
            width_ = other.width_;
            height_ = other.height_;
            data_.reset( new T[ width_ * height_ ] );
            std::copy_n( other.data_.get(), width_ * height_, data_.get() );
        }
    }
    
    // helper proxy to add support for a tab[][] syntax, use also for iteration
    // over the rows
    template < bool useConst >
    struct Array1DRefT {
        using Pointer   = typename std::conditional<useConst, T const *, T *>::type;
        using Reference = typename std::conditional<useConst, T const &, T &>::type;
        
        Array1DRefT( Pointer row, size_t width ) : row_( row ), width_( width ) {}
        
        // the [j] of tab[i][j]
        Reference operator[]( int column ) const { return *(row_ + column); }
        
        // use by for loop on columns
        Pointer begin() { return row_; }
        Pointer end() { return row_ + width_; }
        
        // iterator stuff use by for loop on rows
        Array1DRefT&       operator*() { return *this; }
        Array1DRefT const& operator*() const { return *this; }
        Array1DRefT&       operator++( int ) { row_ += width_; return *this; }
        Array1DRefT        operator++() { auto old = *this; row_ += width_; return old; }
        
        friend bool operator !=( Array1DRefT const & a, Array1DRefT const & b ) {
            return a.row_ != b.row_;
        }
    private:
        Pointer row_;
        size_t width_;
    };
    
    // iterators for const Array2D and non const Array2D
    using Array1DRef      = Array1DRefT<false>;
    using Array1DConstRef = Array1DRefT<true>;
    
    // the [i] of tab[i][j]
    Array1DConstRef operator[] ( int row ) const { return { data_.get() + row * width_, width_ }; }
    Array1DRef      operator[] ( int row )       { return { data_.get() + row * width_, width_ }; }
    
    // entry point for range based for loop
    Array1DRef begin() { return operator[]( 0u ); };
    Array1DRef end() { return operator[]( height_ ); };
    Array1DConstRef begin() const { return operator[]( 0u ); };
    Array1DConstRef end() const { return operator[]( height_ ); };
    
private:
    size_t width_ = 0; // some default
    size_t height_ = 0;
    std::unique_ptr<T[]> data_ { width_ * height_ ? new T[ width_ * height_ ] : nullptr };
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Array2D<T>& tab) {
    for ( auto row : tab ) {
        os << "( ";
        bool first = true;
        for ( auto & column : row ) {
            if ( !first )
                os << ", ";
            else
                first = false;
            
            os << column;
        }
        os << " )" << std::endl;
    }
    
    return os;
}

int main()
{
    Array2D<int> tab01 { 5, 3 };
    
    for ( auto row : tab01 ) {
        for ( auto & column : row ) {
            column = rand() % 10;
        }
    }
   
    std::cout << "tab01" << std::endl << tab01 << std::endl;
    
    auto tab02 = tab01; // copy
    tab02[2][2] = 42; // access
    std::cout << "tab02" << std::endl << tab02 << std::endl;
    
    //tab02 = std::move( tab01 ); // move is deleted
}
