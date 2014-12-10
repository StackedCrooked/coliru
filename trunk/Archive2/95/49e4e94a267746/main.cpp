#include <iostream>

#include <fstream>

#include <iomanip>

#define FILENAME "PERSFILE.DAT"
#define ROWNUM     20 //максимально число строк в файле 

using namespace std;

/*
при запуске необходимо для консоли указать шрифт Lucida Console 
прав кнопкой мышы на форме -> настройка -> шрифты
*/
//#pragma warning(disable : 4996)

class Hotel
{
	char *_name;
	char *_adress;

	short  _starNum;
	short  _placeNum;

	double _costRoom;

public :
	Hotel()
	{
		_name = new char[1];
		_name[0] = '\0';

		_adress = new char[1];
		_adress[0] = '\0';

		_starNum = 1;
		_placeNum = 1;
	}

	Hotel(char* pname, char *padress,int pstarnum,int pleacenum,int pcost)
	{
		int len= 0;

		len = strlen(pname);
		_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';

		len = strlen(padress);
		_adress = new char[len+1];
		strcpy(_adress,padress);
		_adress[len] = '\0';

		_starNum = pstarnum;

		_placeNum=pleacenum;
		_costRoom=pcost;
	}

	Hotel(const Hotel & object)
	{
		
		int len = strlen(object._name);
		_name = new char[len+1];
		strcpy(_name,object._name);
		_name[len] = '\0';

		len = strlen(object._adress);
		_adress = new char[len+1];
		strcpy(_adress,object._adress);
		_adress[len] = '\0';

		_starNum = object._starNum;

		_placeNum=object._placeNum;
		_costRoom=object._costRoom;
	}

	Hotel& operator=(const Hotel& other)
    {
		Hotel tmp(other);
    
		return *this;
    }

	~Hotel()
	{
		// если память была выделена
		if(_name != NULL)
		{
			// освободить
			delete []_name;
		}

		if(_adress != NULL)
		{
			delete []_adress;
		}
	}

	//void Write(Hotel pValue,char *pFileName);
	// чтение из файла
	void diskIn(int pn) 
	{

	}

	void diskOut();          // запись в файл
    static int diskCount();  // Число человек в файле
	
	//вывод данных
	friend ostream &operator<< (ostream &stream,Hotel o);		
	//ввод данных
	friend istream &operator>>(istream &stream,Hotel &o);

};

int currLineNum;

///количество записей в файле
int Hotel::diskCount()
{
	ifstream infile;
    infile.open(FILENAME, ios::binary);
    infile.seekg(0, ios::end); // перейти на позицию «0 байт
                             // от конца файла»
                             // вычислить количество людей
   return (int)infile.tellg() / sizeof(Hotel);	
}

// выводит на экран имя и номер телефона
ostream &operator<< (ostream &stream,Hotel o)
{
	cout<<"hotel"<<endl;
	return stream;
}

istream &operator>>(istream &stream,Hotel &o)
{
		cout<<"Введите название :"<<endl;
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();
		cin>>o._name;		
		
		
		cout<<"Введите адресс "<<endl;
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();
		cin>>o._adress;

		int lYear;
		cout<<"Введите количество звезд"<<endl;
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();
		// бывает всего 5 звезд
		cin>>setw(5)>>o._starNum;

		int lnum;
		cout<<"Стоимость "<<endl;
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();
		cin>>o._costRoom;
	
		currLineNum++;

	return stream;
}


Hotel HotelRecord[ROWNUM];



///записать на диск 
/// <param = pValue>Элемент который необходимо сохранить в файл </param>
/// <param = fileName > указатель на строку содержащую имя файла</param>
void Write(Hotel pValue,char *pFileName)
{
	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in | ios::binary);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(Hotel));

}


/// считать все записи из файла  
/// <param = fileName > указатель на строку содержащую имя файла</param>
void ReadInFile(char * pFileName)
{	
//	currLineNum =0;

	Hotel lplane;

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in | ios::binary);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	int i =0;
	// установить позицию курсора в начало
	file.seekg(0);
	//file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));

	while(!file.eof())
	{			
		// считать данные о следующем 

		HotelRecord[i] = lplane;
		i++;
		currLineNum++;

		file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
					
		cout<<"\n";
	}
}


//--------------------------------------
///запись в файл 
/// <param = fileName > указатель на строку содержащую имя файла</param>
void CreateTestRecord(char *fileName )
{
	//заново создаем файл 	
	ofstream out(fileName);  
    out.close();  
	
	Hotel hotel("Интурист","Ленина 1 ",4,5,300);

	// открываем для записи
	fstream file;
	//out Стирание и запись (файл создается, если его нет) “w”
	//app Дозапись (файл создается, если его нет) “a”
	//in|out Чтение и запись (файл должен существовать) “r+”
	file.open(fileName, ios::app| ios::out | ios::in | ios::binary);
 
    if(file == NULL)
    {
        cout << "Ошибка создания файла!";
		_getch();
        exit(1);
    }

    file.close(); 

	 Write(hotel,FILENAME);
}


/// отображение меню программы на дисплее
int  PrintMenu()
{
	int lshoose = 0;

	bool lfisrt = true;

	do
	{	
		//очишает состояние потока
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();

		if(!lfisrt)
		{
			cout<<"Некорректное значение - повторите попытку"<<endl;
		}
		
		cout<<"\n Выберите пункт меню :"<<endl;
		cout<<"1. Загрузить все записи."<<endl;
		cout<<"2. Просмотреть все текущие записи"<<endl;
		cout<<"3. Добавить запись "<<endl;
		cout<<"4. Загрузить из файла"<<endl;
		cout<<"5. Сортировать по году выпуска."<<endl;
		cout<<"6. Поиск данных по году выпуска."<<endl;	
		cout<<"9. Сохранение результатов в файл"<<endl;	
		cout<<"0. Выход"<<endl;

		cin>>lshoose;

		lfisrt = false;

	}while(lshoose< 0 || lshoose> 6 );

	return lshoose;
}

///вывыести данные на экран
void PrintCurrRow()
{
	cout<<"Hello world!"<<endl;
}



/// флаг - существует ли флаг 
bool isExist(char * pFileName)
{
   fstream file;

   file.open(pFileName);

	if(file == NULL)
    {
        return false;
    }

	return true;
}

int main ()
{
	setlocale(LC_ALL,"Russian");
	setlocale(LC_CTYPE,"Russian");
	

	Hotel hotel;
	 // если файла нету
	 if(!isExist(FILENAME))
	 {
		 //создаем файл с одной записью	
		 CreateTestRecord(FILENAME);	
	 }	


	// выбранный пункт меню
	int lshoose  =0;
	do
	{
		lshoose = PrintMenu();
		//загружаем данные из файла
		if(lshoose==1)
		{
			ReadInFile(FILENAME);
		}
		//вывести на экран 
		else if(lshoose==2)
		{
			PrintCurrRow();
		}

		// Добавить запись
		else if(lshoose==3)
		{			
			cin>>hotel;			
		}
		//Загрузить из файла
		else if(lshoose==4)
		{
			
		}
		//Сортировать по году выпуска.
		else if(lshoose==5)
		{
			
		}
		else if(lshoose==6)
		{
			
		}	
		//Сохранение результатов в файл
	    else if(lshoose==9)
		{
			for(int i =0;i<9;i++)
			{				
				Write(HotelRecord[i],FILENAME);
			}
		}


	}while(lshoose!=0);

	int a(10);

	cout<<"Введите любой символ для продолжения ....";
	
//	_getch();
	return 0;
}