#include <boost/variant.hpp>
#include <utility>
 
typedef boost::variant<
    	int,
		std::pair<int, int>
		// and other stuff later
	> cval_t;

template<class T>
class HierarchyOperatorInterface : public boost::static_visitor<cval_t> {
	public:
	HierarchyOperatorInterface() { }
 
	cval_t operator()(const int& oldval, const int& newval)
    {
        return static_cast<T&>(*this)(oldval, newval);
    }
	cval_t operator()(const int& oldval, const std::pair<int, int>& newval) const
    {
        return static_cast<const T&>(*this)(oldval, newval);
    }
	cval_t operator()(const std::pair<int, int>& oldval, const int& newval) const
    {
        return static_cast<const T&>(*this)(oldval, newval);
    }
	cval_t operator()(const std::pair<int, int>& oldval, const std::pair<int, int>& newval) const
    {
        return static_cast<const T&>(*this)(oldval, newval);
    }
};

class Operator1 : public HierarchyOperatorInterface<Operator1> {
	public:
	cval_t operator()(const int& oldval, const int& newval) const {
		cval_t answer;
		// do some stuff...
		return answer;
	}
	cval_t operator()(const int& oldval, const std::pair<int, int>& newval) const {
		// do something different
		return cval_t();
	}
	cval_t operator()(const std::pair<int, int>& oldval, const int& newval) const {
		// do something else different
		return cval_t();
	}
	cval_t operator()(const std::pair<int, int>& oldval, const std::pair<int, int>& newval) const {
		// do something yet still different
		return cval_t();
	}
};

class Operator2 : HierarchyOperatorInterface<Operator2>
{
    template <typename T, typename U>
    cval_t operator()(const T& oldval, const U& newval) const {
		return oldval;
	}    
};

int 
main() { 
    Operator2 op;
}
