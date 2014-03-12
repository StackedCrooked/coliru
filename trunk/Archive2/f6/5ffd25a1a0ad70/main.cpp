#include <iostream>

template <typename T> struct link {
   T data;
   link<T> *node[2]; // 0 means left, 1 means right
   
   explicit link(const T &data)
   : data(data)
   , node{nullptr, nullptr}
   {}
   
   explicit link()
   : node{nullptr, nullptr}
   {}
   
};

template <typename T> class Tree {  
    
    public:
    
    explicit Tree()
    : root(nullptr)
    {}
    
    bool insert(const T& data) {
        if (root == nullptr) {
            root = new link<T>(data);
            return true;
        }
            
        link<T> *temp = root, *prev = nullptr;
        int dir = 0;
        while (temp != nullptr) {
            if (data == temp->data)
                return false;
            dir = data > temp->data;
            prev = temp;
            temp = temp->node[dir];
        }
        
        prev->node[dir] = new link<T>(data);
        return true;
    }
    
    bool del(const T &data) {
        if (root == nullptr)
            return false;
            
        link<T> *temp = root, *prev = nullptr;
        int dir = -1;
        
        while (temp != nullptr && temp->data != data) {
            prev = temp;
            dir = data > temp->data;
            temp = temp->node[dir];                    
        }
        
        if (temp == nullptr) // not found
            return false;
            
        if (temp->node[0] != nullptr) {
            if (temp->node[1] != nullptr) {
                prev = temp;
                while (temp->node[0]->node[0] != nullptr)
                    temp = temp->node[0];
                prev->data = temp->node[0]->data;
                prev = temp->node[0];
                temp->node[0] = nullptr;
                temp = prev;
            }
            else (prev != nullptr ? prev->node[dir] : root) = temp->node[0];
        }
        else (prev != nullptr ? prev->node[dir] : root) = temp->node[1];
        
        delete temp;
        return true;
    }
    
    friend std::ostream& operator <<(std::ostream& oss, const Tree& btree) {
        const link<T> *ptr = btree.root;
        if (ptr != nullptr)
            btree.inorder(oss, btree.root);
        return oss;
    }
    
    private:
    link<T> *root;
    
    void inorder(std::ostream& oss, const link<T> *next) const {
        if (next != nullptr) {
            inorder(oss, next->node[0]);
            oss << next->data << ' ';
            inorder(oss, next->node[1]);
        }     
    }
};

int main() {
    Tree<double> btree; //{2.0, {nullptr, new link<double>{3, {new link<double>{2.5, {nullptr, nullptr}}, new link<double>{4, {nullptr, nullptr}}}}}};
    if (btree.insert(2))
        if (btree.insert(3))
            if (btree.insert(2.5))
                if (btree.insert(4))
                ;
    
    std::cout << btree << std::endl;
    btree.del(2.5);
    std::cout << btree << std::endl;
    return 0;
}