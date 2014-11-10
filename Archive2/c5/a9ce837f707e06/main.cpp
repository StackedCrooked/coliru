#include <vector>

template <typename InType> class PipeBase {
public:
    virtual ~PipeBase() = default;
    virtual void Fill(InType value) = 0;
};

template <typename InType,typename OutType> class Pipe : public PipeBase<InType> {
public:
    void addListener(PipeBase<OutType>* l){
        listener.push_back(l);
    }
    virtual OutType process(InType) {return OutType();}//=0;
    
    void Fill(InType value) override {
        OutType outValue = process(value);
        for (std::size_t i=0;i<listener.size();i++){
            listener[i]->Fill(outValue);
        }
    }
private:
    std::vector<PipeBase<OutType>*> listener;
};

int main()
{
    Pipe<int, float> p1;
    Pipe<float, char> p2;
    p1.addListener(&p2);
}