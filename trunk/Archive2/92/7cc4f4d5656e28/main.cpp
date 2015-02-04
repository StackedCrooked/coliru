#include<vector>
#include<cstdio>

template<class Iter>
Iter adjacent_find_n(Iter first, Iter last, std::size_t n, std::size_t offset)
{
  if( first == last )
    return last;

  if( offset > 1 ){
    if(!(*first == *(first - 1))) {
      offset = 1;
    }

    if( offset == n ){
      return first-(n-1);
    }
  }

  return adjacent_find_n(++first, last, n, ++offset);
}

template<class Iter>
Iter adjacent_find_n(Iter first, Iter last, std::size_t n)
{
  return adjacent_find_n(first, last, n, 1);
}


int main(){
  std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6};

  auto pos = adjacent_find_n(values.begin(), values.end(), 3);

  while( pos != values.end() ){
    printf("%d ", *pos);
    pos++;
  }

  printf("\n");

  return 0;
}