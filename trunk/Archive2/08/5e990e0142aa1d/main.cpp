#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

class Requirement {
    public:
        bool empty;
        std::string level;
        std::string description;
        std::string label;
        Requirement const* parent;
        std::list <Requirement> children;

        Requirement(Requirement const* p);
        Requirement(std::string l, std::string d, std::string la, Requirement const* p); // unused

        void print(std::string indent = "");
        void print_json(std::ostream &os, std::string indent = "");
};

Requirement::Requirement(Requirement const* p) 
    : empty(false), parent(p)
{
}

Requirement::Requirement(std::string l, std::string d, std::string la,Requirement const* p) // unused
    : empty(false), 
      level(std::move(l)), description(std::move(d)), label(std::move(la)), parent(p)
{
}

void Requirement::print_json(std::ostream &os, std::string indent) {
    os  << "{";
    indent += '\t';

    os
         << "\n" << indent << "\"level\":\""       << level       << "\", "
         << "\n" << indent << "\"description\":\"" << description << "\"";

    if(label.length() > 1) {
        os << ",\n" << indent << "\"label\":\"" << label <<"\"";
    }

    if (!children.empty()) {
        os << ", \"children\":[\n";

        bool first = true;
        for(auto& child : children) {
            if (!first)
                os << ',';

            first=false;

            os << "\n" << indent;
            child.print_json(os, indent);
        }
        os << "]";
    }

    indent.resize(indent.size() - 1);
    os << "\n" << indent << "}";
}

void Requirement::print(std::string indent) {
    std::cout << indent << "level: " << level << " description:" << description << " label: " << label << std::endl;
    for (Requirement kid : children)
        kid.print(indent + '\t');
}

void parse_json(int depth, boost::property_tree::ptree const& tree, Requirement& cur)
{
    cur.label       = tree.get("label",       "");
    cur.level       = tree.get("level",       "");
    cur.description = tree.get("description", "");

    if (auto kids = tree.get_child_optional("children")) {
        for (auto& kid : *kids) {
            std::cout << "at depth " << depth << "... " << std::flush;

            cur.children.emplace_back(&cur);

            std::cout << "going down" << std::endl;
            parse_json(depth + 1, kid.second, cur.children.back());
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc>1) try {
        std::ifstream ss(argv[1]);

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);

        Requirement root(nullptr);
        parse_json(0, pt, root);

        std::cout << std::endl << std::endl;
        root.print("; debug: ");
        root.print_json(std::cout);
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
