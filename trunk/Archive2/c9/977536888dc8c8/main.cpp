#include <iterator>
#include <boost/foreach.hpp>

class MyClass
{
private:
    int* data  = nullptr;
    int length = 100;

public:
    class MyIterator : public std::iterator<std::forward_iterator_tag, int>
    {
        public:
            MyIterator(int* data, int length, bool end = false)
            {
                this->data= data;
                this->length= length;
                if(end)
                    pointer=-1;
            }
            MyIterator& operator++()
            {
                if(pointer!= length-1) {
                    pointer++;
                }
                else {
                    pointer= -1;
                }
                return *this;
            }

            bool operator==(const MyIterator& other) const { return pointer==other.pointer; }
            bool operator!=(const MyIterator& other) const { return pointer!= other.pointer; }
            int& operator*() const
            {
                if(pointer==-1)
                    return nullvalue;
                else
                    return data[pointer];
            }
        private:
            value_type* data     = nullptr;
            int length;
            int pointer          = 0;
            mutable value_type nullvalue = 0;
    };

    class MyConstIterator : public std::iterator<std::forward_iterator_tag, const int>
    {
        public:
            MyConstIterator(int const* data, int length, bool end = false)
            {
                this->data= data;
                this->length= length;
                if(end)
                    pointer=-1;
            }
            MyConstIterator& operator++()
            {
                if(pointer!= length-1) {
                    pointer++;
                }
                else {
                    pointer= -1;
                }
                return *this;
            }

            bool operator==(const MyConstIterator& other) const { return pointer==other.pointer; }
            bool operator!=(const MyConstIterator& other) const { return pointer!= other.pointer; }
            int const& operator*() const
            {
                if(pointer==-1)
                    return nullvalue;
                else
                    return data[pointer];
            }
        private:
            value_type* data     = nullptr;
            int length;
            int pointer          = 0;
            value_type nullvalue = 0;
    };

public:
    typedef MyIterator iterator_type;
    typedef MyConstIterator const_iterator_type;

    MyClass()
    {
        data= new int[length];
        for(int i=0; i<length;i++)
            data[i]=i+1;
    }
    ~MyClass() {
        delete[] data;
    }
    iterator_type begin()             { return MyIterator(data,length);      }
    iterator_type end()               { return MyIterator(data,length,true); }
    const_iterator_type begin() const { return MyConstIterator(data,length);      }
    const_iterator_type end()   const { return MyConstIterator(data,length,true); }
};

namespace boost {
    template<> struct range_mutable_iterator<MyClass> {
        typedef MyClass::MyIterator type;
    };

    template<> struct range_const_iterator<MyClass> {
        typedef MyClass::MyConstIterator type;
    };
}

#include <iostream>

int main()
{
    MyClass c;
    BOOST_FOREACH(int i, c) {
        std::cout << i << "\n";
    }
}
