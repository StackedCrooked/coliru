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
        (*TConstructor)(N, &data[0]);
    }
    ~OGLWrapper(){
        (*TFreer)(N, &data[0]);
    }
};

using VBO = OGLWrapper<1, &glGenBuffers, &glDeleteBuffers>;

int main() {
}