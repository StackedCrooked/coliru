#include <memory>
#include <string>

struct Shader
{
    Shader(const std::string&) {}
};

int main()
{
    std::string _name = "Shader";
    std::unique_ptr<Shader> s = make_unique<Shader>(_name);
}
