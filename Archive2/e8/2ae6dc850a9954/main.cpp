#include <memory>
#include <string>
#include <vector>
#include <list>
#include <iostream>

template<class TrackType> 
std::size_t* mem_used() {static std::size_t s = 0; return &s;}

template<class T, class TrackType, class BaseAllocator = std::allocator<T> > 
class TrackerAllocator : public BaseAllocator {
public:
    typedef typename BaseAllocator::pointer pointer;
    typedef typename BaseAllocator::size_type size_type;

    TrackerAllocator() throw() : BaseAllocator() {}
    TrackerAllocator(const TrackerAllocator& b) throw() : BaseAllocator(b) {}
    //TrackerAllocator(TrackerAllocator&& b) throw() : BaseAllocator(b) {}
    //template <class U> TrackerAllocator(const typename TrackerAllocator::template rebind<U>::other& b) throw() : BaseAllocator(b) {}
    template <class U> TrackerAllocator(const TrackerAllocator<U, TrackType, typename BaseAllocator::template rebind<U>::other>& b) throw() : BaseAllocator(b) {}
    ~TrackerAllocator() {}

    template<class U> struct rebind {
        typedef TrackerAllocator<U, TrackType, typename BaseAllocator::template rebind<U>::other> other;
    };

    pointer allocate(size_type n) {
        pointer r = BaseAllocator::allocate(n);
        *mem_used<TrackType>() += n;
        return r;
    }
    pointer allocate(size_type n, pointer h) {
        pointer r = BaseAllocator::allocate(n, h);
        *mem_used<TrackType>() += n;
        return r;
    }
    void deallocate(pointer p, size_type n) throw() {
        BaseAllocator::deallocate(p, n);
        *mem_used<TrackType>() -= n;
    }
};

typedef std::basic_string<char, 
                          std::char_traits<char>,
                          TrackerAllocator<char, std::string> > trackstring;
typedef std::vector<int, 
                    TrackerAllocator<int, std::vector<int> > > trackvector;
//                                        ^              ^
//                                        This identifies which memory to track
//                                        it can be any type, related or no.
//                                        All with the same type will be tracked togeather
typedef std::list<int, 
                    TrackerAllocator<int, std::list<int> > > tracklist;
int main() {
    trackstring mystring1("HELLO WORLD");
    std::cout << *mem_used<std::string>() << '\n'; //display memory usage of all strings

    trackstring mystring2("MUCH LONGER STRING THAT DEFINITELY GETS HEAP ALLOCATED!");
    std::cout << *mem_used<std::string>() << '\n'; //display memory usage of all strings

    trackvector myvec(mystring1.begin(), mystring1.end());
    std::cout << *mem_used<std::vector<int> >() << '\n'; //display memory usage of all vector<int>
    //                     ^              ^
    //                     This identifies which memory type from above to look up.
    tracklist mylist(mystring1.begin(), mystring1.end());
    std::cout << *mem_used<std::list<int> >() << '\n'; //display memory usage of all list<int>
    return 0;
}
