#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct Texture {
    Texture(const string& filename);
    Texture(const Texture& other);
    ~Texture();
};


Texture::Texture(const string&)
{
    // ....
    std::cout << "Texture::Texture() for " << this << std::endl;
}

Texture::Texture(const Texture&)
{
    std::cout << "Texture::Texture(const Texture&) for " << this << std::endl;
}

Texture::~Texture()
{
    std::cout << "Texture::~Texture() for " << this << std::endl;
}


void setEnvCube(const std::shared_ptr<Texture>& front, const     
    std::shared_ptr<Texture>& back, const std::shared_ptr<Texture>& left, const 
    std::shared_ptr<Texture>& right, const std::shared_ptr<Texture>& top, const 
    std::shared_ptr<Texture>& bottom)
{
    std::shared_ptr<Texture> envFront_ = front;
    std::shared_ptr<Texture> envBack_ = back;
    std::shared_ptr<Texture> envLeft_ = left;
    std::shared_ptr<Texture> envRight_ = right;
    std::shared_ptr<Texture> envTop_ = top;
    std::shared_ptr<Texture> envBot_ = bottom;
}

int main() 
{
    std::shared_ptr<Texture> up(std::make_shared<Texture>("textures/lakeup.png")),
                             down(std::make_shared<Texture>("textures/lakedn.png")),
                             left(std::make_shared<Texture>("textures/lakelf.png")),
                             right(std::make_shared<Texture>("textures/lakert.png")),
                             back(std::make_shared<Texture>("textures/lakebk.png")),
                             front(std::make_shared<Texture>("textures/lakeft.png"));
    
    setEnvCube(front, back, left, right, up, down);
}