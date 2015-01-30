#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

struct texture {
    virtual ~texture() {}
    virtual void foo() const = 0;
};

struct texA : texture { virtual void foo() const { std::cout << __PRETTY_FUNCTION__ << " "; } };
struct texB : texture { virtual void foo() const { std::cout << __PRETTY_FUNCTION__ << " "; } };

template <typename Pointer> void test() {

    struct mesh {
        Pointer _ptr;

        mesh()    : _ptr(new(texA)) {}
        mesh(int) : _ptr(new(texB)) {}

        void bar() const { _ptr->foo(); }
    };

    boost::ptr_vector<mesh> meshes;
    for (int i=0; i<100; ++i) {
        if (rand()%2)
            meshes.push_back(new mesh(i));
        else
            meshes.push_back(new mesh());
    }

    for (auto& m : meshes)
        m.bar();
}

#include <boost/scoped_ptr.hpp>
#include <memory>

int main() {

    //  non-leaking methods
    test<boost::scoped_ptr<texture> >(); // scoped_ptr_mesh
    test<std::unique_ptr<texture> >();   // std_mesh
    test<std::shared_ptr<texture> >();   // shared_mesh

    // uncommenting the next causes textures to be leaked
    // test<texture*>();                    // leaking_mesh
}
