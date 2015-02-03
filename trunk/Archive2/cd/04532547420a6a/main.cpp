template <typename T, int n>
class SmallVector {
private:
    T* begin_;
    T* end_;
    T* capacity_;
    alignas(T) char data_small_[n * sizeof(T)];
public:
    SmallVector()
    : begin_(reinterpret_cast<T*>(data_small_))
    , end_(reinterpret_cast<T*>(data_small_))
    , capacity_(reinterpret_cast<T*>(data_small_ + n * sizeof(T)))
    {}
};

int main()
{}
