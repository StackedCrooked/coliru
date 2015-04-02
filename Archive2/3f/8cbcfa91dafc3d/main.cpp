// map::emplace
#include <iostream>
#include <map>
#include <memory>
#include <algorithm>
#include <future>
#include <thread>

template<class I, class F>
void parallel_for_each(I rangeStart, I rangeEnd, F callback, int numSegments = 0)
{
    int numValues = std::distance(rangeStart,rangeEnd);
    numSegments = numSegments > 0 ? numSegments : numValues;
    int segmentSize = numValues/numSegments;
    
    std::vector<std::future<void>> futures(numSegments);
    int segment = 0;
    for (auto &future: futures)
    {
        future = std::async([=,&callback](){
            auto segmentStart = rangeStart + segment*segmentSize;
            auto segmentEnd =  segment+1 < numSegments ? rangeStart + (segment+1)*segmentSize : rangeEnd;
    
            for (auto i = segmentStart; i != segmentEnd; ++i) callback(*i);
        });
        ++segment;
    }
    
    for (auto &future: futures)
    {
        future.wait();
    }
}

template<class T, class F>
void parallel_for_each(T range, F callback, int numSegments)
{
    parallel_for_each(std::begin(range), std::end(range), callback, numSegments);
}

class Range
{
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, int>
    {
        public:
           Iterator (): _index(0) {}
           Iterator (int i): _index(i) {}
           Iterator (const Iterator &other) = default;
           Iterator &operator = (const Iterator &) = default;
           
           int operator * () const { return _index; }
           
           Iterator &operator ++ () { _index++; return *this; }
           Iterator operator ++ (int) { Iterator tmp(*this); _index++; return tmp; }
           Iterator &operator -- () { _index--; return *this; }
           Iterator operator -- (int) { Iterator tmp(*this); _index--; return tmp; }
           
           bool operator == (const Iterator &other) const { return _index == other._index; }
           bool operator != (const Iterator &other) const { return _index != other._index; }
           
           Iterator &operator += (difference_type d) { _index += d; return *this; }
           Iterator &operator -= (difference_type d) { _index -= d; return *this; }
           
           Iterator operator + (difference_type d) const { return Iterator(_index+d); }
           Iterator operator - (difference_type d) const { return Iterator(_index-d); }
           
           int operator [] (difference_type d) const { return _index + d; }
           
           bool operator < (const Iterator &other) const { return _index < other._index; }
           bool operator > (const Iterator &other) const { return _index > other._index; }
           bool operator <= (const Iterator &other) const { return _index <= other._index; }
           bool operator >= (const Iterator &other) const { return _index >= other._index; }
           
           difference_type operator - (const Iterator &other) const { return _index - other._index; }
           
    private:
        int _index;
    };

    Range(int size, int offset = 0):
        _offset(offset),
        _size(size)
    {}
    
    Range(const Range &other) = default;
    Range &operator=(const Range &other) = default;
    
    Iterator begin() const { return Iterator(_offset); }
    Iterator end() const { return Iterator(_offset+_size); }

private:
    int _offset;
    int _size;
};

namespace std
{
    Range::Iterator begin(const Range &range) { return range.begin(); }
    Range::Iterator end(const Range &range)   { return range.end(); }
}

int main ()
{
  std::vector<int> values(100);
  int i = 0;
  for (auto &v: values) v = i++;
  
  parallel_for_each(Range(1000), [](int a) {
      printf("%d\n",a);
  }, 10);

  return 0;
}