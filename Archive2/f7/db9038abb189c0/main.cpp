#include <typeinfo>
#include <cstddef>

using namespace std;

template <typename T>
inline void generic_glVertexAttribPointer           (GLuint index, GLint dim, GLsizei stride, const GLvoid *offset) {
    static_assert( glconst4type<T>::value,  "Invalid type!" );
    glVertexAttribIPointer( index, size, glconst4type<T>::value,                 stride, pointer );
}

template <>
inline void generic_glVertexAttribPointer<float>    (GLuint index, GLint dim, GLsizei stride, const GLvoid *offset) {
    glVertexAttribPointer( index, size, glconst4type<float>::value, GL_FALSE,    stride, pointer );
}

template <>
inline void generic_glVertexAttribPointer<double>   (GLuint index, GLint dim, GLsizei stride, const GLvoid *offset) {
    glVertexAttribLPointer( index, size, glconst4type<double>::value,            stride, pointer );
}

template <typename T>
struct glconst4type
{
    static_assert( std::is_same<T, void>::value,  "Invalid type!" );
    static constexpr GLenum value = 0;
};

template <> struct glconst4type<unsigned char>  {static constexpr GLenum value = GL_UNSIGNED_BYTE;};
template <> struct glconst4type<signed char>    {static constexpr GLenum value = GL_BYTE;};
//template <> struct glconst4type<char>           {static constexpr GLenum value = Utils::is_char_signed ? GL_BYTE : GL_UNSIGNED_BYTE;};
template <> struct glconst4type<unsigned short> {static constexpr GLenum value = GL_UNSIGNED_SHORT;};
template <> struct glconst4type<signed short>   {static constexpr GLenum value = GL_SHORT;};
template <> struct glconst4type<unsigned int>   {static constexpr GLenum value = GL_UNSIGNED_INT;};
template <> struct glconst4type<signed int>     {static constexpr GLenum value = GL_INT;};
template <> struct glconst4type<float>          {static constexpr GLenum value = GL_FLOAT;};
template <> struct glconst4type<double>         {static constexpr GLenum value = GL_DOUBLE;};


template <typename Tn>
void process_vertex_attribute( 
    OpenGLContext&          openGLContext, 
    OpenGLShaderProgram&    shader, 
    std::string             name, 
    size_t                  stride_bytes, 
    size_t                  offset_bytes
    )
{
    // e.g. float[3] -> float and 3
    using Type = typename remove_extent<Tn>::type;
    static constexpr size_t  dim = extent<Tn>::value;

    GLint location = openGLContext.extensions.glGetAttribLocation(shader.getProgramID(), attributeName);
    if( location == -1 )
        return nullptr; // not found in shader
    
    OpenGLShaderProgram::Attribute gl_attribute =  new OpenGLShaderProgram::Attribute (shader, attributeName);
    
    if( gl_attribute == nullptr )
        return nullptr;
    
    generic_glVertexAttribPointer<Type>(
        attribNumber->attributeID,
        dim,
        vec_bytes,
        (const GLvoid *)offset_bytes
        );

    glEnableVertexAttribArray( attribNumber->attributeID );
}

#define ENABLE_VERTEX_ATTRIBUTE( openGLContext, shader, VertexStruct, attr_type, attr_name )  \
    process_vertex_attribute< VertexStruct::attr_type > ( \ 
                                        openGLContext, \
                                        shader, \
                                        name, \
                                        sizeof(VertexStruct) \
                                        )

void foo()
{
    struct V {  float pos[3];  int uv[2];  double color[4]; };
    
    ENABLE_VERTEX_ATTRIBUTE( openGLContext, shader, V, pos,   "position"  );
    ENABLE_VERTEX_ATTRIBUTE( openGLContext, shader, V, uv,    "uv"        );
    ENABLE_VERTEX_ATTRIBUTE( openGLContext, shader, V, color, "color"     );
}

int main()
{ }