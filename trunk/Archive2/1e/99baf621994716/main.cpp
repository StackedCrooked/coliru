#define BOOST_SPIRIT_DEBUG
#include <boost/property_tree/ptree.hpp>
#include <memory>
#include <iostream>
#include <list>

struct ITreeNode {
    std::string Name() const { return _name; }
    std::list<ITreeNode *> const &Children() const { return _children; }

    ITreeNode(std::string name = "", std::list<ITreeNode*> const& children = {})
        : _name(std::move(name)),
          _children(children)
    {
    }

    ITreeNode(ITreeNode const&)            = delete;
    ITreeNode& operator=(ITreeNode const&) = delete;

    ~ITreeNode() {
        for (auto* c : _children)
            delete c; // TODO make depthfirst deletion using iteration instead
                      // of breadth-first using recursion to avoid
                      // stack-overflow on large trees
    }
  private:
    std::string _name;
    std::list<ITreeNode *> _children;
};

using boost::property_tree::ptree;

namespace demo {
    ptree insertProjectNode(ITreeNode const& node);

    ptree insertProjectNode(ITreeNode const& node) {
        ptree current;

        for (auto const* child : node.Children())
            if (child) 
                current.add_child(child->Name(), insertProjectNode(*child));

        return current;
    }
}

#include <boost/property_tree/xml_parser.hpp>

int main() {

    ITreeNode const source = { "a", {
        new ITreeNode { "ab", {
            new ITreeNode { "ab0" },
            new ITreeNode { "ab1" },
            new ITreeNode { "ab2" },
        } },
        new ITreeNode { "ac", {
            new ITreeNode { "ac0" },
        } },
        new ITreeNode { "ad", {
            new ITreeNode { "ad0" },
            new ITreeNode { "ad1" },
            new ITreeNode { "ad2" },
            new ITreeNode { "ad3" },
        } },
    } };

    ptree root;
    root.add_child(source.Name(), demo::insertProjectNode(source));

    boost::property_tree::write_xml(std::cout, root,
            boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
}
