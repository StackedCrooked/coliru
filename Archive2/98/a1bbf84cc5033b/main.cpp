#include <list>

class cli {
public:
    struct stat {
        unsigned long int id;
        bool is_locked;
        bool release;
    };
    std::list<stat> li;
    std::list<stat>::pointer search_item(unsigned long int);
};

std::list<stat>::iterator search_item(unsigned long int) {

}

int main() {
    cli cl;
    cl.search_item(4);
}