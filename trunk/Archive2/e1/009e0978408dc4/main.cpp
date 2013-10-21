#include <memory>
#include <vector>
#include <cassert>

namespace std
{
    template <typename T, typename... Args>
        unique_ptr<T> make_unique(Args&&... args) {
            return unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
}

struct TreeElem {
    virtual ~TreeElem() {}
    virtual std::unique_ptr<TreeElem> clone() const= 0;
};

struct Leaf : public TreeElem {
    Leaf(int value) : _value(value) {}
    virtual std::unique_ptr<TreeElem> clone() const { 
        return std::make_unique<Leaf>(_value); 
    }
    int _value;
};

struct Node : public TreeElem {
    std::vector<std::unique_ptr<TreeElem>> _children;

    virtual std::unique_ptr<TreeElem> clone() const { 
        auto cloned = std::make_unique<Node>(); 
        for (auto& c : _children)
            cloned->addChild(c->clone());
        return std::move(cloned);
    }
    TreeElem *addChild(std::unique_ptr<TreeElem>&& rawNode)
    {
        _children.push_back(std::move(rawNode));
        return static_cast<TreeElem*>(_children.back().get());
    }
    Node *addChild()
    {
        _children.emplace_back(std::make_unique<Node>());
        return static_cast<Node*>(_children.back().get());
    }
    TreeElem *addChild(int value)
    {
        _children.emplace_back(std::make_unique<Leaf>(value));
        return _children.back().get();
    }

    template <typename F>
        bool traverse(F callback, int level = 1) const
        {
            for (auto& c : _children)
            {
                Node const* sub = dynamic_cast<Node const*>(c.get());
                if (sub != nullptr)
                {
                    if (!sub->traverse(callback, level + 1))
                        return false;
                }
                else
                {
                    Leaf const* leaf = dynamic_cast<Leaf const*>(c.get());
                    assert(leaf);
                    if (!callback(*leaf, level))
                        return false;
                }
            }

            return true;
        }
};

#include <iostream>

int main()
{
    Node branch1;
    branch1.addChild(2);
    branch1.addChild(1);

    auto subbranch = branch1.addChild();
    subbranch->addChild(42);
    subbranch->addChild(-42);

    Node tree;
    tree.addChild(branch1.clone());
    tree.addChild(0);
    tree.addChild(branch1.clone());

    // now, for some way to traverse...
    int previousLevel = 0;
    tree.traverse([&previousLevel] (Leaf const& leaf, int level) mutable {
            for (;level > previousLevel;++previousLevel)
                std::cout << "{ ";
            for (;level < previousLevel;--previousLevel)
                std::cout << "} ";
            std::cout << leaf._value << " ";
            return true;
        });

    while (previousLevel--)
        std::cout << "} ";
}
