#include <utility>

template <typename func>
class Entry{
public:
    void* Address = (void*)(void(*)())[]{};

    template <typename... Args>
    auto operator()(Args&&... args)
     -> decltype( ((typename std::remove_pointer<func>::type*) Address)(std::forward<Args>(args)...) ) {
        return    ((typename std::remove_pointer<func>::type*) Address)(std::forward<Args>(args)...);
    }
};

int main()
{
    Entry<void(*)()>()();
    Entry<void   ()>()();
}