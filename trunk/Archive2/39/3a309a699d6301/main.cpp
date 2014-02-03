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
    Controller::QtOpenGL::cQOpenGLContext ctx(std::cout.rdbuf());
    RenderClientObjects multimethod(&ctx);

    Model::ClientModel::cClientVerticesObject vertices;
    Model::ClientModel::cRawClientObject      raw;
    Model::ClientModel::cFunkyClientObject    funky;

    // Fully static dispatch:
    //
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

    // Runtime dispatch:
    //
    variant_multimethd(ctx, vertices, vertices);
    variant_multimethd(ctx, vertices, raw);
    variant_multimethd(ctx, vertices, funky);
    //
    variant_multimethd(ctx, raw, vertices);
    variant_multimethd(ctx, raw, raw);
    variant_multimethd(ctx, raw, funky);
    //
    variant_multimethd(ctx, funky, vertices);
    variant_multimethd(ctx, funky, raw);
    variant_multimethd(ctx, funky, funky);
}
