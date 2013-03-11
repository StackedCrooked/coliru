struct Model { /* blah blah */ };

class ResourceCache {
    std::unordered_map<std::string, std::unique_ptr<Model>> models;
public:
    Model* GetModel(std::string name) {
        if (models.find(name) != models.end())
            return models[name].get();
        return nullptr;
    }
    template<typename Range> Model* GetModel(std::string name, Range r) {
        if (models.find(name) != models.end())
            return models[name].get();
        return models[name] = CreateModelFromRange(r);
    }
    void UnloadModel(std::string name) {
        models.erase(name);
    }
};
    
    