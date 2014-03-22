#include <boost/thread.hpp>
#include <boost/optional.hpp>

using namespace boost;

boost::atomic_size_t counter(0ul);

static constexpr size_t bignumber = 1 << 14;

class myClass 
{
    //unsigned char readbuffer[bignumber];
    //unsigned char writebuffer[bignumber];
    void functiondostuff() { }
    void functiondomorestuff() { }

    boost::thread_group group;
  public:
    void wreak_havoc()
    {
        std::cout << "enqueuing jobs... " << std::flush;
        for(size_t i=0; i<bignumber; ++i)
        {
            functiondostuff();
            for(int j=0; j<2; ++j) {
                functiondomorestuff();
                group.create_thread(bind(&myClass::myFunction, this, j, i));
            }     
        }
        std::cout << "done\n";
    }

    ~myClass() {
        group.join_all();
    }

  private:
    void myFunction(int i, int j)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
        counter += 1;
    }
};

int main()
{
    myClass instance;
    instance.wreak_havoc();

    size_t last = 0;
    while (counter < (2*bignumber))
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        if ((counter >> 4u) > last)
        {
            std::cout << "Progress: " << counter << "/" << (bignumber*2) << "\n";
            last = counter >> 4u;
        }
    }

}
