#include <memory>

struct IRenderer { virtual ~IRenderer() = default; };

struct GLRenderer : IRenderer {
    GLRenderer(int, std::string&&, double) {}
};

struct DXRenderer : IRenderer {
    template<typename... Ts>
    DXRenderer(bool, bool, Ts&&...) {}
};

template <typename D, typename... Ts> 
static std::unique_ptr<IRenderer> 
create(Ts&&... params)
{
    return std::unique_ptr<IRenderer>(new D(std::forward<Ts>(params)...));
}

int main()
{
    auto r = create<DXRenderer>(true, false, "Maybe", (struct FileNotFound*)nullptr);
    r = create<GLRenderer>(42, "surely", 3.14);
}