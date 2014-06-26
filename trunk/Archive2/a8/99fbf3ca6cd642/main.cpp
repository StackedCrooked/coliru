// empty list:
template<typename... Args>
struct List {
    struct head {static_assert(sizeof...(Args) != 0, "Attempt to access the head of an empty list."); };
    struct tail {static_assert(sizeof...(Args) != 0, "Attempt to access the tail of an empty list."); };
};

// non-empty list:
template<typename Head, typename ...Tail>
struct List<Head, Tail...> {
    typedef Head head;
    typedef List<Tail...> tail;
};



int main() {
    typedef List<int, long> l;
    l::head i = 0;
    typedef l::tail l2;
    l2::head c = 0L;
    typedef l2::tail l3;
    l3 test;
    // l3::tail l4;  // uncomment for compile error
}