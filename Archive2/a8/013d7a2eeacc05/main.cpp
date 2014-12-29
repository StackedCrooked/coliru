#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class empty
{
};

class audience
{ 
protected:
  int name;
  static int amount;
  virtual void show()
  {
    cout << "main" << amount<< endl;
  };
public:
  audience();  
  void Print()
  {
    show();   
  };
};
int audience::amount =0;


class Mat_kafedra : public audience
{
public:
    Mat_kafedra();
	void show()
  {
    cout << name << " – аудит. Каф. математики" << endl;
  }
};

Mat_kafedra::Mat_kafedra() : audience()
{

	while(1)
    {
      try
      {
        cout<<endl;
         int name;
         cout<<"вместительность(не более 100 чел.):  ";
         cin >> name;
        
        if(name<1 || name>100)
          throw 1;
        Mat_kafedra::name=name;
        amount++;
        return;
      }
      catch (int)
      {
          cout << "Введено неверное количество\n";
      }
    
    }
  
}

class Filosof_kafedra : public audience
{
  string dezhurn;
public:
  Filosof_kafedra();
  void show()
  {
    cout << name << " – вмест. аудит. Каф. философии " << endl;
    cout << "кол-во стендов:  " << dezhurn << endl;
  }
};

Filosof_kafedra::Filosof_kafedra() : audience()
{
  cout<<endl;
    cout<<" вмест. аудит. Каф. философии:  "; 
    cin >> name;
    Filosof_kafedra::name=name;
    while(1)
    {
      try
      {
        cout<<"Enter FIO Dezhurnogo(от 3 до 15):  "; 
        string name;
        cin >> name;
        int j=name.length();
          for( int i = 0; i < j; i++)
          if(name[i] == '0' || name[i] == '1' || name[i] == '2' || name[i] == '3'|| name[i] == '4' || name[i] == '5' || name[i] == '6' || name[i] == '7' || name[i] == '8' || name[i] == '9')
            throw empty();
          if(name.length()>20 || name.length()<3)
          throw 1;
        dezhurn=name;
        amount++;
        return;
      }
     catch (int)
      {
          cout << "Введено неверное количество\n";
      }
      catch(class empty)
      {
          cout << "В поле для букв введены цифры\n";
      }
    }
}

class Phys_kafedra : public audience
{
public:	
	Phys_kafedra();
	void show()
	{
		cout << name << " - вмест. аудит. Каф. физики " << endl;
	}
};

Phys_kafedra::Phys_kafedra() : audience()
{
    cout<<endl;
    cout<<" вмест. аудит. Каф. физики:  "; 
    cin >> name;
	Phys_kafedra::name=name;
  	amount++;
}

audience::audience()
{
	cout<<endl;
    cout<<"конструктор ";
}

int main()
{
	audience *A[3];
  A[0]=new Mat_kafedra();
  A[1]=new Phys_kafedra();
  A[2]=new Filosof_kafedra();
  for(int a=0;a<3;a++)
  {
    A[a]->Print();
  }
  return 0;
}
