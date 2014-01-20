#include <iostream>
#include <memory>

//unique_ptr::reset(other) : deletes the previouls managed object and now manages other

class TreeElement {
    int value;//uninitialized
	std::unique_ptr<TreeElement> left{nullptr};//initializes left with nullptr for all constructors
	std::unique_ptr<TreeElement> right{nullptr};//initializes right with nullptr for all constructors
public:
	TreeElement(int value) : value{value} {//initializes the last uninitialized element with the specified value
		std::cout << '#' << value << '\n';
	}

	~TreeElement() {//the unique_ptrs dtors delete their elements
		std::cout << '~' << value << '\n';
	}

	bool find(int value) {
		if (this->value == value) {//found it
			return true;
		} else {
			bool truth{false};
			if (left != nullptr) {
				truth |= left->find(value);
			}
			if (right != nullptr) {
				truth |= right->find(value);
			}
			return truth;//left logical or right
		}
		return false;
	}

	void insert(int newValue) {
		if (newValue < value) {
			if (left != nullptr) {//descend
				left->insert(newValue);
			} else {
				left.reset(new TreeElement(newValue));
			}
		} else if (newValue > value) {
			if (right != nullptr) {//descend
				right->insert(newValue);
			} else {
				right.reset(new TreeElement(newValue));
			}
		} else {//newValue == value
			std::cout << value << " already present\n";
		}
	}

	bool isLeaf() {
		return left == nullptr && right == nullptr;
	}

	int min() {
		if (left.get() != nullptr) {//more smaller elements
			return left->min();
		} else {//no more smaller elements
			return value;
		}
	}

	bool removeNode(const int findValue) {
		if (findValue < value) {
			if (left->isLeaf()) {
				left.reset(nullptr);
			} else {
				left->removeNode(findValue);
			}
		} else if (findValue > value) {
			if (right->isLeaf()) {
				right.reset(nullptr);
			} else {
				right->removeNode(findValue);
			}
		} else {//findValue == findvalue
			if (left != nullptr && right != nullptr) {//two childs
				value = right->min();//get replacement
				//left remains unchanged
				if (right->isLeaf()) {//remove value from previous position in subtree
					right.reset(nullptr);//deletes right
				} else {
					right->removeNode(value);
				}
			} else if (left != nullptr && right == nullptr) {
				value = left->value;
				right.reset(left->right.get());//fill empty right node
				left.reset(left->left.get());//replace left, old left gets deleted
			} else if (left == nullptr && right != nullptr) {
				value = right->value;
				left.reset(right->left.get());//fill empty left node
				right.reset(right->right.get());//replace right, old right gets deleted
			} else {
				return true;//since there’re no childs, delete level above
			}
		}
		return false;//the element was not found
	}

	//friend: this global function can access the private members of this class
	friend std::ostream& operator<<(std::ostream & out, const TreeElement & elem);//print function
};

class SortedBinaryTree {
	std::unique_ptr<TreeElement> root{nullptr};//initializes root to nullptr for all ctors
public:
	SortedBinaryTree() {}
	~SortedBinaryTree() {//the unique pointers dtor deletes root, which in turn invokes its dtor
		std::cout << "Tree is being deleted\n";
	}

	void insertTreeElement(int newValue) {
		if (root == nullptr) {
			root.reset(new TreeElement(newValue));//populate root
		} else {
			root->insert(newValue);//forward insertion
		}
	}

	bool find(const int value) const {
        if (root == nullptr) {
            return false;
        } else {
		    return root->find(value);
        }
	}

	void deleteTreeElement(const int value) {
		if (root != nullptr) {
            if (root->removeNode(value)) {
			    root.reset(nullptr);
            }
		}
	}

	friend std::ostream& operator<<(std::ostream & out, const SortedBinaryTree & tree);//print function
};

std::ostream& operator<<(std::ostream & out, const SortedBinaryTree & tree) {
    out << ":";
    if (tree.root != nullptr) {
        out << *tree.root;
    } else {
        out << "{}";
    }
	return out;
}

std::ostream& operator<<(std::ostream & out, const TreeElement & elem) {
	out << elem.value;
	if (elem.left == nullptr && elem.right == nullptr) {
		return out;//no chidren, no braces
	}

	out << '{';
	if (elem.left != nullptr) {
		out << *elem.left;
	}
	out << ',';
	if (elem.right != nullptr) {
		out << *elem.right;
	}
	return out << "}";
}

int main() {
	SortedBinaryTree tree1;
	tree1.insertTreeElement(5);
	std::cout << tree1 << '\n';
	tree1.insertTreeElement(6);
	std::cout << tree1 << '\n';
	tree1.insertTreeElement(2);
	std::cout << tree1 << '\n';
	tree1.insertTreeElement(5);
	std::cout << tree1 << '\n';
	tree1.insertTreeElement(9);
	std::cout << tree1 << '\n';

	std::cout << std::boolalpha;
	std::cout << 3 << ':' << tree1.find(3) << ", ";
	std::cout << 5 << ':' << tree1.find(5) << '\n';

	tree1.deleteTreeElement(9);
	std::cout << tree1 << '\n';

	tree1.deleteTreeElement(5);
	std::cout << tree1 << '\n';
}
