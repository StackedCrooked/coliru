#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>
#include <vector>
#include <set>
#include <initializer_list>

class CLBind {
private:
    using triple = std::pair<std::pair<std::string,std::string>,std::function<void()>>;
    std::string header;
    std::vector<triple> options;
    std::set<std::string> args;
public:
    CLBind(): header("Allowed Options") {}
    CLBind(std::initializer_list<triple> lol): header("Allowed Options"), options(lol) {}
    void parseCommandLine(int argc, char* argv[]) {
        for(int i = 0; i < argc; ++i) {
            args.insert(std::string(argv[i]));
        }
        for(auto& option : options) {
            if(args.find(option.first.first) != args.end())
                option.second();
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const CLBind& binder) {
        out << binder.header << ":\n";
        for(auto& option : binder.options) {
            out << std::left << '\t' << std::setw(30) << option.first.first << option.first.second << '\n';
        }
        return out;
    }
};

void print() {
    std::cout << "Printing stuff";
}

void otherstuff() {
    std::cout << "stuff..";
}

int main(int argc, char* argv[]) {
    CLBind op = {
        {{"--help","Displays this message"}, [&](){std::cout << op; std::exit(0);}},
        {{"--print","Prints stuff to the command line"},print},
        {{"--do-other-stuff","Does other stuff"},otherstuff}
    };
    op.parseCommandLine(argc,argv);
}
