#include <iostream>

using namespace std;

class CI
{
 public:
 virtual void display() =0; 
};


class Inter: public CI
{
 public:
  int parseData (int);
};

int Inter::parseData (int data)
{
  cout <<"Parsing the data "<<data;
  return data*100;
}



class Last: public Inter
{
 public:
  virtual void display();
};

void Last::display()
{
  cout <<" Last:: Displaying From Last "<<endl;
}

class USB: public Inter
{
 public:
  void display();
};


void USB::display()
{
  cout <<" USB:: Displaying From Last "<<endl;
}
int main ( int argc, char ** argv)
{
  int temp;
  Inter *obj = new Last;

  obj->display();
  temp = obj->parseData (100);
  cout <<"Parsed DAta .. "<<temp<<endl;
  delete obj;

  obj = new USB;
  obj->display();
  temp = obj->parseData (200);

}