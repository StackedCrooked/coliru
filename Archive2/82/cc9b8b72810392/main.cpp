#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
using namespace std;

int main() {
    typedef int T;
    typedef std::vector<T>                  content_1d_t;
    typedef boost::shared_ptr<content_1d_t> storage_1d_t;

    typedef std::vector<storage_1d_t>       content_2d_t;
    typedef boost::shared_ptr<content_2d_t> storage_2d_t;

    int dim1 = 10;
    int dim2 = 1;
    storage_2d_t storage_1 = boost::make_shared<storage_2d_t::element_type>(dim2);

    for (auto& v1d : *storage_1)
        v1d = boost::make_shared<storage_1d_t::element_type>(dim1);

    storage_2d_t storage_2 = storage_1;
    // note that storage_1 and storage_2 now refer to exactly the same vector:
    std::cout << "storage_2 aliases storage_1: " << std::boolalpha << (storage_1.get() == storage_2.get()) << "\n";

    for (int i = 0; i < dim2; ++i) {
        cout << "use count before : " << (*storage_1)[i].use_count() << endl;

        // note that storage_1 and storage_2 still refer to exactly the same vector:
        std::cout << "storage_2 aliases storage_1: " << std::boolalpha << ((*storage_1)[i].get() == (*storage_2)[i].get()) << "\n";

        storage_1d_t& sptr_1 = (*storage_1)[i];
        storage_1d_t& sptr_2 = (*storage_2)[i];

        std::cout << "elements refer to same shared_ptr: " << std::boolalpha << (&sptr_1 == &sptr_2) << "\n";

        sptr_2 = sptr_1; // doesn't do anything, really

        cout << "use count after: " << (*storage_1)[i].use_count() << endl; // unsurprisingly unchanged
    }
}
