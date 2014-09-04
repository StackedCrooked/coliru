#include <ctime>
#include <iostream>

int calculate_age(tm entered_tm) {
    time_t current_time = time(NULL);
    tm current_tm = *gmtime(&current_time);
    
    int years = current_tm.tm_year - entered_tm.tm_year;
    int month_offset = current_tm.tm_mon - entered_tm.tm_mon;
    int months = years*12 + month_offset;
    if (current_tm.tm_mday > entered_tm.tm_mday)
        months -= 1;
    return months;
}

void main_age_io() {
    tm entered_tm = {0,0,0,3,9,2014};

    std::cout << "What is your birth year (1970)?\n"; 
    std::cin >> entered_tm.tm_year; 
    std::cout << "What is your birth month (1-12)?\n"; 
    std::cin >> entered_tm.tm_mon; 
    std::cout << "What is your birth day-of-month (1-31)?\n"; 
    std::cin >> entered_tm.tm_mday; 
    
    entered_tm.tm_year -= 1900; //tm.year expected to have have offset of 1900
    entered_tm.tm_mon -= 1; //tm.year expected to be 0-11    
    
    int months = calculate_age(entered_tm);
    
    std::cout << "You are " << months << " months old\n";
}

int main () {
    main_age_io();
    std::cout << "0\t=" << calculate_age({0,0,0,2,7,114}) << '\n';
    std::cout << "1\t=" << calculate_age({0,0,0,3,7,114}) << '\n';
    std::cout << "1\t=" << calculate_age({0,0,0,4,7,114}) << '\n';
    std::cout << "12\t=" << calculate_age({0,0,0,2,7,113}) << '\n';
    std::cout << "13\t=" << calculate_age({0,0,0,3,7,113}) << '\n';
    std::cout << "13\t=" << calculate_age({0,0,0,4,7,113}) << '\n';
    return 0;
}