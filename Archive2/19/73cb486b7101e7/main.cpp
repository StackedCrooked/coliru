#include <string>

namespace foo {
    struct placeholder_value {
        constexpr placeholder_value() {}    
    } constexpr _;
    
    template<typename... Ts>
    struct TypeList {};
    
    template<typename T, typename... Ts>
    struct AddType_;
    
    template<typename T, typename... Ts>
    struct AddType_<TypeList<Ts...>, T> {
        using type = TypeList<Ts..., T>;
    };
    
    template<typename T, typename... Ts>
    using AddType = AddType_<T, Ts...>;
    
    struct File {
        File(const std::string &/*filename*/, int /*blockSize*/ = 1024, bool /*isReadonly*/ = false) {}
    };
    
    template<typename... Params>
    struct OpenFile {
        template<typename... OtherParams>
        friend struct OpenFile;
        
        friend File build(Params...);
        
        constexpr OpenFile() {}
        
        template<typename... OtherParams>
        constexpr OpenFile(const OpenFile<OtherParams...> other) 
            : blockSizeProvided_(other.blockSizeProvided_), filenameProvided_(other.filenameProvided_), isReadonly_(other.isReadonly_) {}
        
        constexpr OpenFile<Params..., const std::string &> filename(placeholder_value) {
            filenameProvided_ = true;
            return OpenFile<Params..., const std::string &>(*this);
        }
        
        constexpr OpenFile &readonly() {
            isReadonly_ = true;
            return *this;
        }
        
        constexpr OpenFile<Params..., int> blockSize(placeholder_value) {
            blockSizeProvided_ = true;   
            return OpenFile<Params..., int>(*this);
        }
        
        constexpr bool valid() const {
            return filenameProvided_;
        }
        
        File build(Params... params) const {
            return File(params...);
        }
        
    private:
        bool blockSizeProvided_ = false;
        bool filenameProvided_ = false;
        
        bool isReadonly_ = false;
    };
}

int main() {
    using namespace foo;
    constexpr auto builder = OpenFile<>().blockSize(_);
    static_assert(builder.valid());
    
    auto file = builder.build(1000);
}
