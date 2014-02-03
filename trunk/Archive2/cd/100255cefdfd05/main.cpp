#include <boost/variant.hpp>
#include <boost/utility.hpp>
#include <iostream>

////// STUBS
namespace Model { namespace ClientModel { 
     struct cClientVerticesObject : boost::noncopyable {};
     struct cRawClientObject      : boost::noncopyable {};
     struct cFunkyClientObject    : boost::noncopyable {};
} }
namespace Controller { namespace QtOpenGL { 
    typedef std::ostream cQOpenGLContext;
} }
////// END STUBS

/////////////////////////////////////////////////////////////////////
// Why not **just** make it a polymorphic functor?
//
// You can make it use an extension point if you're so inclined:
// (note the use of Enable to make it Sfinae-friendly)
namespace UserTypeHooks
{
    template <typename ClientObject1, typename ClientObject2, typename Enable = void> 
    struct RenderClientObjectsImpl
    {
        void static call(
                Controller::QtOpenGL::cQOpenGLContext* glContext, 
                ClientObject1 const& clientObject1,
                ClientObject2 const& clientObject2)
        {
            (*glContext) << __PRETTY_FUNCTION__ << "\n";
        }
    };
}

struct RenderClientObjects
{
    typedef void result_type;

    RenderClientObjects(Controller::QtOpenGL::cQOpenGLContext* glContext) 
        : glContext(glContext) 
    { }

    //
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
            return UserTypeHooks::RenderClientObjectsImpl<ClientObject1, ClientObject2>::call(glContext, clientObject1, clientObject2);
        }

  private: 
    Controller::QtOpenGL::cQOpenGLContext* glContext;
};

/////////////////////////////////////////////////////////////////////
// Demonstrating the user-defined extension point mechanics:
namespace UserTypeHooks
{
    template <typename ClientObject>
    struct RenderClientObjectsImpl<ClientObject, ClientObject>
    {
        void static call(
                Controller::QtOpenGL::cQOpenGLContext* glContext, 
                ClientObject const& clientObject1,
                ClientObject const& clientObject2)
        {
            (*glContext) << "Both objects are of the same type (and not funky) : " << typeid(ClientObject).name() << "\n";
        }
    };
}

/////////////////////////////////////////////////////////////////////
// Variant dispatch (boost apply_visitor supports binary dispatch)
typedef boost::variant<
        Model::ClientModel::cClientVerticesObject&, 
        Model::ClientModel::cRawClientObject&,
        Model::ClientModel::cFunkyClientObject&
    > ClientObjectVariant;

void variant_multimethod(Controller::QtOpenGL::cQOpenGLContext& ctx, ClientObjectVariant const& a, ClientObjectVariant const& b)
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

    variant_multimethod(glContext, vertices, vertices);
    variant_multimethod(glContext, vertices, raw);
    variant_multimethod(glContext, vertices, funky);
    //
    variant_multimethod(glContext, raw, vertices);
    variant_multimethod(glContext, raw, raw);
    variant_multimethod(glContext, raw, funky);
    //
    variant_multimethod(glContext, funky, vertices);
    variant_multimethod(glContext, funky, raw);
    variant_multimethod(glContext, funky, funky);
}
