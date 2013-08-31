#include <iterator>

template <class ItSource, class ItPredicate>
class ConditionalIterator
{
    ItSource _srcBegin;
    ItSource _srcEnd;

    ItPredicate _predBegin;
    ItPredicate _predEnd;
public:
    typedef ConditionalIterator & Reference;
    typedef typename std::iterator_traits<ItSource>::value_type ValueType;

    ConditionalIterator(ItSource srcBegin, ItSource srcEnd,
                        ItPredicate predBegin, ItPredicate predEnd)
                        : _srcBegin(srcBegin)
                        , _srcEnd(srcEnd)
                        , _predBegin(predBegin)
                        , _predEnd(predEnd)
    {
        while (_predBegin != _predEnd &&
               _srcBegin != _srcEnd &&
               *_predBegin) 
        {
            ++_predBegin;
            ++_srcBegin;
        }
    }

    Reference operator++()
    {
        do 
        {
            ++_predBegin;
            ++_srcBegin;
        }
        while (_predBegin != _predEnd &&
               _srcBegin != _srcEnd &&
               *_predBegin);
        return (*this);
    }
    ConditionalIterator operator++(int) {ConditionalIterator t(*this); operator++(); return t;}

    operator bool() const
    {
        return (_srcBegin != _srcEnd &&
                _predBegin != _predEnd);
    }

    ValueType operator*()
    {
        return (*_srcBegin);
    }
};

template <class ItSource, class ItPredicate>
ConditionalIterator<ItSource, ItPredicate> 
make_conditional_iterator(ItSource fs, ItSource es, ItPredicate fp, ItPredicate ep) 
{return ConditionalIterator<ItSource, ItPredicate>(fs, es, fp, ep);}

#include <array>
#include <iostream>

int main() {
    std::array<int,5>  element={ 1   , 2   , 4    , 8    , 10   };
    std::array<bool,5> deleted={ true, true, false, false, true };
    
    auto cit = make_conditional_iterator(element.begin(), element.end(), deleted.begin(), deleted.end());
    while (cit)
    {
        std::cout << *cit << std::endl;
        cit++;
    }
}