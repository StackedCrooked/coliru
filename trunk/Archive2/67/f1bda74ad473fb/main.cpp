#include <boost/variant.hpp>
#include <iostream>

////// STUBS
#define UNUSED(x) (void)(x)
namespace Model { namespace ClientModel { 
     struct cClientVerticesObject {};
     struct cRawClientObject      {};
     struct cFunkyClientObject    {};
} }
namespace Controller { namespace QtOpenGL { 
    typedef std::ostream cQOpenGLContext;
} }
////// END STUBS

typedef boost::variant<
        Model::ClientModel::cClientVerticesObject, 
        Model::ClientModel::cRawClientObject,
        Model::ClientModel::cFunkyClientObject
    > ClientObjectVariant;

struct RenderClientObjects : boost::static_visitor<void>
{
    RenderClientObjects(Controller::QtOpenGL::cQOpenGLContext* glContext) 
        : glContext(glContext) 
    { }

    void operator()(Model::ClientModel::cFunkyClientObject const& clientObject1, Model::ClientModel::cFunkyClientObject const& clientObject2) const
    {
        (*glContext) << "Both objects are Funky.\n";
    }

    template <typename ClientObject2> 
        void operator()(Model::ClientModel::cFunkyClientObject const& clientObject1, ClientObject2 const& clientObject2) const
        {
            (*glContext) << "Funky object involved (other is " << typeid(clientObject2).name() << ")\n";
        }

    template <typename ClientObject1> 
        void operator()(ClientObject1 const& clientObject1, Model::ClientModel::cFunkyClientObject const& clientObject2) const
        {
            (*this)(clientObject2, clientObject1); // delegate implementation, for example
        }

    // catch all:
    template <typename ClientObject1, typename ClientObject2> 
        void operator()(ClientObject1 const& clientObject1, ClientObject2 const& clientObject2) const
        {
            (*glContext) << __PRETTY_FUNCTION__ << "\n";
        }

  private: 
    Controller::QtOpenGL::cQOpenGLContext* glContext;
};

void variant_multimethd(Controller::QtOpenGL::cQOpenGLContext& ctx, ClientObjectVariant const& a, ClientObjectVariant const& b)
{
    RenderClientObjects multimethod(&ctx);
    boost::apply_visitor(multimethod, a, b);
}

int main()
{
    Controller::QtOpenGL::cQOpenGLContext glContext(std::cout.rdbuf());
    RenderClientObjects multimethod(&glContext);

    Model::ClientModel::cClientVerticesObject vertices;
    Model::ClientModel::cRawClientObject      raw;
    Model::ClientModel::cFunkyClientObject    funky;

    glContext << "// Fully static dispatch:\n";
    glContext << "//\n";
    multimethod(vertices, vertices);
    multimethod(vertices, raw);
    multimethod(vertices, funky);
    //
    multimethod(raw, vertices);
    multimethod(raw, raw);
    multimethod(raw, funky);
    //
    multimethod(funky, vertices);
    multimethod(funky, raw);
    multimethod(funky, funky);

    glContext << "\n";
    glContext << "// Runtime dispatch:\n";
    glContext << "//\n";
    variant_multimethd(glContext, vertices, vertices);
    variant_multimethd(glContext, vertices, raw);
    variant_multimethd(glContext, vertices, funky);
    //
    variant_multimethd(glContext, raw, vertices);
    variant_multimethd(glContext, raw, raw);
    variant_multimethd(glContext, raw, funky);
    //
    variant_multimethd(glContext, funky, vertices);
    variant_multimethd(glContext, funky, raw);
    variant_multimethd(glContext, funky, funky);
}
