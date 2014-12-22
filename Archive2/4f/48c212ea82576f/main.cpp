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
    storage_2d_t storage_1 = boost::make_shared<storage_2d_t::element_type>();
    storage_1->reserve(dim2);

    for (int i = 0; i < dim2; ++i) {
        storage_1->push_back(boost::make_shared<storage_1d_t::element_type>(dim1));
    }

    storage_2d_t storage_2 = storage_1;

    for (int i = 0; i < dim2; ++i) {
        cout << "use count before : " << (*storage_1)[i].use_count() << endl;
        (*storage_2)[i] = (*storage_1)[i];
        cout << "use count after: " << (*storage_1)[i].use_count() << endl;
    }

    for (int i = 0; i < dim2; ++i) {
        cout << "use count before : " << (*storage_1)[i].use_count() << endl;
        {
            storage_1d_t ref = (*storage_1)[i];
            (*storage_2)[i] = ref;
            cout << "use count during: " << (*storage_1)[i].use_count() << endl;
        }
        cout << "use count after: " << (*storage_1)[i].use_count() << endl;
    }
}
