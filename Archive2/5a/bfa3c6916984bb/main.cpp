template<typename Parser>
struct ModuleA{
    using DType = typename Parser::DType;
    // extract more important types from Parser type...

    using OptionsType = int;
};

template<typename D>
struct Parser{
    using DType = D;
    using ModuleTypeA = ModuleA<Parser>;

    using ModuleOptionsA = typename ModuleTypeA::OptionsType; //uncomment this!!

};

int main() {
    Parser<double> t;
}
