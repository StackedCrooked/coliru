#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

@class flights;




int main()
{
    flights * fli = new flights(10);
    return 0;
}



class flights {
    struct flight;
private:
    int size;
    flight* flight_list;
public:
    
    flights(const flights & cp) {
        this->size=cp.size;
    }

    flights(int size) {
        this->size = size;
        this->flight_list = new flight[size];
    }

    ~flights() {
        delete [] flight_list;
    }

private:

    struct flight {
        
        int flight_number;
        int number_of_rows_of_seats;
        int number_of_seats_in_each_row;
        flight(int flight_number, int number_of_rows_of_seats, int number_of_seats_in_each_row) : flight_number(flight_number), number_of_rows_of_seats(number_of_rows_of_seats), number_of_seats_in_each_row(number_of_seats_in_each_row) {
        }
        flight() {
            this->flight_number =0;this->number_of_rows_of_seats =0;this->number_of_seats_in_each_row =0;
        }
    };
    
};