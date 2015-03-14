#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

struct flightdata {
    static const int max_pass = 275;
    static const int min_pass = 50;

    int number;
    int num_passengers;
    std::string name;
    std::string destination;
    int index;
};
auto sort_flights_by_destination = [](const flightdata& left, const flightdata& right)->bool {return left.destination<right.destination;};
auto sort_flights_by_name = [](const flightdata& left, const flightdata& right)->bool {return left.name<right.name;};

const int max_records = 4;
flightdata flights[max_records];

void display_airline();
void display_destination();
std::istream& operator>>(std::istream& in, flightdata& row);

int main()
{ 
    for(flightdata& flight : flights) 
        std::cin >> flight;
        
    display_airline();
    display_destination();

    return 0;
}

std::istream& operator>>(std::istream& in, flightdata& flight)
{
    std::cout << "\nPlease enter...";
    std::cout << "\nAirline Name----> ";
    in >> flight.name;
    std::cout << "\nFlight Number----> ";
    in >> flight.number;
    std::cout << "\nDestination----> ";
    in >> flight.destination;
    std::cout << "\nPassenger Load----> ";
    in >> flight.num_passengers;
    
    while (in && (flight.num_passengers < flightdata::min_pass || flight.num_passengers > flightdata::max_pass))
    {
        std::cout << "\nYou have entered an invalid amount of passengers.";
        std::cout << "\nThere must be between 50 and 275 passengers. > ";
        in >> flight.num_passengers;
    }
    return in;
}

void display_airline()
{
    system("cls");
    std::sort(std::begin(flights), std::end(flights), sort_flights_by_name);

    std::cout<<'\n'<<std::setw(12)<<"Airline"<<std::setw(10)<<"Flight"<<std::setw(20)<<"Destination"<<std::setw(6)<<"#Pass";
    for(flightdata& flight : flights) 
        std::cout<<'\n'<<std::setw(12)<<flight.name<<std::setw(10)<<flight.number<<std::setw(20)<<flight.destination<<std::setw(6)<<flight.num_passengers;
}

void display_destination()
{
    system("cls");
    std::sort(std::begin(flights), std::end(flights), sort_flights_by_destination);

    std::cout<<'\n'<<std::setw(20)<<"Destination"<<std::setw(12)<<"Airline"<<std::setw(10)<<"Flight"<<std::setw(6)<<"#Pass";
    for(flightdata& flight : flights) 
        std::cout<<'\n'<<std::setw(20)<<flight.destination<<std::setw(12)<<flight.name<<std::setw(10)<<flight.number<<std::setw(6)<<flight.num_passengers;
}
