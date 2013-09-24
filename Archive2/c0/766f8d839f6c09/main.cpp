#include <boost/units/unit.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>

#include <iostream>

using namespace boost::units;

quantity<si::velocity> calculateSpeed(quantity<si::length> distance, quantity<si::time> time)
{
    quantity<si::velocity> speed = distance/time;
	std::cout << distance << " / " << time << " = " << speed << std::endl;
	return speed;
}

int main()
{
	calculateSpeed(100*si::meter, 5*si::second);
}
