#include <string>
#include <vector>
#include <algorithm>

using package_info = std::string;
using requirements = std::vector<package_info>;

struct package {
    package_info name;
    requirements dependencies;
};

using repository = std::vector<package>;

#include <iostream>

bool is_installed(const repository& repo, const package_info& pkg) {
    return std::find_if(repo.begin(), repo.end(), [&pkg](const package& p) { return pkg == p.name; }) != repo.end();
}

void handle_dependencies(const repository& global, repository& local, const requirements& deps) {
    for(auto&& dependency : deps) {
        if(not is_installed(local, dependency)) {
            auto it = std::find_if(global.begin(), global.end(), [&dependency](const package& pkg) { return pkg.name == dependency; });
            if(it == global.end()) {
                std::cout << "could not find package " << dependency << '\n';
                return;
            }
            std::cout << "installing dependency: " << dependency << '\n';
            std::cout << it->dependencies.size() << " inner dependencies found for dependency " << dependency << '\n';
            handle_dependencies(global, local, it->dependencies);
            std::cout << "successfully installed dependency: " << dependency << '\n';
            local.push_back(*it);
        }
        else {
            std::cout << "dependency " << dependency << " is already installed... skipping...\n";
        }
    }
}

void install(const repository& global, repository& local, const package& pkg) {
    std::cout << "installing package: " << pkg.name << '\n';
    auto it = std::find_if(global.begin(), global.end(), [&pkg](const package& p) { return pkg.name == p.name; });
    if(it == global.end()) {
        std::cout << "could not find package " << pkg.name << '\n';
        return;
    }
    std::cout << it->dependencies.size() << " dependencies found for package " << pkg.name << '\n';
    handle_dependencies(global, local, it->dependencies);
    local.push_back(pkg);
    std::cout << "successfully installed package: " << pkg.name << '\n';
}

int main() {
    repository global = {
        { "root", { "A", "B", "C" }},
        { "A", {}},
        { "B", { "D", "E" }},
        { "C", { "E" }},
        { "D", {}},
        { "E", {}}
    };

    repository local;
    install(global, local, global.front());
}
