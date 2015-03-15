template <typename LHT, typename RHT>
auto findGreater(LHT lhs, RHT rhs) -> decltype((lhs > rhs) ? lhs : rhs) { return (lhs > rhs) ? lhs : rhs; }

int main(){
    findGreater(1,2);
}