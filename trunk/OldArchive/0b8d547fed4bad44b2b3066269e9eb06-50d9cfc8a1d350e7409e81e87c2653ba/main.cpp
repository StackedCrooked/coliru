
template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    explicit StrongTypedef(const T & data = T()) : data_(data) {}    
    operator const T&() const { return data_; }        
    
    T data_;
};
