struct Model { /* blah blah */ };

class ResourceCache {
    struct base { virtual ~base() {} };
    template<typename T> struct derived {
        T resource;
        derived(T t)
            : t(std::move(resource)) 
        {}
    };
    std::unordered_map<std::string, std::unique_ptr<base>> models;
public:
    template<typename T> T* Get(std::string name) {
        if (models.find(name) != models.end()) {
            if (auto p = dynamic_cast<derived<T>*>(models[name].get())) {
                return &p->resource;
            }
        }
        return nullptr;
    }
    template<typename T, typename... Args> T* Get(std::string name, Params&&... args) {
        auto p = Get(name); if (p) return p;
        return &(models[name] = make_unique<derived<T>>(T::Load(std::forward<Params>(args)...)))->resource;
    }
    void Unload(std::string name) {
        models.erase(name);
    }
};

