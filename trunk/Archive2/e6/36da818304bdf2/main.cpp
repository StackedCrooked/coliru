#include <iostream>
#include <thread>

class DataCollector
{
    public:
    DataCollector()
    {
        t1 = NULL;
        isCancelled = false;
    }
    
    ~DataCollector()
    {
        cancel();
    }
    
    void cancel()
    {
        if(t1 != NULL)
        {
            isCancelled = true;
            t1->join();
            delete t1;
            t1 = NULL;
        }
    }
    
    void startCollect()
    {
        t1 = new std::thread(readSource, this);
    }

    private:
    bool static readSource(DataCollector *dc)
    {
        while(!dc->isCancelled)
        {
            // read some data for storage
            std::cout << "Doing stuff..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        return true;
    }
    
    bool isCancelled;
    std::thread *t1;
};

int main()
{
    DataCollector myDataCollector;
    myDataCollector.startCollect();
    int seconds = 5;


    for(int i = 0; i < seconds; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
