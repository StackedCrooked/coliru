#include <typeinfo>
#include <boost/type_traits.hpp>
#include <iostream>

////// STUBS
struct move_only {  // apparently boost::noncopyable prohibits move too
    move_only(move_only const&) = delete;
    move_only(move_only&&) = default;
    move_only() = default;
};

namespace Model { namespace ClientModel { 
     struct cClientVerticesObject : move_only {};
     struct cRawClientObject      : move_only {};
     struct cFunkyClientObject    : move_only {};
} }
namespace Controller { 
    namespace QtOpenGL { 
        struct cQOpenGLContext : move_only {};
    } 
    struct cConsoleContext : move_only {};
    struct cDevNullContext : move_only {};
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
// Added: Dynamic interface
//
// Making this a bit more complex than you probably need, but hey, assuming the
// worst:
#include <memory>

struct IPolymorphicRenderable
{
    // you likely require only one of these, and it might not need to be
    // virtual
    virtual void render(Controller::QtOpenGL::cQOpenGLContext& ctx) = 0;
    virtual void render(Controller::cConsoleContext& ctx) = 0;
    virtual void render(Controller::cDevNullContext& ctx) = 0;
};

struct IClientObject : IPolymorphicRenderable
{
    template <typename T> IClientObject(T&& val) : _erased(new erasure<T>(std::forward<T>(val))) { }

    virtual void render(Controller::QtOpenGL::cQOpenGLContext& ctx) { return _erased->render(ctx); }
    virtual void render(Controller::cConsoleContext& ctx)           { return _erased->render(ctx); }
    virtual void render(Controller::cDevNullContext& ctx)           { return _erased->render(ctx); }

  private:
    template <typename T> struct erasure : IPolymorphicRenderable
    {
        erasure(T val) : _val(std::move(val)) { }

        void render(Controller::QtOpenGL::cQOpenGLContext& ctx) { return RenderClientObjects()(_val, ctx); }
        void render(Controller::cConsoleContext& ctx)           { return RenderClientObjects()(_val, ctx); }
        void render(Controller::cDevNullContext& ctx)           { return RenderClientObjects()(_val, ctx); }

        T _val;
    };

    std::unique_ptr<IPolymorphicRenderable> _erased;
};

int main()
{
    IClientObject vertices(Model::ClientModel::cClientVerticesObject {});
    IClientObject raw     (Model::ClientModel::cRawClientObject      {});
    IClientObject funky   (Model::ClientModel::cFunkyClientObject    {});

    Controller::QtOpenGL::cQOpenGLContext glContext;
    Controller::cConsoleContext           console;
    Controller::cDevNullContext           devnull;

    std::cout << "// Fully virtual dispatch\n";
    std::cout << "//\n";
    vertices.render(glContext);
    vertices.render(console);
    vertices.render(devnull);
    //
    raw.render(glContext);
    raw.render(console);
    raw.render(devnull);
    //
    funky.render(glContext);
    funky.render(console);
    funky.render(devnull);
}
