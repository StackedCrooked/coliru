#include <utility>
#include <array>
#include <cstddef>
#include <vector>
#include <iostream>

using std::size_t;

    template<class T, size_t N>
    struct array_index {
      size_t const* dimensions;
      size_t offset;
      T* buffer;
      array_index<T,N-1> operator[](size_t i)&&{
        return {dimensions+1, (offset+i)* *dimensions, buffer};
      }
      array_index<T,N-1> const operator[](size_t i) const&&{
        return {dimensions+1, (offset+i)* *dimensions, buffer};
      }
    };
    template<class T>
    struct array_index<T,0> {
      size_t const* dimension;
      size_t offset;
      T* buffer;
      T& operator[](size_t i)&&{
        return buffer[i+offset];
      }
      T const& operator[](size_t i)const&&{
        return buffer[i+offset];
      }
    };
    
    template<class T, size_t N>
    struct n_dim_array {
      template<class...Szs, class=std::enable_if_t<sizeof...(Szs)==N>>
      explicit n_dim_array( Szs... sizes ):
        szs{{ static_cast<size_t>(sizes)... }}
      {
        size_t sz = 1;
        for( size_t s : szs )
          sz *= s;
        buffer.resize(sz);
      }
      n_dim_array( n_dim_array const& o ):
        szs(o.szs),
        buffer(o.buffer)
      {}
      n_dim_array& operator=( n_dim_array const& o ) {
        szs = o.szs;
        buffer = o.buffer;
        return *this;
      }
      const std::array<size_t,N> szs;
      std::vector<T> buffer;
      auto operator[]( size_t i ) {
        return array_index<T,N-1>{szs.data(),0,buffer.data()}[i];
      }
      auto operator[]( size_t i ) const {
        using helper = array_index<T,N-1> const;
        return helper{szs.data(),0,buffer.data()}[i];
      }
    private:
      n_dim_array() = delete;
    };
    
int main() {
    n_dim_array<int, 3> arr{ 3,2,2 };
    arr[1][1][1] = 3;
    std::cout << arr[1][1][1] << "\n";
}