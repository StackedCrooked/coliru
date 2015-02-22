#include <boost/algorithm/string.hpp>
#include <boost/container/scoped_allocator.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <algorithm>
#include <numeric>

namespace bi = boost::interprocess;
namespace bc = boost::container;

namespace common {
    template <typename Alloc>
    class CheckList {
        typedef typename Alloc::template rebind<double>::other double_allocator;
        typedef bc::vector<double, double_allocator> double_vector;

    public:
        double_vector values;

        typedef Alloc allocator_type;
        CheckList(const allocator_type& void_alloc = allocator_type()) : values(void_alloc) {}

        template <typename Alloc2>
        CheckList(CheckList<Alloc2> const& other, const allocator_type& void_alloc = allocator_type())
          : values(void_alloc)
        {
            for(auto& v : other.values) values.emplace_back(v);
        }

        friend std::ostream& operator<<(std::ostream& os, const CheckList& o) {
            for (size_t i = 0; i < o.values.size(); i++)
                os << (i?", ":"") << o.values[i];
            return os;
        }
    };

    template <typename Alloc>
    class Lists {
        typedef typename Alloc::template rebind<CheckList<Alloc> >::other checklist_allocator;

    public:
        typedef Alloc allocator_type;
        typedef bc::vector<CheckList<Alloc>, checklist_allocator> checklist_vector;

        template <typename Alloc2>
        Lists& operator=(Lists<Alloc2> const& other) {
            for(auto& cl : other.checklists) checklists.emplace_back(cl);
            return *this;
        }

        Lists(const Alloc& void_alloc = allocator_type()) : checklists(void_alloc) {}
        checklist_vector checklists;

        friend std::ostream& operator<<(std::ostream& os, const Lists& o) {
            for (size_t i = 0; i < o.checklists.size(); i++)
                os << o.checklists[i] << '\n';
            return os;
        }
    };
}

namespace Shared {
    typedef bi::managed_mapped_file::segment_manager                             segment_manager_t;
    typedef bc::scoped_allocator_adaptor<bi::allocator<void, segment_manager_t> >  void_allocator;
    using Lists = common::Lists<void_allocator>;
}

namespace Heap {
    typedef std::allocator<void> void_allocator;
    using Lists = common::Lists<void_allocator>;
}

    Heap::Lists generate_local() {
        Heap::Lists lists;
        Heap::Lists::checklist_vector::value_type v;

        for (int i=0; i<10; ++i) {
            v.values.emplace_back(i+1);
            lists.checklists.push_back(v);
        }

        return lists;
    }

    int main(int argc, char **argv) {

        if (argc > 1 && (boost::iequals("clear", argv[1]) || boost::iequals("c", argv[1]))) {
            std::cout << "Remove shared memory" << std::endl;
            std::remove("MySharedMemory");
        }

        //Create shared memory
        bi::managed_mapped_file segment(bi::open_or_create,"MySharedMemory", 16*1024);

        using Lists = Shared::Lists;

        //An allocator convertible to any allocator<T, segment_manager_t> type
        Lists::allocator_type alloc_inst(segment.get_segment_manager());
        Lists& lists = *segment.find_or_construct<Lists>("Lists")(alloc_inst);

        if (lists.checklists.size() != 10) {
            std::cout << "Create Data" << std::endl;
            auto x = generate_local();
            lists = std::move(x);
        } else {
            std::cout << "Data Exists" << std::endl;
        }

        std::cout << lists << std::endl;
    }
