#include <boost/variant.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include <iostream>

////// STUBS
namespace Model { namespace ClientModel { 
     struct cClientVerticesObject : boost::noncopyable {};
     struct cRawClientObject      : boost::noncopyable {};
     struct cFunkyClientObject    : boost::noncopyable {};

} }
namespace Controller { 
    namespace QtOpenGL { 
        struct cQOpenGLContext : boost::noncopyable {};
    } 
    struct cConsoleContext : boost::noncopyable {};
    struct cDevNullContext : boost::noncopyable {};

}

namespace traits
{
    template <typename T> struct supports_console_ctx : boost::mpl::false_ {};
    template <> 
        struct supports_console_ctx<Model::ClientModel::cFunkyClientObject> : boost::mpl::true_ {};
}
////// END STUBS

/////////////////////////////////////////////////////////////////////
// Why not **just** make it a polymorphic functor?
//
// You can make it use an extension point if you're so inclined:
// (note the use of Enable to make it Sfinae-friendly)
namespace UserTypeHooks
{
    template <typename ClientObject, typename Context, typename Enable = void> 
    struct RenderClientObjectsImpl
    {
        void static call(ClientObject const& clientObject, Context const& context)
        {
            // static_assert(false, "not implemented");
            // throw?
            std::cout << "NOT IMPLEMENTED:\t" << __PRETTY_FUNCTION__ << "\n";
        }
    };

    template <typename ClientObject> 
        struct RenderClientObjectsImpl<ClientObject, Controller::QtOpenGL::cQOpenGLContext>
    {
        void static call(ClientObject const& clientObject, Controller::QtOpenGL::cQOpenGLContext const& context)
        {
            std::cout << "cQOpenGLContext:\t" << typeid(ClientObject).name() << "\n";
        }
    };

    template <typename ClientObject> 
        struct RenderClientObjectsImpl<ClientObject, Controller::cDevNullContext>
    {
        void static call(ClientObject const& clientObject, Controller::cDevNullContext const& context)
        {
            std::cout << "devnull:\t\t" << typeid(ClientObject).name() << "\n";
        }
    };
}

struct RenderClientObjects
{
    typedef void result_type;

    template <typename ClientObject, typename Context> 
        void operator()(ClientObject const& clientObject, Context const& context) const
        {
            return UserTypeHooks::RenderClientObjectsImpl<ClientObject, Context>::call(clientObject, context);
        }
};

/////////////////////////////////////////////////////////////////////
// Demonstrating the user-defined extension point mechanics:
namespace UserTypeHooks
{
    template <typename ClientObject>
    struct RenderClientObjectsImpl<ClientObject, Controller::cConsoleContext,
        typename boost::enable_if<traits::supports_console_ctx<ClientObject> >::type>
    {
        void static call(
                ClientObject const& clientObject,
                Controller::cConsoleContext const& context)
        {
            std::cout << "This type has cConsoleContext support due to the supports_console_ctx trait! " << typeid(ClientObject).name() << "\n";
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

typedef boost::variant<
        Controller::QtOpenGL::cQOpenGLContext&,
        Controller::cConsoleContext&,
        Controller::cDevNullContext&
    > AnyContext;

void variant_multimethod(ClientObjectVariant const& o, AnyContext const& ctx)
{
    boost::apply_visitor(RenderClientObjects(), o, ctx);
}

int main()
{
    Model::ClientModel::cClientVerticesObject vertices;
    Model::ClientModel::cRawClientObject      raw;
    Model::ClientModel::cFunkyClientObject    funky;

    Controller::QtOpenGL::cQOpenGLContext glContext;
    Controller::cConsoleContext           console;
    Controller::cDevNullContext           devnull;

    RenderClientObjects multimethod;

    std::cout << "// Fully static dispatch:\n";
    std::cout << "//\n";
    multimethod(vertices, glContext);
    multimethod(vertices, console);
    multimethod(vertices, devnull);
    //
    multimethod(raw, glContext);
    multimethod(raw, console);
    multimethod(raw, devnull);
    //
    multimethod(funky, glContext);
    multimethod(funky, console);
    multimethod(funky, devnull);

    std::cout << "\n";
    std::cout << "// Runtime dispatch:\n";
    std::cout << "//\n";
    variant_multimethod(vertices, glContext);
    variant_multimethod(vertices, console);
    variant_multimethod(vertices, devnull);
    //
    variant_multimethod(raw, glContext);
    variant_multimethod(raw, console);
    variant_multimethod(raw, devnull);
    //
    variant_multimethod(funky, glContext);
    variant_multimethod(funky, console);
    variant_multimethod(funky, devnull);
}

