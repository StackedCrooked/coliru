#include <iostream>


#include <string>
#include <map>
#include <unordered_map>
#include <list>

template <typename V>
class Trie;

template <typename V>
class TrieNode {
    friend class Trie<V>;
    typedef V value_type;
    char sub_key;
    TrieNode<V> *parent;
    std::map<char,TrieNode<V>*> children;
    V value;
    bool hasValue;
public:
    TrieNode() : sub_key(0), parent(nullptr), children() {}
    TrieNode(char skey, TrieNode<V> *p) : sub_key(skey), parent(p), children() {}
    void setKey(char k) {
        sub_key = k;
    }
    void setValue(V v) {
        value = v;
        hasValue = true;
    }
    void unsetValue() {
        hasValue = false;
    }
};
    
template <typename V>
class Trie {
    typedef V value_type;
    TrieNode<V> root;
    std::unordered_map<std::string, TrieNode<V>*> vHashTable;
    void scanSubtree(TrieNode<V> *proot, std::list<V> *matches) {
        std::list<TrieNode<V>*> scan_list;
        scan_list.push_back(proot);
        while (!scan_list.empty()) {
            TrieNode<V> *cur_node = scan_list.front();
            scan_list.pop_front();
            if (cur_node->hasValue) {
                matches->push_back(cur_node->value);
            }
            for (auto it = cur_node->children.begin();
                it != cur_node->children.end();
                ++it) {
                scan_list.push_back(it->second);
            }
        }
    }

    void removeRaw(TrieNode<V> *node) {
        TrieNode<V> *par_node = node->parent;
        while (par_node != &root) {
            int nb = node->children.size();
            if (!nb) {
                par_node->children.erase(node->sub_key);
                delete node;
            } else {
                break;
            }
            node = par_node;
            par_node = node->parent;
        }
    }

public:
    virtual ~Trie() {
        for (auto it = vHashTable.begin(); it != vHashTable.end(); ++it) {
            removeRaw(it->second);
        }
    }
    V& insert(std::string key, V value = V()) {
        TrieNode<V> *cur_node = &root;
        for(auto it = key.begin(); it != key.end(); ++it) {
            TrieNode<V>* n = nullptr;
            auto node_it = cur_node->children.find(*it);
            if (cur_node->children.end() == node_it) {
                n = new TrieNode<V>(*it, cur_node);
                cur_node->children.emplace(*it, n);
            } else {
                n = node_it->second;
            }
            cur_node = n;
        }
        if (!cur_node->hasValue) { 
            cur_node->setValue(value);
            vHashTable.emplace(key, cur_node);
        }
        return cur_node->value;
    }
    bool remove(std::string key) {
        auto it = vHashTable.find(key);
        TrieNode<V> *node = nullptr, *par_node = nullptr;
        if (vHashTable.end() == it) {
            return false;
        }
        node = it->second;
        node->unsetValue();
        removeRaw(node);
        vHashTable.erase(key);
        return true;
    }

    void keyMatch(std::string key, std::list<V> *matches) {
        TrieNode<V> *cur_node = &root;
        for (auto it = key.begin(); it != key.end(); ++it) {
            auto match_it = cur_node->children.find(*it);
            if (cur_node->children.end() == match_it) {
                return;
            }
            cur_node = match_it->second;
        }
        // Ended up in the node, must scan its subtree
        scanSubtree(cur_node, matches);
    }

    V& operator[](std::string key) {
        auto it = vHashTable.find(key);
        if (vHashTable.end() == it) {
            return insert(key);
        }
        return it->second->value;
    }
};


int main() {
    // your code goes here
	Trie<std::string> trie;
	trie.insert("test", "blob");
	trie.insert("telluric", "planet");
	trie.insert("teutonic", "german");
	trie.insert("testies", "blobies");
	std::list<std::string> matches;
	trie.keyMatch("tes", &matches);
	for (auto it = matches.begin(); it != matches.end(); ++it) {
		std::cout << *it << std::endl;
	}
	return 0;
}