#include <memory>
#include <iostream>
#include <vector>
#include <string>

class JBoss {
public:
    const std::vector<std::string>& GetUsers() {
        return users;
    }
    void AddUser(const std::string& name) {
        users.push_back(name);
    }
private:
    std::vector<std::string> users;
};

int main () {
    auto jboss = std::make_shared<JBoss>();
    jboss->AddUser("Rob");
    auto people = jboss->GetUsers();
    for (const auto p : people) {
        std::cout << p << " is supamadmad" << std::endl;
    }
}
