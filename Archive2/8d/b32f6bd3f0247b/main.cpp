#include <boost/variant.hpp>
#include <utility>
 
typedef boost::variant<
    	int,
		std::pair<int, int>
		// and other stuff later
	> cval_t;
 
class HierarchyOperatorInterface : public boost::static_visitor<cval_t> {
	public:
	HierarchyOperatorInterface() { }
	virtual ~HierarchyOperatorInterface() = 0;
 
	virtual cval_t operator()(const int& oldval, const int& newval) const = 0;
	virtual cval_t operator()(const int& oldval, const std::pair<int, int>& newval) const = 0;
	virtual cval_t operator()(const std::pair<int, int>& oldval, const int& newval) const = 0;
	virtual cval_t operator()(const std::pair<int, int>& oldval, const std::pair<int, int>& newval) const = 0;
};
inline HierarchyOperatorInterface::~HierarchyOperatorInterface() { }
 
class Operator1 : public HierarchyOperatorInterface {
	public:
	virtual cval_t operator()(const int& oldval, const int& newval) const {
		cval_t answer;
		// do some stuff...
		return answer;
	}
	virtual cval_t operator()(const int& oldval, const std::pair<int, int>& newval) const {
		// do something different
		return cval_t();
	}
	virtual cval_t operator()(const std::pair<int, int>& oldval, const int& newval) const {
		// do something else different
		return cval_t();
	}
	virtual cval_t operator()(const std::pair<int, int>& oldval, const std::pair<int, int>& newval) const {
		// do something yet still different
		return cval_t();
	}
};

template <typename T, typename U>
struct identity_operator : public virtual HierarchyOperatorInterface {
    cval_t operator () (const T& oldval, const U&) const {
        return oldval;
    }
};
 
class Operator2 
    : public identity_operator<int, int>
    , public identity_operator<int, std::pair<int, int>>
    , public identity_operator<std::pair<int, int>, int>
    , public identity_operator<std::pair<int, int>, std::pair<int, int>>
{ };

int 
main() { 
    Operator2 op;
}
