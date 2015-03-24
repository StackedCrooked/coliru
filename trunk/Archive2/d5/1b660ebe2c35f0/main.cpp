#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
class Requirement {
    public:
		bool empty;
		std::string level;
		std::string description;
		std::string label;
		std::vector <Requirement> children;
		Requirement * parent;
		Requirement(std::string l, std::string d, std::string la, Requirement * p);
		void Display(int depth);
		void JSON(int depth, std::ofstream &outfile);
};

void display(const int depth, const boost::property_tree::ptree& tree, Requirement* cur_requirement,
             std::vector<Requirement>& requirements)
{
    //unsigned int count;
    std::string label, level, description;
    //boost::property_tree::ptree const& kids = tree.get_child("");
    auto& kids = tree.get_child("");
    //bool godown = false;
    for (const auto& v : kids) { // v is of type ptree::value_type
        std::cout << std::string("").assign(depth + 1, '#') << " ";
        std::string nodestr = tree.get<std::string>(v.first);
        // std::cout << v.first << " = " << nodestr << std::endl;
        if (v.first == "label") {
            label = nodestr;
            std::cout << "lbl: " << label << std::endl;
        } else if (v.first == "level") {
            // std::cout << "LABEL!";
            level = nodestr;
            std::cout << "lvl: " << level << std::endl;
        } else if (v.first == "description") {
            description = nodestr;
            std::cout << "dsc: " << description << std::endl;
        } else if (v.first == "children") { // going down, store stuff first
            if (depth == 0) { // zero depth
                std::cout << "zero depth...";
                requirements.emplace_back(level, description, label, cur_requirement);
                cur_requirement = &requirements.back();
            } else { // one or higher depth
                std::cout << "at depth " << depth << "..." << std::flush;
                cur_requirement->children.emplace_back(level, description, label, cur_requirement->parent);
                cur_requirement = &cur_requirement->children.back();
            }
            std::cout << "going down" << std::endl;
            // cur_requirement = &cur_requirement->children.back();
            display(depth + 1, v.second, cur_requirement, requirements);
        } else if (v.first == "") {
            std::cout << "empty v.first ... level: " << level << std::endl;
            if (depth == 0) { // zero depth
                std::cout << "store at zero depth...";
                requirements.emplace_back(level, description, label, cur_requirement);
                cur_requirement = &requirements.back();
            } else { // one or higher depth
                std::cout << "store at depth " << depth << " : " << level << "--" << description << std::flush;
                cur_requirement->children.emplace_back(level, description, label, cur_requirement->parent);
                // cur_requirement = &cur_requirement->children.back();
            }
            std::cout << " going to next " << std::endl;
            // cur_requirement = &cur_requirement->children.back();
            display(depth, v.second, cur_requirement, requirements);
        } else {
            std::cout << "what else..." << std::endl;
        }
        // v.first is the name of the child
        // v.second is the child tree
    }
}

int main(int argc, char* argv[])
{
    std::vector<Requirement> requirements;
    requirements.reserve(256);
    Requirement* cur_requirement = nullptr;
    std::string name;
    std::string prefix;
    std::string filename;
    filename = argv[1];
    std::vector<std::string> filesplit;
    boost::split(filesplit, filename, boost::is_any_of("."));
    name = filesplit[0];
    boost::replace_all(name, "_", " ");
    prefix = filesplit[1];
    std::cout << "name: " << name << " prefix: " << prefix << std::endl << std::endl;
    if (argc>1) try {
        std::ifstream ss(argv[1]);
        //	std::stringstream ss;
        // ss << "{ \"root\": { \"values\": [1, 2, 3, 4, 5 ] } }";

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        display(0, pt, cur_requirement, requirements);
        std::cout << std::endl << std::endl;
        for (Requirement req : requirements) {
            req.Display(0);
        }

        return EXIT_SUCCESS;
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}
