#include <initializer_list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <string>

class Options {
private:
    using setting = std::pair<std::string,std::string>;
    friend class Parser;
    std::set<setting> options;
    std::string header, usage;
public:
    Options(std::initializer_list<setting> init): options(init), header("Allowed Options") {}
    friend std::ostream& operator<<(std::ostream& out, const Options& op) {
        out << op.header << ":\n";
        if(!op.usage.empty())
            out << '\n' << op.usage << '\n';
        for(auto& i : op.options) {
            out << std::left << '\t' << std::setw(30) << i.first << i.second << '\n';
        }
        return out;
    }
};

class Base {
public:
    virtual ~Base() {}
    virtual bool enabled() const = 0;
};

template<typename T>
class Value : public Base {
private:
    T* value;
public:
    virtual bool enabled() const {
        return true;
    }
    Value(const T& var): value(&var) {}
    Value(): value(nullptr) {}
};

template<>
class Value<void> : public Base {
public:
    virtual bool enabled() const {
        return false;
    }
};

class Parser {
private:
    const Options* opt;
    std::vector<std::pair<std::string,Base*>> values;
    std::vector<std::pair<std::string,std::function<void()>>> functions;
    std::vector<std::string> args;
public:
    Parser(): opt(nullptr) {}
    Parser(const Options& op): opt(&op) {}
    void addValue(const std::string& arg, Base&& base) {
        values.push_back(std::make_pair(arg,&base));
    }
    void addFunction(const std::string& arg, std::function<void()> func) {
        functions.push_back(std::make_pair(arg,func));
    }
    void parse(int argc, char* argv[]) {
        for(int i = 0; i < argc; ++i) {
            args.push_back(std::string(argv[i]));
            for(auto& value : values) {
                //Found value
                if(value.first == args[i]) {
                    if(value.second->enabled()) {
                        //shit..
                    }
                }
            }
        }
    }
};

int main() {
    Options op = {
        {"--help","Prints this.."},
        {"--prints","Prints something else"}
    };
    Parser parser(op);
    parser.addValue("--help",Value<void>());
}