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
  template<class...Is, std::enable_if_t<sizeof...(Is) == N>>
  T& operator()(size_t i, Is...is)&&{
    return std::move(*this)[i](is...);
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
  T& operator()(size_t i)&&{
    return std::move(*this)[i];
  }
};

template<class T, size_t N>
struct n_dim_array {
  template<class...Szs, class=std::enable_if_t<sizeof...(Szs)==N>>
  explicit n_dim_array( Szs... sizes ):
    szs{ { static_cast<size_t>(sizes)... } }
  {
    size_t sz = 1;
    for( size_t s : szs )
      sz *= s;
    buffer.resize(sz);
  }
  n_dim_array( n_dim_array const& o ) = default;
  n_dim_array& operator=( n_dim_array const& o ) = default;


  using top_level_index = array_index<T,N-1>;
  top_level_index index(){return {szs.data(),0,buffer.data()};}
  auto operator[]( size_t i ) {
    return index()[i];
  }
  using const_top_level_index = array_index<const T,N-1>;
  const_top_level_index index()const{return {szs.data(),0,buffer.data()};}
  auto operator[]( size_t i ) const {
    return index()[i];
  }
  template<class...Is,class=std::enable_if_t<sizeof...(Is)==N>>
  T& operator()(Is...is){
    return index()(is...);
  }
  template<class...Is,class=std::enable_if_t<sizeof...(Is)==N>>
  T const& operator()(Is...is) const {
    return index()(is...);
  }
private:
  n_dim_array() = delete;
  std::array<size_t,N> szs;
  std::vector<T> buffer;
};

    
int main() {
    n_dim_array<int, 3> arr{ 3,2,2 };
    arr[1][1][1] = 3;
    std::cout << arr[1][1][1] << "\n";
}