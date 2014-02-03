#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>

std::string formatDuration(time_t duration)
{
    static const time_t MINUTE = 60;
	static const time_t HOUR   = 60 * MINUTE;
	static const time_t DAY    = 24 * HOUR;
	static const time_t WEEK   =  7 * DAY;
	
	std::vector<std::string> parts;
	
	if (duration >= WEEK) {
		std::stringstream ss;
		ss << (duration/WEEK) << " week" << (duration/WEEK == 1 ? "" : "s");
		parts.push_back(ss.str());
		
		duration %= WEEK;
	}
	
	if (duration >= DAY) {
		std::stringstream ss;
		ss << (duration/DAY) << " day" << (duration/DAY == 1 ? "" : "s");
		parts.push_back(ss.str());
		
		duration %= DAY;
	}
	
	if (duration >= HOUR) {
		std::stringstream ss;
		ss << (duration/HOUR) << " hour" << (duration/HOUR == 1 ? "" : "s");
		parts.push_back(ss.str());
		
		duration %= HOUR;
	}
	
	if (duration >= MINUTE) {
		std::stringstream ss;
		ss << (duration/MINUTE) << " minute" << (duration/MINUTE == 1 ? "" : "s");
		parts.push_back(ss.str());
		
		duration %= MINUTE;
	}
	
	if (duration > 0) {
		std::stringstream ss;
		ss << duration << " second" << (duration == 1 ? "" : "s");
		parts.push_back(ss.str());
	}
	
	std::string result;
	std::vector<std::string>::const_iterator it = parts.begin(), end = parts.end();
	for ( ; it != end; ++it) {
		if (it != parts.begin())
			result += ", ";
		result += *it;
	}
	return result;
}

int main()
{
    std::cout << formatDuration(0) << std::endl;
    std::cout << formatDuration(1) << std::endl;
    std::cout << formatDuration(2) << std::endl;
    std::cout << formatDuration(59) << std::endl;
    std::cout << formatDuration(60) << std::endl;
    std::cout << formatDuration(61) << std::endl;
    std::cout << formatDuration(300) << std::endl;
    std::cout << formatDuration(900) << std::endl;
    std::cout << formatDuration(1800) << std::endl;
    std::cout << formatDuration(3600) << std::endl;
    std::cout << formatDuration(3601) << std::endl;
    std::cout << formatDuration(86423) << std::endl;
    std::cout << formatDuration(1234567) << std::endl;
}