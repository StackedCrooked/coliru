#include <cassert>

#include <iostream>
#include <iterator>
#include <memory>

    typedef int Point;
    
    class DataIterator;
 
    class Data {
    public:
        friend class DataIterator;
        
        Data(Point a, Point b, Point c): _one(a), _two(b), _three(c) {}

        DataIterator begin();
        DataIterator end();

    private:
        Point _one; 
        Point _two;
        Point _three;
    }; // class Data

    class DataIterator:
        public std::iterator<std::forward_iterator_tag, Point>
    {
    public:
        struct BeginTag{};
        struct EndTag{};
    
        DataIterator(): _data(0), _member(0) {}

        DataIterator(Data& data, BeginTag): _data(&data), _member(0) {}
        DataIterator(Data& data, EndTag): _data(&data), _member(N) {}

        reference operator*() const {
            this->ensure_valid();
            MemberPtr const ptr = Pointers[_member];
            return _data->*ptr;
        }

        pointer operator->() const { return std::addressof(*(*this)); }

        DataIterator& operator++() { this->ensure_valid(); ++_member; return *this; }
        DataIterator operator++(int) { DataIterator tmp(*this); ++*this; return tmp; }
        
        friend bool operator==(DataIterator const& left, DataIterator const& right) {
            return left._data == right._data and left._member == right._member;
        }
        
        friend bool operator!=(DataIterator const& left, DataIterator const& right) {
            return not (left == right);
        }

    private:
        typedef Point Data::*MemberPtr;

        static size_t const N = 3;
        static MemberPtr const Pointers[N];

        void ensure_valid() const { assert(_data and _member < N); }

        Data* _data;
        size_t _member;
    }; // class DataIterator

    //
    // Implementation
    //
    DataIterator Data::begin() { return DataIterator(*this, DataIterator::BeginTag{}); }
    DataIterator Data::end() { return DataIterator(*this, DataIterator::EndTag{}); }
    
    size_t const DataIterator::N;

    DataIterator::MemberPtr const DataIterator::Pointers[DataIterator::N] = {
        &Data::_one, &Data::_two, &Data::_three
    };
    
    int main() {
        Data d(1, 2, 3);
        
        for (Point& p: d) { ++p; }
        
        for (Point const& p: d) { std::cout << p << "\n"; }
    }
    
    
    