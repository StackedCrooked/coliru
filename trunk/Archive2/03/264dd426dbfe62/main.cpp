#include <iostream>
#include <functional>
#include <cassert>

template<typename T> struct Leaf {};
template<typename T> struct Branch;

template<typename T> CreateTreeType {
    typedef boost::variant<Leaf<T>, Branch<T> > type;
};

template<typename T> struct Branch {
    typedef CreateTreeType<T>::type Tree;
    Branch(const T& value, const Tree& left, const Tree& right)
		: value(value), left(left), right(right) {}
	T value;
	Tree left;
	Tree right;
};

// implicit constructor of boost::variant
template<typename T, typename Tree> Tree empty() { return Leaf<T>(); }

template<typename T, typename Tree> Tree singleton(const T& value) { 
	return Branch<T>(value, empty<T, Tree>(), empty<T, Tree>()); }

template<typename T, typename Tree> struct InsertVisitor {
      
};

template<typename T> Tree<T>* insert(const T& value, Tree<T>* tree) {
	Branch<T>* branch = dynamic_cast<Branch<T>*>(tree);
	if (branch) {
		if (value < branch.value) {
			Tree<T>* tt = new Branch<T>(branch.value, insert(value, branch.left), 
				branch.right);
			delete tree;
			return tt;
		} else {
			Tree<T>* tt = new Branch<T>(branch.value, branch.left,
				insert(value, branch.right));
			delete tree;
			return tt;
		}
	}
	delete tree;
	return singleton(value);
}

template<typename T, typename U> U fold(std::function<U(T, U, U)> f, U z, 
		Tree<T>* tree) {
	Branch<T>* branch = dynamic_cast<Branch<T>*>(tree);
	if (branch) {
		return f(branch.value, fold(f, z, branch.left), 
				fold(f, z, branch.right));
	}
	return z;
}

template<typename T> Tree<T>* intTree_(T value, Tree<T>* tree) {
	for (T i = value; i > 0; --i) {
		tree = insert(i, tree);
	}
	return tree;
}

template<typename T> Tree<T>* intTree(T value) {
	//assert(value > 0);
	return intTree_(value, empty<T>());
}

int main() {
	// your code goes here
	
	Tree<int>* tree = intTree<int>(3);		
	
	return 0;
}