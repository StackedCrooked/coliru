#include <iostream>
#include <functional>
#include <cassert>

#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

//------------------------------------------------------------------------------

template<typename T> struct Leaf {};
template<typename T> struct Branch;

template<typename T> struct CreateTreeType {
    typedef boost::variant<boost::recursive_wrapper<Leaf<T>>::type, 
            boost::recursive_wrapper<Branch<T>>::type> type;
};

template<typename T> struct Branch {
    typedef typename CreateTreeType<T>::type Tree;
    Branch(const T& value, const Tree& left, const Tree& right)
		: value(value), left(left), right(right) {}
	T value;
	Tree left;
	Tree right;
};

//------------------------------------------------------------------------------

// implicit constructor of boost::variant
template<typename T, typename Tree> Tree empty() { return Leaf<T>(); }

template<typename T, typename Tree> Tree singleton(const T& value) { 
	return Branch<T>(value, empty<T, Tree>(), empty<T, Tree>()); }

//------------------------------------------------------------------------------

template<typename T, typename Tree> 
struct InsertVisitor : boost::static_visitor<Tree> {
    InsertVisitor(T val) : val(val) {}
    Tree operator ()(Leaf<T>& l) { 
        return Branch<T>(val, Leaf<T>(), Leaf<T>());  }
    Tree operator ()(Branch<T>& b) { 
        if (val < b.value) {
            return Branch<T>(b.value, insert(val, b.left), b.right);
        } else {
            return Branch<T>(b.value, b.left, insert(val, b.right));
        }
    }
private:
    T val;    
};

//------------------------------------------------------------------------------

template<typename T, typename Tree> Tree insert(const T& value, Tree& tree) {
    typedef InsertVisitor<T, Tree> InsertVisitor;
    return boost::apply_visitor(InsertVisitor(value), tree);
}

//------------------------------------------------------------------------------

template<typename T, typename U, typename Tree> struct FoldVisitor;

//------------------------------------------------------------------------------

template<typename T, typename U, typename Tree> 
U fold(std::function<U(T, U, U)> f, U z, Tree tree) {
    return boost::apply_visitor(FoldVisitor<T, U, Tree>(z, f), tree);
}

//------------------------------------------------------------------------------

template<typename T, typename U, typename Tree> 
struct FoldVisitor : boost::static_visitor<Tree> {
    FoldVisitor(T value, std::function<U(T, U, U)> f) : value(value), f(f) {}
    Tree operator ()(Leaf<T>&) { return value; }
    Tree operator ()(Branch<T>& b) {
        return f(b.value, fold(f, value, b.left), fold(f, value, b.right));
    }
private:
    T value;
    std::function<U(T, U, U)> f;
};

//------------------------------------------------------------------------------
/*
template<typename T, typename Tree> 
IntTreeVisitor : boost::static_visitor<Tree> {
    IntTreeVisitor(T val) : val(val) {}
    Tree operator ()(Leaf<T>&) { return singleton(val); }
    Tree operator ()(Branch<T>& b) {
           
    }
private:
    T val;
};
*/
template<typename T, typename Tree> Tree intTree_(T value, Tree tree) {
	for (T i = value; i > 0; --i) {
		tree = insert(i, tree);
	}
	return tree;
}

template<typename T, typename Tree> Tree intTree(T value) {
	//assert(value > 0);
	return intTree_(value, empty<T, Tree>());
}

int main() {
    
	typedef CreateTreeType<int>::type Tree;
	Tree tree = intTree<int, Tree>(3);
	
	return 0;
}