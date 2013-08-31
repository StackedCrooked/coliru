//andere .cpp:


void Init()
{
    Timer j;
    unsigned int t = j.get_ticks(); // get system ticks

	boost::mt19937 rng;
	rng.seed(static_cast<unsigned int>(std::time(0) + t + getpid()));
	boost::uniform_int<> u(5, UINT_MAX);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gen(rng, u);
	seed = gen();
	
	std::cout << "seed: " << seed << std::endl;

	Dungeoncraft::rng.seed(static_cast<unsigned int>(std::time(0) + t + getpid()));    
}


//.h:

namespace mynamespace
{
    static boost::mt19937 rng;
    
    int random(int min, int max);
    float random(float min, float max);
}

//.cpp:

namespace Dungeoncraft
{    

	int random(int min, int max)
	{
		boost::uniform_int<> u(min, max);
		boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gen(rng, u);
		return gen();
	}

	float random(float min, float max) 
	{	
		boost::uniform_real<float> u(min, max);
		boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
		return gen();
	}
}