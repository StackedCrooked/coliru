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
    class DataOwnerCallback;
    
public:
    void doProcess(DataOwner&);
};


class Processor::DataOwnerCallback final : public IDataOwnerCallback
{
    Processor& p;
public:
    DataOwnerCallback(Processor& p)
    : p(p)
    {}

    virtual void visit(Data& data) final override
    {
        p.useData(data);
    }
};



void Processor::doProcess(DataOwner& dataOwner)
{   
    DataOwnerCallback callback(*this);
    dataOwner.accept(&callback);
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