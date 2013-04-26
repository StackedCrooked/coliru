template<class T>
struct identity{ using type = T; };

template<unsigned...>
struct seq : identity<seq>{};

int main(){}