
template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    template<typename ...Args>
    explicit StrongTypedef(Args && ...args) : data_(std::forward<Args>(args)...) {}    
    operator const T&() const { return data_; }        
    
    T data_;
};


typedef StrongTypedef<int, struct width_> Width;
typedef StrongTypedef<int, struct height_> Height;

int GetArea(Width w, Height h)
{
    return w * h;
}


int main()
{
    return GetArea(Width(200), Height(300));
}