template< typename Vert, typename Vert::Tn > // think T[n] e.g. MyVert::float[5]
struct VAHelper
{
    using AttrType = typename  std::remove_extent<Tn>::type;

    static constexpr unsigned int dim           = std::extent<Tn>::value;
    static constexpr unsigned int stride_bytes  = sizeof(Vert);
    static constexpr unsigned int offset_bytes  = offsetof(Vert, Tn);

    static bool
    connect_to( OpenGLShaderProgram::Attribute* gl_attribute )
    {
        if( gl_attribute == nullptr )
            return false;


        generic_glVertexAttribPointer<AttrType>(
            gl_attribute->attributeID,
            dim,
            stride_bytes,
            offset_bytes
            );

        glEnableVertexAttribArray( gl_attribute->attributeID );

        return true;
    }
}



// usage: 

class MainContentComponent   : public OpenGLAppComponent
{
   :
private:
    //==============================================================================
    struct Vertex
    {
        float _position[3];
        float normal[3];
        float colour[4];
        float texCoord[2];
    };

    //==============================================================================
    // This class just manages the attributes that the shaders use.
    struct Attributes
    {
        Attributes (OpenGLContext& openGLContext, OpenGLShaderProgram& shader)
        {
            position      = createAttribute (openGLContext, shader, "position");
            normal        = createAttribute (openGLContext, shader, "normal");
            sourceColour  = createAttribute (openGLContext, shader, "sourceColour");
            texureCoordIn = createAttribute (openGLContext, shader, "texureCoordIn");
        }

        void enable (OpenGLContext& openGLContext)
        {
            VAHelper<Vertex::_position>::connect_to( position );
:
:



