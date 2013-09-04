#include <iostream>
#include <vector>

using namespace std;

class DisplayImage {
public:
virtual void display() = 0; // mostra dati immagine
virtual ~DisplayImage(){};
};

class DisplayImageContent : public DisplayImage{
    public:
    DisplayImageContent(){};
    void display(){
        cout<< "A"<<endl;
    }
};

class DisplayImageMetadata : public DisplayImage{
    public:
    DisplayImageMetadata(){};
    void display(){
        cout<< "B"<<endl;
    }
};

class MyImage {
public:
MyImage() : _X(100), _Y(100), _channels(3), _transp(1.0) {};
void setParams(int X, int Y, int channels, float transp) {
      _X=X;
      _Y=Y;
      _channels=channels;
      _transp= transp;
      Update(Observers);
 }

void Update(vector <DisplayImage*> obs){  //L'importante è qui
    for (vector <DisplayImage*>::iterator iter = obs.begin(); iter!=obs.end(); iter++){
    (*iter)->display();
}
}

vector <DisplayImage*> Observers;       //Vettore di observers!!!
vector <DisplayImage*>::iterator it;

private:
int _X, _Y;
int _channels;
float _transp; 

};



int main()
{
    MyImage img;
    DisplayImageMetadata* dim = new DisplayImageMetadata;
    DisplayImageContent* dic = new DisplayImageContent;
    
    img.Observers.push_back(dim);
    img.Observers.push_back(dic);


    img.Update(img.Observers);   //no problem!
    
   cout << "Hello World" << endl; 
   
   return 0;
}