class GeneratorBase;
class World {
    friend class GeneratorBase;
    //... stuff
    void SetColour(int x, int y) {}
};
class GeneratorBase {
protected:
    void SetColour(World& world, int x, int y) {
        return world.SetColour(x, y);
    }
};
class MahGeneratorOne : public GeneratorBase {
public:
    void Generate(World& world) {
        SetColour(world, 1, 2);
    }
};
int main() {
    World w;
    MahGeneratorOne gen;
    gen.Generate(w);
}