#include <iostream>
#include <vector>

template <typename T>
void print_collection(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
  std::cout << "collection = { ";
  for(; start != end; ++start) {
    std::cout << *start << ", ";
  }
  std::cout << "};" << std::endl;
}


template <typename T>
void bubble_sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
  typename std::vector<T>::iterator i, j;
  int temp;
  bool swapped = false;

  do {
    swapped = false;
    i = start;
    j = start;
    ++j;

    for(; j != end; ++i, ++j) {
      if (*j < *i) {
        temp = *j;
        *j = *i;
        *i = temp;
        swapped = true;
      }
    }
  } while (swapped);
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


template <typename T>
void merge_sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, int len) {
  if(len <= 1) {
    return;
  }
  int odd, left_len, right_len;
  typename std::vector<T>::iterator pivot;
  odd = len % 2;
  left_len = (len / 2) + odd;
  pivot = start + left_len;
  right_len = len / 2;
  
  merge_sort<T>(start, pivot, left_len);
  merge_sort<T>(pivot, end, right_len);
  merge<T>(start, pivot, end, left_len, right_len);
}


int main(void) {
  std::vector<double> vl = { 1.1, 9.1, 2.1, 8.1, 3.1, 7.1, 4.1, 6.1, 5.1, 0.1 };
  print_collection<double>(vl.begin(), vl.end());
  merge_sort<double>(vl.begin(), vl.end(), vl.size());
  print_collection<double>(vl.begin(), vl.end());
  return 0;
}