#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

template <typename Tree, typename Out, typename T = std::string>
Out enumerate_path(Tree const& pt, typename Tree::path_type path, Out out) {
    if (path.empty())
        return out;

    if (path.single()) {
        *out++ = pt.template get<T>(path);
    } else {
        auto head = path.reduce();
        for (auto& child : pt)
            if (child.first == head)
                out = enumerate_path(child.second, path, out);
    }
    
    return out;
}

int main() {
    using namespace boost::property_tree;

    ptree pt;
    read_xml(std::cin, pt);

    enumerate_path(pt, "foo.bar.item.link",
            std::ostream_iterator<std::string>(std::cout, "\n"));
}
