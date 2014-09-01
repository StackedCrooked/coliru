#include <iostream>
#include <memory>
#include <iostream>

template<typename Impl>
struct renderer{
    void get() const {
        static_cast<const Impl*>(this)->_get();
    }
};
struct open_gl : public renderer<open_gl>{
    void _get() const {
        std::cout << "OpenGL" << std::endl;
    }
};
struct direct_draw : public renderer<direct_draw>{
    void _get() const {
        std::cout << "DX" << std::endl;
    }
};
struct typeerased : public renderer<typeerased> {
private:
    struct inter {
        virtual void _get() const=0;
    };
    template<class T>
    struct impl : public inter {
        template<class...Us>
        impl(Us&&...vs) : t(std::forward<Us>(vs)...) {}
        void _get() const {return t.get();}
        T t;
    };
    std::unique_ptr<inter> ptr;
public:
    typeerased() = default;
    typeerased(typeerased&&) = default;
    typeerased&operator=(typeerased&&) = default;
    template<class T, class...Us>
    typeerased(T*t, Us&&...vs) : ptr(new impl<T>(std::forward<Us>(vs)...)) {assert(t==nullptr);}
    template<class T, class allowed=renderer<typename std::decay<T>::type>>
    typeerased(T&&t) : ptr(new impl<T>(std::forward<T>(t))) {}
    template<class T, class...Us>
    void reset(Us&&...vs) {ptr.reset(new impl<T>(std::forward<Us>(vs)...));} 
    
    void _get() const {return ptr->_get();}
};

template<typename T>
void print_renderer(const renderer<T>& r){
    r.get();
}
int main() {
    auto gl = open_gl();
    auto dx = direct_draw();
    print_renderer(gl);
    print_renderer(dx);
    
    auto te = typeerased(open_gl{});
    print_renderer(te);
    te.reset<direct_draw>();
    print_renderer(te);
    return 0;
}