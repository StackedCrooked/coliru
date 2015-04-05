#include <iostream>
#include <fstream>
#include <string>

#include "Flexiglass.hpp"

class Reader
{
public:
    Reader(flgl::Event_Queue& eq)
	: sender(eq)
	{}

	void read(const char* str)
	{
		std::string buffer;
		
		file.open(str);
		
		//Open file
		if (!file)
		{
			std::cout << "File: " << str << " could not open!\n";
			return;
		}
		else
			std::cout << "File: " << str << " opened.\n";
		
		int line_no = 1;
		//Print out file line by line
		while(file && file.good())
		{
			//Create line number as name
			std::string name = "line";
			name.push_back(line_no);
			
			//Read a line
			getline(file, buffer);
			std::cout << buffer << "\n";
			
			//Package an flgl::Event with data
			flgl::Event msg(name, "reader_text");
			msg.push_data(buffer);
			
			//Send an Event to the Event_Queue
			sender.send_event(msg);
			++line_no;
		}
		
		file.close();
	}
private:
	flgl::Event_Sender sender;
	std::fstream file;
	
};

//Writer class inherits from interface and has a Listener.
class Writer : public flgl::Event_Receivable
{
public:
	Writer(flgl::Event_Queue& eq)
	: listener(this)
	{
		eq.add_listener(dynamic_cast<flgl::Event_Listener*>(&listener));
		std::cout << "Writer initialized." << std::endl;
	}
	
private:
	flgl::Event_Listener listener;
	std::fstream file;
	
	//Event handler is overloaded
	virtual void on_notify(flgl::Event* e) override
	{
		//If it's the correct type of message, unpack
		if (e->get_type() == "reader_text")
		{
			flgl::data_list data_list = e->get_data();
			flgl::any data = data_list.front();
			std::string text = flgl::unpack<std::string>(data);
			
			//Print out the line received
			if (!text.empty())
				std::cout << text << std::endl;
		}
	}
};

flgl::Event_Receivable::~Event_Receivable() {}


int main()
{
	flgl::Event_Queue event_queue;
	
	Reader r(event_queue);
	r.read("file.txt");
	
	std::cout << "/////\n/////\n/////\n";
	
	Writer w(event_queue);
	
	char c;
	while(std::cin >> c && c != '!')
		event_queue.process();
	
	return 0;
}