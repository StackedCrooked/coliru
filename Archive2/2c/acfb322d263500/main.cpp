#include <iostream>
#include <sstream>

class range {
 public:
   class iterator {
      friend class range;
    public:
      long int operator *() const { return i_; }
      const iterator &operator ++() { ++i_; return *this; }
      iterator operator ++(int) { iterator copy(*this); ++i_; return copy; }

      bool operator ==(const iterator &other) const { return i_ == other.i_; }
      bool operator !=(const iterator &other) const { return i_ != other.i_; }

    protected:
      iterator(long int start) : i_ (start) { }

    private:
      unsigned long i_;
   };

   iterator begin() const { return begin_; }
   iterator end() const { return end_; }
   range(long int  begin, long int end) : begin_(begin), end_(end) {}
private:
   iterator begin_;
   iterator end_;
};

int main() {
      int m, n;
      std::istringstream in("10 20");
      if ( in >> m >> n ) //using in, because std::cin cannot be used at coliru.
      {
        if ( m > n ) std::swap(m,n); 
        for (auto i : range(m,n)) 
        {
             std::cout << i << " ";
        }
      }
      else 
        std::cout <<"invalid input";
}