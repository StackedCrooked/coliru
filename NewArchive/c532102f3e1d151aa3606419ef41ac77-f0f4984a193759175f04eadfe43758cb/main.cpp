#include <mutex>
#include <queue>

namespace netw
{
    struct Packet {};
}

template <typename ListenerT>
class Driver
{
public:
    template <typename... Args>
    Driver(Args&&... args) :
        listener_(std::forward<Args>(args)...) {}

    void enqueue_md(netw::Packet* packet)
    {
        std::lock_guard<std::mutex> lock(pending_md_mtx_);
        pending_md_.push(packet);
    }

    void process_md()
    {
        std::lock_guard<std::mutex> lock(pending_md_mtx_);
        while (pending_md_.size())
        {
            netw::Packet* pkt=pending_md_.front();
            pending_md_.pop();
            process_md(*pkt);
        }
    }
    //... Other code which I can't post...

private:
    ListenerT listener_;
    std::mutex pending_md_mtx_;
    std::queue<netw::Packet*> pending_md_;
};

struct Lsnr {};

int main()
{
    Driver<Lsnr> driver;
}
