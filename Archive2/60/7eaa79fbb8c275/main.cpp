#include <iostream>
#include <string>
#include <memory>

class Texture
{
public:
    Texture(const std::string&)
    {
        std::cout << "Texture::Texture() for " << this << std::endl;
    }

    Texture(const Texture& other)
    {
        std::cout << "Texture::Texture(const Texture&) for " << this << std::endl;
    }

    ~Texture()
    {
        std::cout << "Texture::~Texture() for " << this << std::endl;
    }
};

int main(int argc, char *argv[])
{
    std::shared_ptr<Texture> up(std::make_shared<Texture>("textures/lakeup.png"));
    return 0;
}