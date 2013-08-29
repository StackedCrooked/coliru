#include <functional>

template <typename TValue, typename TPred = std::less<TValue> >
class BinarySearchTree {

    struct TNode {
		TValue value;
		TNode *pLeft;
		TNode *pRight;
	};

public:

	BinarySearchTree();
	BinarySearchTree(BinarySearchTree<TValue, TPred> const &tree);
	BinarySearchTree<TValue, TPred> &operator=(BinarySearchTree<TValue, TPred> const &tree);
	~BinarySearchTree();

	bool Insert(TValue const &value); // returns false if already contained

	template <typename TVisitor> void VisitPreOrder (TVisitor visitor) const;
	template <typename TVisitor> void VisitInOrder  (TVisitor visitor) const;
	template <typename TVisitor> void VisitPostOrder(TVisitor visitor) const;

private:
	TNode *pRoot;

	TNode * m_MakeNode (TValue Data);
	bool m_Insert(TValue const &value, TNode *& pRoot);
	void m_Flush(TNode * & pRoot);
	template <typename TVisitor> void m_PreOrder (TVisitor visitor, TNode const * const pRoot) const;
	template <typename TVisitor> void m_InOrder  (TVisitor visitor, TNode const * const pRoot) const;
	template <typename TVisitor> void m_PostOrder(TVisitor visitor, TNode const * const pRoot) const;
};

// CTor
template <typename TValue, typename TPred>
BinarySearchTree<TValue, TPred>::BinarySearchTree() : pRoot(0) {}

template <typename TValue, typename TPred>
BinarySearchTree<TValue, TPred>::BinarySearchTree(BinarySearchTree<TValue, TPred> const &tree) {
	tree.VisitInOrder(Insert);
}

template <typename TValue, typename TPred>
BinarySearchTree<TValue, TPred> &BinarySearchTree<TValue, TPred>::operator=(BinarySearchTree<TValue, TPred> const &tree) {
	if (this != &tree) {
		tree.VisitInOrder(
            std::bind(&BinarySearchTree::Insert, this, std::placeholders::_1));
	}
	return *this;
}

// DTor
template <typename TValue, typename TPred>
BinarySearchTree<TValue, TPred>::~BinarySearchTree() {
	m_Flush(pRoot);
}

// Member methods
template <typename TValue, typename TPred>
bool BinarySearchTree<TValue, TPred>::Insert(TValue const &value) {
	return m_Insert(value, pRoot);
}

template <typename TValue, typename TPred>
template <typename TVisitor>
void BinarySearchTree<TValue, TPred>::VisitPreOrder(TVisitor visitor) const {
	m_PreOrder(visitor, pRoot);
}

template <typename TValue, typename TPred>
template <typename TVisitor>
void BinarySearchTree<TValue, TPred>::VisitInOrder(TVisitor visitor) const {
	m_InOrder(visitor, pRoot);
}

template <typename TValue, typename TPred>
template <typename TVisitor>
void BinarySearchTree<TValue, TPred>::VisitPostOrder(TVisitor visitor) const {
	m_PostOrder(visitor, pRoot);
}

// Private methods
template <typename TValue, typename TPred>
typename BinarySearchTree<TValue, TPred>::TNode * BinarySearchTree<TValue, TPred>::m_MakeNode(TValue Data) {
	TNode * const pNewNode = new TNode;
	pNewNode->value  = Data;
	pNewNode->pLeft  = 0;
	pNewNode->pRight = 0;
	return pNewNode;
}

template <typename TValue, typename TPred>
bool BinarySearchTree<TValue, TPred>::m_Insert(TValue const &value, TNode *& pRoot) {
	if (pRoot == 0) {
		pRoot = m_MakeNode(value);
		return true;
	}
	else if (value < pRoot->value) {
		m_Insert(value, pRoot->pLeft);
	}
	else if (value > pRoot->value) {
		m_Insert(value, pRoot->pRight);
	}
	return false;
}

template <typename TValue, typename TPred>
void BinarySearchTree<TValue, TPred>::m_Flush(TNode * & pRoot) {
	if (pRoot != 0) {
		m_Flush(pRoot->pLeft);
		m_Flush(pRoot->pRight);
		delete pRoot; pRoot = 0;
	}
}

template <typename TValue, typename TPred>
template <typename TVisitor>
void BinarySearchTree<TValue, TPred>::m_PreOrder(TVisitor visitor, TNode const * const pRoot) const {
	if (pRoot != 0) {
		visitor(pRoot->value);
		m_PreOrder(visitor, pRoot->pLeft);
		m_PreOrder(visitor, pRoot->pRight);
	}
}

template <typename TValue, typename TPred>
template <typename TVisitor>
void BinarySearchTree<TValue, TPred>::m_InOrder(TVisitor visitor, TNode const * const pRoot) const {
	if (pRoot != 0) {
		m_PreOrder(visitor, pRoot->pLeft);
		visitor(pRoot->value);
		m_PreOrder(visitor, pRoot->pRight);
	}
}

template <typename TValue, typename TPred>
template <typename TVisitor>
void BinarySearchTree<TValue, TPred>::m_PostOrder(TVisitor visitor, TNode const * const pRoot) const {
	if (pRoot != 0) {
		m_PreOrder(visitor, pRoot->pLeft);
		m_PreOrder(visitor, pRoot->pRight);
		visitor(pRoot->value);
	}
}

#include <iostream>

void Print(int const x) { std::cout << x << std::endl; }

int main() {
    BinarySearchTree<int> obj1, obj2, obj3;
    obj1.Insert(10);
    obj1.VisitInOrder(Print);
    obj3 = obj1;
    return 0;
}
