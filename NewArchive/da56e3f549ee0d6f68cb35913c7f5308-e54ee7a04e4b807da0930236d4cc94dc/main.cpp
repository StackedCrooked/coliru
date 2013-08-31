#include <cstdio>
#include <string>
#include <iostream>

using std::endl;
using std::string;

void print(string str) {
    std::cout << str << endl;
}

void process(int hr, int min, string t) {
	string ret("Time: " + std::to_string(hr) + " " + std::to_string(min) + t);
	if (min >= 50) {
		++hr;
	}
	if (t != "") {
		// assume 24hr format
		if (hr < 0 || hr > 12) {
			print("BAD!");
			std::exit(-1);
		}
		if (t == "pm") {
			hr += 12;
		}
	}
	if (hr >= 5 && hr < 12) {
		print("Good Morning");
	}
	if (hr >= 12 && hr < 19) {
		print("Good Afternoon");
	}
	if ((hr >= 19 && hr <= 24) || (hr >= 0 && hr < 5)) {
		print("Good Evening");
	}
}

int main() {
	string time;
	print("Enter time, eg 1:30am, 22:00");
	while (true) {
		std::getline(std::cin, time);
		int hour, min;
		char t[2];
		sscanf(time.c_str(), "%d:%d%s", &hour, &min, &t[0]);
		string t_(t);
		process(hour, min, t_);
	}
	return 0;
}
