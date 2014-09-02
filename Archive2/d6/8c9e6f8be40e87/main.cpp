class Processor;

class Data
{
    friend Processor;
    void privateFunction() {}
};

class IDataOwnerCallback
{
public:
    virtual void visit(Data&) = 0;
};

class DataOwner
{
    Data d;
public:
    void accept(IDataOwnerCallback* pcb) { pcb->visit(d); }
};

class Processor
{
    void useData(Data& data);
public:
    void doProcess(DataOwner&);
};

void Processor::doProcess(DataOwner& dataOwner)
{   
    auto l = [this](Data& d) { useData(d); };
    
    class DataOwnerCallback final : public IDataOwnerCallback
    {
        decltype(l)& l;
    public:
        DataOwnerCallback(decltype(l)& p)
        : l(p)
        {}

        virtual void visit(Data& data) final override
        {
            l(data);
        }
    } callback;
    
    dataOwner.accept(callback);
}

void Processor::useData(Data& data)
{
    // Use the data, accessing private functionality via friendship
    data.privateFunction();
    // etc
}

int main()
{
    DataOwner dataOwner;
    Processor p;
    p.doProcess(dataOwner);
}