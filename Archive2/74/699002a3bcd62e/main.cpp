#include <iostream>
#include <cstddef>
#include <stdint.h>
#include <array>

using GLsizei = std::size_t;
using GLuint = uint32_t;

using TBuilder = void(*)(GLsizei, GLuint *);

TBuilder glGenBuffers;
TBuilder glDeleteBuffers;

template<std::size_t N, TBuilder* TConstructor, TBuilder* TFreer>
struct OGLWrapper{
    std::array<GLuint, N> data;
    void gen(){
        (*TConstructor)(N, data.data());
    }
    ~OGLWrapper(){
        (*TFreer)(N, data.data());
    }
};

using VBO = OGLWrapper<1, &glGenBuffers, &glDeleteBuffers>;

void f(GLsizei, GLuint* ptr) {
    std::cout << "f!\n";
}
void g(GLsizei, GLuint* ptr) {
    std::cout << "g!\n";
}
int main() {
    glGenBuffers = f;
    glDeleteBuffers = g;
    VBO vbo;
    vbo.gen();
}