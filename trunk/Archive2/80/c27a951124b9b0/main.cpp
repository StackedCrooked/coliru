template<class ...> struct Tuple {};
template<class T1, class ... Types> void g(Tuple<T1, Types ...>);
template<class T1, class ... Types> void g(Tuple<T1, Types& ...>);
g(Tuple<int>());