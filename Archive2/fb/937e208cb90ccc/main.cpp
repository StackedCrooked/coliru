    #include <boost/multi_index_container.hpp>
    #include <boost/multi_index/sequenced_index.hpp>
    #include <boost/multi_index/ordered_index.hpp>
    #include <boost/multi_index/member.hpp>
       
    #include <iostream>
    #include <vector>

    using namespace boost::multi_index;
    using namespace std;

    struct Entry {
        int nonUniqueInt;
        string somethingExtra;
    };

    using Container_t = multi_index_container<Entry, indexed_by<
        sequenced<>,
        ordered_non_unique<
            // ***** What can I put here? *****
            member<Entry, int, &Entry::nonUniqueInt>
        >
    >>;

    std::vector<Entry> const sampleData{
        {1, "first"}, {2, "second"}, {3, "third"}, {3, "fourth"}, {2, "fifth"}, {1, "sixth"}
    };

    // fillFront should make the sequence LIFO
    template <typename T>
    void fillFront(T & container) {
        for (auto & item : sampleData) {
            container.push_front(item);
        }
    }

    // fillBack should make the sequence FIFO
    template <typename T>
    void fillBack(T & container) {
        for (auto & item : sampleData) {
            container.push_back(item);
        }
    }

    int main() {
        Container_t container;
        auto & sequenced = container.get<0>();
        auto & ordered = container.get<1>();

        fillFront(sequenced);
        for(auto & entry : ordered) {
            cout << entry.nonUniqueInt << ": " << entry.somethingExtra << endl;
        }

        cout << endl;
        container.clear();

        fillBack(sequenced);
        for(auto & entry : ordered) {
            cout << entry.nonUniqueInt << ": " << entry.somethingExtra << endl;
        }
    }

    // Expected/desired output:   Actual output:
    //  1: sixth                   1: first
    //  1: first                   1: sixth
    //  2: fifth                   2: second
    //  2: second                  2: fifth
    //  3: fourth                  3: third
    //  3: third                   3: forth
    //           
    //  1: first                   1: first
    //  1: sixth                   1: sixth
    //  2: second                  2: second
    //  2: fifth                   2: fifth
    //  3: third                   3: third
    //  3: forth                   3: forth

