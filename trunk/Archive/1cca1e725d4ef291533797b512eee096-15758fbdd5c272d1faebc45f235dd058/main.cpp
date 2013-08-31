#include <iostream>


struct RetransmissionTime_v1
{
    RetransmissionTime_v1(uint32_t rtt) :
        alpha_(0.9), // dilutes the update
        rtt_(rtt)
    {
    }

    uint32_t get() const
    {
        // JUST-IN-TIME ROUNDING
        return static_cast<uint32_t>(0.5 + rtt_);
    }

    // new value = 90% of old value + 10% of new value
    void update(uint32_t rtt)
    {        
        rtt_ = alpha_ * rtt_ + (1 - alpha_) * rtt;
    }

    double alpha_;
    double rtt_; // STORE AS DOUBLE
};

struct RetransmissionTime_v2
{
    RetransmissionTime_v2(uint32_t rtt) :
        alpha_(0.9), // dilutes the update
        rtt_(rtt)
    {
    }

    uint32_t get() const
    {
        return rtt_;
    }

    // new value = 90% of old value + 10% of new value
    void update(uint32_t rtt)
    {
        double new_rtt = alpha_ * rtt_ + (1 - alpha_) * rtt;
        
        // EAGER ROUNDING
        rtt_ = static_cast<uint32_t>(0.5 + new_rtt);
    }

    double alpha_;
    uint32_t rtt_; // STORE AS INTEGER
};


int main()
{
    RetransmissionTime_v1 rtt_v1(100);
    RetransmissionTime_v2 rtt_v2(100);
    
    std::cout << "Lazy\tEager\n";
    std::cout << rtt_v1.get() << '\t' << rtt_v2.get() << std::endl;
    for (int i = 0; i != 50; ++i)
    {
        rtt_v1.update(10);
        rtt_v2.update(10);
        std::cout << rtt_v1.get() << '\t' << rtt_v2.get() << std::endl;
    }
}
