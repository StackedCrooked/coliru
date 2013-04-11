#include <gears/any.hpp>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <functional>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>


namespace detail {
struct ArgNotFound : public std::logic_error {
    ArgNotFound(const std::string& message): std::logic_error(message) {}
};

template<typename T>
T lexical_cast(const std::string& str) {
    std::stringstream ss(str);
    T result;
    if((ss >> result).fail() || !(ss >> std::ws).eof())
        throw std::bad_cast();
    return result;
}

template<typename Container, typename T>
auto find(const Container& container, const T& value) -> decltype(std::begin(container)) {
    auto first = std::begin(container);
    auto last = std::end(container);
    for(; first != last; ++first)
        if(*first == value)
            return first;

    return last;
}
template<typename InputIt>
InputIt next(InputIt it) {
    InputIt i = it;
    ++i;
    return i;
}
} //detail

class Parser {
private:
    std::unordered_map<std::string,std::tuple<std::string,gears::Any,bool,std::function<void()>>> options;
    std::vector<std::string> args;
    std::vector<std::pair<std::string,std::string>> descriptions;
    std::string header, usage, footer;

    void checkRequiredArgs() const {
        auto it = std::begin(args);
        for(auto& i : options) {
            if(std::get<2>(i.second)) {
                it = detail::find(args,i.first);
                if(it != args.end())
                    continue; //found
                else
                    throw detail::ArgNotFound(i.first + " not found... ");
            }
        }
    }

public:
    void setUsage(const std::string& str) {
        usage = str;
    }
    void setFooter(const std::string& str) {
        footer = str;
    }
    void setHeader(const std::string& str) {
        header = str;
    }

    template<typename T>
    void add(const std::string& arg, const std::string& desc, const T& def, bool req = false) {
        options[arg] = std::make_tuple(desc,def,req,std::function<void()>());
    }

    //Adds function to bind to a command line argument
    void addFunction(const std::string& arg, const std::string& desc, const std::function<void()> f) {
        options[arg] = std::make_tuple(desc,gears::Any(),false,f);
    }

    //Allows you to get the next command line argument and executes a binded function.
    //Default variable required.. cause fuck.
    template<typename T>
    void addFunction(const std::string& arg, const std::string& desc, const T& def, const std::function<void()> func, bool req = false) {
        options[arg] = std::make_tuple(desc,def,req,func);
    }

    void addDescription(const std::string& reqarg, const std::string& desc) {
        descriptions.push_back(std::make_pair(reqarg,desc));
    }

    void clearDescriptions() {
        descriptions.clear();
    }

    std::vector<std::string> getArgs() const {
        return args;
    }

    void parse(int argc, char* argv[]) {
        for(int i = 0; i < argc; ++i)
            args.push_back(std::string(argv[i]));

        checkRequiredArgs();

        for(auto it = args.begin(); it != args.end(); ++it) {
            bool found = options.find(*it) != options.end();
            if(found) {
                //Function
                if(!std::get<1>(options[*it])) { //If Any isn't null
                    if(std::get<3>(options[*it])) //valid function
                        std::get<3>(options[*it])(); //call it
                }
                else {
                    //Value
                    auto next_it = detail::next(it);
                    if(next_it != args.end()) {
                        std::get<1>(options[*it]) = *(next_it);
                    }
                    //If it also contains a function
                    if(std::get<3>(options[*it]))
                        std::get<3>(options[*it])(); //Call it
                    //Increment
                    ++it;
                }
            }
        }
    }

    template<typename T>
    T get(const std::string& arg) {
        bool found = options.find(arg) != options.end();
        if(!found) 
            throw detail::ArgNotFound(arg + " not found..");
        //If it's already that value
        if(std::get<1>(options[arg]).is<T>())
            return std::get<1>(options[arg]).as<T>();
        //If it's the stored std::string from parsing
        else if(std::get<1>(options[arg]).is<std::string>())
            return detail::lexical_cast<T>(std::get<1>(options[arg]).as<std::string>());
        //If it somehow managed to not throw or cast, it'll just return the defaulted state
        return T();
    }

    friend std::ostream& operator<<(std::ostream& out, const Parser& p) {
        if(!p.header.empty())
            out << p.header << ":\n";
        if(!p.usage.empty())
            out << "Usage: " << p.usage << '\n';
        for(auto& option : p.options)
            out << std::left << '\t' << std::setw(35) << option.first << std::get<0>(option.second) << '\n';
        if(!p.descriptions.empty()) {
            out << "Operands: \n";
            for(auto& desc : p.descriptions) {
                out << std::left << '\t' << std::setw(35) << desc.first << desc.second << '\n';
            }
        }
        if(!p.footer.empty())
            out << p.footer << '\n';
        return out;
    }
};

#include <cstdlib>

void add(int a, int b) {
    std::cout << (a+b);
}

void subtract(int a, int b) {
    std::cout << (a-b);
}

void multiply(int a, int b) {
    std::cout << (a*b);
}

void divide(int a, int b) {
    std::cout << ((float)a/b);
}

int main(int argc, char* argv[]) {
    Parser parser;
    std::vector<std::function<void(int,int)>> functions = {add,subtract,multiply,divide};
    size_t pos = 0;
    parser.setUsage("optionsbeta [--operation=--add] [--left] [arg1] [--right] [arg2]");
    parser.setHeader("Allowed Options");
    parser.setFooter("This program is being made to test how easy it is to parse compile line arguments");
    parser.addFunction("--help","Displays this message",[&]{std::cout << parser; std::exit(0);});
    parser.addFunction("--add","Adds the two together",[&]{pos=0;});
    parser.addFunction("--subtract","Subtracts the two together",[&]{pos=1;});
    parser.addFunction("--multiply","Multiplies the two together",[&]{pos=2;});
    parser.addFunction("--divide","Divides the two together",[&]{pos=3;});
    parser.addDescription("arg1","The left hand side being operated on");
    parser.addDescription("arg2","The right hand side being operated on");
    parser.add<int>("--left","Left operand",0);
    parser.add<int>("--right","Right operand",0);
    parser.parse(argc,argv);
    int a = parser.get<int>("--left");
    int b = parser.get<int>("--right");
    functions[pos](a,b);
}