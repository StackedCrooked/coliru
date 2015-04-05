#include <iostream>
#include <fstream>
#include <string>

#include "Flexiglass.hpp"

//Basic file reader class for demonstration purposes
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
			std::cout << "File: " << str << " is:\n";
		
		int line_no = 1;
		//Print out file line by line
		while(file && file.good())
		{
			//Create line number as name
			std::string name = "line";
			name += std::to_string(line_no);
			
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
//Event_Receivable only requires one function to be defined: on_notify.
//on_nofify also takes one flgl::Event* argument.
class Writer : public flgl::Event_Receivable
{
public:
	Writer(flgl::Event_Queue& eq)
	: listener(this)
	{
		//Write over or create a new file to output to.
		file.open("output.txt", std::ios::out);
		
		eq.add_listener(dynamic_cast<flgl::Event_Listener*>(&listener));
		std::cout << "Writer initialized. Enter a character to write to a output.txt. Press ! to end." << std::endl;
	}
	
	~Writer()
	{
		file.close();
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
			{
				std::cout << e->get_name() << ": " << text << std::endl;
				file << e->get_name() << ": " << text << std::endl;
			}
		}
	}
};

int main()
{
	//Create an event queue to pass events to
	//Multiple event queue can be used to separate lines of work
	flgl::Event_Queue event_queue;
	
	//Create an arbitrary Reader object to open a file
	//Select the queue that it will send events to
	Reader r(event_queue);
	//Read the file
	r.read("file.txt");
	
	std::cout << "/////\n/////\n/////\n";
	
	//Initialize the writer object, creating a new file.
	//Select the queue that it will subscribe to
	Writer w(event_queue);
	
	//Line by line reception of messages
	char c;
	while(std::cin >> c && c != '!')
		event_queue.process();
	
	return 0;
}