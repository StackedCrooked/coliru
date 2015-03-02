#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace boost::multi_index;

struct Demo {
    Demo(int id) : id(id) {}
    int get_id() const { return id; }

    ~Demo() { std::cout << "some kind of deleter runs :)\n"; }
    private:
    int id;
};

typedef multi_index_container<boost::shared_ptr<Demo>, // use pointer instead of real Demo
        indexed_by<
        // hash using function Demo::get_id
        hashed_unique<const_mem_fun<Demo, int, &Demo::get_id>>> // end indexed_by
        > HostContainer;

int main()
{
    {
        HostContainer testHosts;
        testHosts.insert(boost::make_shared<Demo>(42));
    }

    std::cout << "done\n";
}
