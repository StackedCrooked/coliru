#include <boost/range/adaptor/transformed.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/deque.hpp>
#include <boost/range/algorithm.hpp>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <limits>

template<typename InputIterator>
class tee_iterator : public boost::iterator_facade
    <
        tee_iterator<InputIterator>,
        const typename std::iterator_traits<InputIterator>::value_type,
        boost::forward_traversal_tag
    >
{
    typedef typename std::iterator_traits<InputIterator>::value_type Value;
    typedef unsigned Index;
    struct Data
    {
        boost::container::deque<Value> values;
        boost::container::vector<tee_iterator*> iterators;
        InputIterator current,end;
        Index min_index, current_index;
        Index poped_from_front;
        //
        Data(InputIterator first,InputIterator last)
            : current(first), end(last), min_index(0), current_index(0), poped_from_front(0)
        {}
        ~Data()
        {
            assert(iterators.empty());
        }
    };
    boost::shared_ptr<Data> shared_data;
    Index index;
    static Index get_index(tee_iterator *p)
    {
        return p->index;
    }
public:
    tee_iterator()
        : index(std::numeric_limits<Index>::max())
    {}
    tee_iterator(InputIterator first,InputIterator last)
        : shared_data(boost::make_shared<Data>(first,last)), index(0)
    {
        shared_data->iterators.push_back(this);
    }
    tee_iterator(const tee_iterator &x)
        : shared_data(x.shared_data), index(x.index)
    {
        if(shared_data)
            shared_data->iterators.push_back(this);
    }
    friend void swap(tee_iterator &l,tee_iterator &r)
    {
        using std::swap;
        *boost::find(l.shared_data->iterators,&l) = &r;
        *boost::find(r.shared_data->iterators,&r) = &l;
        swap(l.shared_data,r.shared_data);
        swap(l.index,r.index);
    }
    tee_iterator &operator=(tee_iterator x)
    {
        swap(x,*this);
    }
    ~tee_iterator()
    {
        if(shared_data)
        {
            erase_from_iterators();
            if(!shared_data->iterators.empty())
            {
                using boost::adaptors::transformed;
                shared_data->min_index = *boost::min_element(shared_data->iterators | transformed(&get_index));
                Index to_pop = shared_data->min_index - shared_data->poped_from_front;
                if(to_pop>0)
                {
                    shared_data->values.erase(shared_data->values.begin(), shared_data->values.begin()+to_pop);
                    shared_data->poped_from_front += to_pop;
                }
            }
        }
    }
private:
    friend class boost::iterator_core_access;
    void erase_from_iterators()
    {
        shared_data->iterators.erase(boost::find(shared_data->iterators,this));
    }
    bool last_min_index() const
    {
        return boost::count
        (
            shared_data->iterators | boost::adaptors::transformed(&get_index),
            shared_data->min_index
        )==1;
    }
    Index obtained() const
    {
        return Index(shared_data->poped_from_front + shared_data->values.size());
    }
    void increment()
    {
        if((shared_data->min_index == index) && last_min_index())
        {
            shared_data->values.pop_front();
            ++shared_data->min_index;
            ++shared_data->poped_from_front;
        }
        ++index;
        if(obtained() <= index)
        {
            ++shared_data->current;
            if(shared_data->current != shared_data->end)
            {
                shared_data->values.push_back(*shared_data->current);
            }
            else
            {
                erase_from_iterators();
                index=std::numeric_limits<Index>::max();
                shared_data.reset();
            }
        }
    }
    bool equal(const tee_iterator& other) const
    {
        return (shared_data.get()==other.shared_data.get()) && (index == other.index);
    }
    const Value &dereference() const
    {
        if((index==0) && (obtained() <= index))
        {
            shared_data->values.push_back(*(shared_data->current));
        }
        assert( (index-shared_data->poped_from_front) < shared_data->values.size());
        return shared_data->values[index-shared_data->poped_from_front];
    }
};

template<typename InputIterator>
tee_iterator<InputIterator> make_tee_iterator(InputIterator first,InputIterator last)
{
    return tee_iterator<InputIterator>(first,last);
}

template<typename InputIterator>
boost::iterator_range< tee_iterator<InputIterator> > tee_range(InputIterator first,InputIterator last)
{
    return boost::iterator_range< tee_iterator<InputIterator> >
    (
        tee_iterator<InputIterator>(first,last),
        tee_iterator<InputIterator>()
    );
}
// _______________________________________________________ //

#include <iostream>
#include <ostream>
#include <sstream>

int main()
{
    using namespace std;
    stringstream ss;
    ss << "1 2 3 4 5";
    istream_iterator<int> first(ss /*cin*/ ),last;
    typedef boost::iterator_range< tee_iterator< istream_iterator<int> > > Range; // C++98
    Range r1 = tee_range(first,last);
    Range r2 = r1, r3 = r1;
    boost::copy(r1,ostream_iterator<int>(cout," "));
    cout << endl;
    boost::copy(r2,ostream_iterator<int>(cout," "));
    cout << endl;
    boost::copy(r2,ostream_iterator<int>(cout," "));
}
