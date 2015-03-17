#include <iostream>
#include <string>
#include <vector>

#include <stdint.h>
#include <math.h>
#include <deque>


int16_t int_arr[10] = {
936,
924,
923,
923,
924,
923,
922,
923,
924,
923
};

class ThresholdCalculator
{
public:
    ThresholdCalculator(uint16_t win_size)    
    :	max_samples(win_size),
	 	mean_accumulator(0ULL),
	 	std_accumulator2(0ULL)
    {
        
    }
	~ThresholdCalculator(){}
	void add_value(int16_t val)
    {
        if( data_buffer.size()==max_samples )
	    {
        	int16_t removed_value = data_buffer.front();
        	// remove from front
        	data_buffer.pop_front();
        	// update accumulators
        	mean_accumulator = mean_accumulator - removed_value;
        	std_accumulator2 =
        			std_accumulator2 - (removed_value*removed_value);
	    }
	// add at the end
	    data_buffer.push_back(val);
        mean_accumulator = mean_accumulator + val;
        std_accumulator2 = std_accumulator2 + (val*val);
        
        std::cout << "data buf size = " << data_buffer.size() << std::endl;
        std::cout << "max samples = " << max_samples << std::endl;
        std::cout << "mean_accumulator = " << mean_accumulator << std::endl;
        std::cout << "std_accumulator2 = " << std_accumulator2 << std::endl;
    }
    
	uint64_t get_mean(void)
    {
        return (mean_accumulator/data_buffer.size());
    }
    
	uint64_t get_std(void)
    {
            return (uint64_t)(sqrt(static_cast<double> ((data_buffer.size()*std_accumulator2) -
			(mean_accumulator*mean_accumulator)) )/data_buffer.size() + 0.5);
    }
    
	void reset(void)
    {
        data_buffer.clear();
	    mean_accumulator = 0ULL;
	    std_accumulator2 = 0ULL;
    }

private:
	uint16_t max_samples;
	uint64_t mean_accumulator;
	uint64_t std_accumulator2;
	std::deque<int16_t> data_buffer;
};


int main()
{
    std::cout << "hello world" << std::endl;
    ThresholdCalculator th_cal(10);
    th_cal.reset();
    
    for(int i=0; i<10; i++)
    {
        th_cal.add_value(int_arr[i]);
        
        std::cout << "mean = " << th_cal.get_mean() << std::endl;
        std::cout << "std_dev = " << th_cal.get_std() << std::endl;
    }   
}


