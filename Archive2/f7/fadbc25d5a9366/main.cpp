#include <iostream>
#include <vector>

template <typename Iter>
void print_collection(Iter start, Iter end) {
  std::cout << "collection = { ";
  for(; start != end; ++start) {
    std::cout << *start << ", ";
  }
  std::cout << "};" << std::endl;
}


template <typename T>
void merge(typename std::vector<T>::iterator start, typename std::vector<T>::iterator pivot, typename std::vector<T>::iterator end, int left_len, int right_len) {
  std::vector<T> temp;
  typename std::vector<T>::iterator i, j;
  i = start;
  j = pivot;
  while(i != pivot && j != end) {
    if(*i <= *j) {
      temp.push_back(*i);
      ++i;
    } else if(*i > *j) {
      temp.push_back(*j);
      ++j;
    }
  }
  for(; i != pivot; ++i) {
    temp.push_back(*i);
  }
  for(; j != end; ++j) {
    temp.push_back(*j);
  }
  i = start;
  j = temp.begin();
  for(; i != end, j != temp.end(); ++i, ++j) {
    *i = *j;
  }
}


template <typename Iter>
void merge_sort(Iter start, Iter end, int len) {
  if(len <= 1) {
    return;
  }
  int odd, left_len, right_len;
  Iter pivot;
  odd = len % 2;
  left_len = (len / 2) + odd;
  pivot = start + left_len;
  right_len = len / 2;

  merge_sort(start, pivot, left_len);
  merge_sort(pivot, end, right_len);
  merge(start, pivot, end, left_len, right_len);
}


int main(void) {
  std::vector<double> vl = { 1.1, 9.1, 2.1, 8.1, 3.1, 7.1, 4.1, 6.1, 5.1, 0.1 };
  print_collection(vl.begin(), vl.end());
  merge_sort(vl.begin(), vl.end(), vl.size());
  print_collection(vl.begin(), vl.end());
  return 0;
}