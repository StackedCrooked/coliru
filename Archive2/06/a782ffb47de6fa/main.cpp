#include<iostream .h>
#include<ctype .h>
#include<conio .h>
#include<stdio .h>
#include<string .h>
#include<iomanip .h>
#include<fstream .h>
#include<dos .h>
 
struct marks_criteria
{
int sc_min,com_min,arts_min, seat_sc, seat_com, seat_arts;
} crit;
 
struct administrator
{
    char user_name[10];
	char password[10];
}admin;
 
struct  student
{
char name[20];
int regno,m_eng,m_math,m_sc,m_sst,m_lang;
int pref_code, stream;
// Sc=1, Com=2; Arts=3;
 
 
	public:
		void new_file();
		void input_data();
		void allot_stream();
		int get_stream();
		void display();
		int show_per()
		{
			return((m_eng+m_math+m_sc+m_sst+m_lang)/5);
		}
 
};
void welcome();
void menu();
int verify_password();
void assign_user();
void clear();
void input_criteria();
void read_criteria();
void read_student();
void create_eligible_sc();
void create_eligible_com();
void create_eligible_arts();
void read_eligible_sc();
void read_eligible_com();
void read_eligible_arts();
char * stream_name(int strm);
void select_list( char *in_file, char *out_file);
void thanks();
 
student s;
void main()
{
 
 
	  clrscr();
	  welcome();
 
	 // cout< <"welcome";
fstream fin, fout;
fstream fsc, fcom, farts;
char opt='1', ch;
 
while(opt!='8')
{
	textmode(C80);
	textcolor(BLUE);
	textbackground(WHITE);
	clrscr();
	cout<<"\n\t======================  MAIN   MENU  =======================\n";
	cout<<"\n\t[1] CREATE / MODIFY ADMISSION CRITERIA(Administrator only)";
	cout<<"\n\n\t[2] ENTER STUDENT'S DATA ";
	cout<<"\n\n\t[3] ALLOTMENT OF  STREAM";
	cout<<"\n\n\t[4] DISPLAY CRITERIA FOR SELECTION";
	cout<<"\n\n\t[5] DISPLAY ALLOTMENT OF STUDENT'S STREAM";
	cout<<"\n\n\t[6] DISPLAY ALL STUDENT'S REGISTERED";
	cout<<"\n\n\t[7] CREATE / DISPLAY MERIT LIST";
	cout<<"\n\n\t[8] QUIT";
	cout<<"\n\t=============================================================\n";
	cout<<"\n\n\t\tEnter your  choice : ";
	opt=getche();
	switch(opt)
	{
	case '1':
			int p;
			assign_user();
			p=verify_password();
			if(p==0)
			{
 
				input_criteria();
			}
			else
			{
				cout<<"\n\tU R Not a Valid User.";
				cout<<"\n\tU Dont have the Authority to Create Question Bank. Bye\n\n";
			}
			break;
 
	case '2':
			 int option;
			 clrscr();
			 cout<<"\nWhat do u want --\n\n\n\n\n\tCreate  a new student information  file or Append to the existing file?\n\n\t(press 1 for new creation and 2 for appending)";
			 cin>>option;
			 if(option==1)
			 {
		  s.new_file();
		  }
		  else
		  {
		s.input_data();
		}
		break;
 
	case '3':
		clrscr();
		//	read_student();
		fin.open("student" ,ios::in|ios::out);
 
		fsc.open("elig_sc",ios::out);
		fcom.open("eligcom",ios::out);
		farts.open("eligart",ios::out);
 
		while(fin.read((char*)& s,sizeof(s)))
		{
 
 
				s.allot_stream();
 
				s.get_stream();
 
				//if(s.get_stream()==0)
						 cout< <"\nApplication Rejected. Not Eligible\n";
 
				if(s.get_stream()==1)
					fsc.write((char*)& s,sizeof(s));
 
 
				if(s.get_stream()==2)
					fcom.write((char*)& s,sizeof(s));
 
				if(s.get_stream()==3)
					farts.write((char*)& s,sizeof(s));
 
 
 
		}
		fin.close();
		fsc.close();
		fcom.close();
		farts.close();
		cout<<"\n\n\n\n\n";
		cout<<"\n*******************************************";
		cout<<"\n\n\tSTREAM ALLOCATION DONE.";
		cout<<"\n*******************************************";
      getch();
		break;
	case '4':
		read_criteria();
	//	clear();
		cout<<"\n Sc  : "<<crit.sc_min;
		cout<<"\n Com : "<<crit.com_min;
		cout<<"\n Sc  : "<<crit.arts_min;
 
		 getch();
		break;
 
	case '5':
 
		cout<<"\n Enter [1] for Sc, [2] for Com, [3] for Arts  :  ";
		ch=getche();
		if (ch=='1')
			{
			read_eligible_sc();
			getch();
	 }
		if (ch=='2')
			{
			read_eligible_com();
			getch();
			}
		if (ch=='3')
			{
			read_eligible_arts();
			getch();
			}
		break;
	case '6':         clrscr() ;
			read_student();
			getch();
			break;
	case '7':
		{
			char c;
			char k;
			cout<<"\n****************************************";
			cout<<"\n****************************************";
			cout<<"\n       M E R I T  L I S T";
			cout<<"\n       ==================";
			cout<<"\n\tEnter 1 for MERIT LIST SCIENCE ";
			cout<<"\n\tEnter 2 for MERIT LIST COMMERCE ";
			cout<<"\n\tEnter 3 for MERIT LIST ARTS \t";
			cout<<"\n****************************************";
			cout<<"\n****************************************";
			k=getch();
			if (k=='1')
			{
				select_list("elig_sc","sell_sc");
				fin.open("sell_sc",ios::in);
				getch();
			}
			if (k=='2')
			{
				select_list("eligcom","sellcom");
				fin.open("sellcom",ios::in);
				getch();
			}
			if (k=='3')
			{
				select_list("eligart","sellart");
				fin.open("sellart",ios::in);
				getch();
			}
			if(k>='1' && k< ='3')
			{
				while(fin.read((char*)& s,sizeof(s)))
				{
					s.display();
 
					cout<<"\n\t Continue (y/n)? : ";
						c=getche();
					c=tolower(c);
					if(c=='n')
						break;
 
				}
 
			}
			fin.close();
			fin.close();
			fin.close();
		break;
		}
	case '8':
		thanks();
		 //	cout<<"\nTHANKS BYE ";
		 //	exit(0);
		break;
	}
 
		}
 
 }
 
// END OF WHILE
 
 
void	assign_user()
{
 
	strcpy(admin.user_name, "abhisek");
	strcpy(admin.password, "nokia");
 
 
}
int verify_password()
{
	char u_name[10];
	char u_pwd[10],temp[2];
	int x=1;
	cout<<"\n\n   Enter user name : ";
	cin>>u_name;
	cout< <"\n\n   Enter Password : ";
	cin>>u_pwd;
	x=strcmp(admin.user_name,u_name);
	if (x==0)
	{
		x=strcmp(admin.password,u_pwd);
 
	}
	cin.getline(temp,2);
	return(x);
 
}
void student::allot_stream()
{
	int	per=(m_eng+m_math+m_sc+m_sst+m_lang)/5;
	read_criteria();
 
	switch(pref_code)
	{
		case 1:
				if(per>=crit.sc_min)
					stream=pref_code;
				else
					stream=0;
 
				break;
		case 2:
				if(per>=crit.com_min)
					stream=pref_code;
				else
					stream=0;
				break;
		case 3:
				if(per>=crit.arts_min)
					stream=pref_code;
				else
					stream=0;
				break;
	}
}
 
int student::get_stream()
{
	return(stream);
}
 
 
void input_criteria()
{
	fstream fout;
	fout.open("criteria" ,ios::in|ios::out);
	cout< <"\nEnter  the  required marks for SCIENCE stream (in percentage) : ";
	cin>>crit.sc_min;
	cout< <"\nEnter  No. of Seats for SCIENCE stream : ";
	cin>>crit.seat_sc;
	cout< <"\nEnter  the  required marks for COMMERCE stream(in percentage) : ";
	cin>>crit.com_min;
	cout< <"\nEnter  No. of Seats for COMMERCE stream :";
	cin>>crit.seat_com;
	cout< <"\nEnter  the  required marks for ARTS stream(in percentage) : ";
	cin>>crit.arts_min;
	cout< <"\nEnter  No. of Seats for ARTS stream : ";
	cin>>crit.seat_arts;
	fout.write((char*)& crit,sizeof(crit));
	fout.close();
}
 
void read_criteria()
{
	fstream fin;
	fin.open("criteria" ,ios::in);
	fin.read((char*)& crit,sizeof(crit));
	fin.close();
 
}
 
void student::input_data()
{     clrscr();
	fstream fin;
	fin.open("student",ios::app|ios::out);
	char t[2], ans;
	while(1)
	{
	cout< <"\nEnter  the  name of the  student  : ";
	gets(name);
	cout<<"\n\nEnter  the roll of the  student : ";
	cin>>regno;
	cout< <"\n\nEnter  marks in eng      : ";
	cin>>m_eng;
	cout< <"\n\nEnter  marks in math     : ";
	cin>>m_math;
	cout< <"\n\nEnter  marks in science  : ";
	cin>>m_sc;
	cout< <"\n\nEnter  marks in sst      : ";
	cin>>m_sst;
	cout< <"\n\nEnter  marks in language : ";
	cin>>m_lang;
	clrscr();
	cout< <endl<<endl<<endl<<endl;
	cout<<"================= STREAM  PREFERED ? ============== \n";
	cout<<"\t"<<"[1] for SCIENCE\n";
	cout<<"\t"<<"[2] for COMMERCE\n";
	cout<<"\t"<<"[3] for ARTS ";
	cout<<"\n================================================= \n\tENTER PREFERENCE CODE : ";
	cin>>pref_code;
	stream=-1;
	fin.write((char*)&s,sizeof(s));
	cin.getline(t,2);
	cout< <"\n\tEnter More Student ? (y/n) : ";
		ans=getche();
		ans=tolower(ans);
	if (ans=='n')
		break;
	}
	fin.close();
}
void student::new_file()
{     clrscr();
	fstream fin;
	fin.open("student",ios::out);
	char t[2], ans;
	while(1)
	{
	cout<<"\nEnter  the  name of the  student  : ";
	gets(name);
	cout<<"\n\nEnter  the roll of the  student : ";
	cin>>regno;
	cout< <"\n\nEnter  marks in eng      : ";
	cin>>m_eng;
	cout< <"\n\nEnter  marks in math     : ";
	cin>>m_math;
	cout< <"\n\nEnter  marks in science  : ";
	cin>>m_sc;
	cout< <"\n\nEnter  marks in sst      : ";
	cin>>m_sst;
	cout< <"\n\nEnter  marks in language : ";
	cin>>m_lang;
	clrscr();
	cout< <endl<<endl<<endl;
	cout<<"================= STREAM  PREFERED ? ============== \n";
	cout<<"\t"<<"[1] for SCIENCE\n";
	cout<<"\t"<<"[2] for COMMERCE\n";
	cout<<"\t"<<"[3] for ARTS ";
	cout<<"\n================================================= \n\tENTER PREFERENCE CODE : ";
	cin>>pref_code;
	stream=-1;
	fin.write((char*)&s,sizeof(s));
	cin.getline(t,2);
	cout< <"\n\tEnter More Student ? (y/n) : ";
		ans=getche();
		ans=tolower(ans);
	if (ans=='n')
		break;
	}
	fin.close();
}
void student::display()
{
 
	cout<<"\n============================================\n";
	cout<<"\n\tNAME		       : "<<name;
	cout<<"\n\tREGISTRATION NO.    : "<<regno;
	cout<<"\n\tPERCENTAGE OF MARKS : "<<( (m_eng+m_math+m_sc+m_sst+m_lang)/5)<<"%";
	cout<<"\n\tSTREAM APPLIED FOR  : "<<stream_name(pref_code);
       //	cout<<"\n\tSTREAM ALLOTED	: "<<stream_name(stream);
	cout<<"\n============================================\n";
 
}
 
void read_student()
{
	fstream fin;
	fin.open("student" ,ios::in);
	while(fin.read((char*)& s,sizeof(s)))
	{
			s.display();
			cout<<"\n\tPress any key to continue... ";
			getch();
			cout<<"\n";
	}
	fin.close();
 
}
 
 
 
void read_eligible_sc()
{
	char ans;
	fstream fout;
	fout.open("elig_sc",ios::in);
	fout.seekg(0);
	while(fout.read((char*)& s,sizeof(s)))
	{
		s.display();
		cout<<"\n\t Continue (y/n) ? : ";
 
		ans=getche();
		ans=tolower(ans);
		if (ans=='n')
			break;
 
	}
	fout.close();
 
}
 
void read_eligible_com()
{
	char ans;
	fstream fout;
	fout.open("eligcom",ios::in);
 
	while(fout.read((char*)& s,sizeof(s)))
	{
		s.display();
		cout<<"\n\t Continue (y/n)? : ";
 
		ans=getche();
		ans=tolower(ans);
		if (ans=='n')
			break;
 
	}
	fout.close();
}
 
 
 
void read_eligible_arts()
{
		char ans;
	fstream fout;
	fout.open("eligart",ios::in);
 
	while(fout.read((char*)& s,sizeof(s)))
	{
		s.display();
		cout<<"\n\t Continue (y/n) ? : ";
 
		ans=getche();
		ans=tolower(ans);
		if (ans=='n')
			break;
 
	}
	fout.close();
}
void clear()
{
//	for(int i=1;i<=24;i++)
	//	cout<<"\n";
}
char * stream_name(int strm)
{
	switch(strm)
	{
	case -1:
		return("Not assigned");
	    //	break;
	case 0:
		return("Nill");
	     //	break;
	case 1:
		return("Science");
	  //	break;
	case 2:
		return("Commerce");
	     //	break;
	case 3:
		return("Arts");
	    //	break;
	    default:
		return("None");
	}
}
void select_list( char *in_file, char *out_file)
{
	fstream sel, fin;
	int n=0, i,j;
	student sl[100], t;
 
 
		sel.open(out_file, ios::out);
		fin.open(in_file,ios::in);
 
		while(fin.read((char*)& sl[n],sizeof(s)))
		{
			n++;
 
		}
		cout<<"\nNo of Eligible Students = "<<n<<"\n";
		for(i=0;i<n;i++)
		{
			for(j=i+1;j<=n;j++)
			{
				if ( sl[i].show_per()<sl[j].show_per())
				{
					t=sl[j];
					sl[j]=sl[i];
					sl[i]=t;
				}
			}
		}
		for(i=0;i<n;i++)
		{
			sel.write((char*)& sl[i],sizeof(s));
		}
	sel.close();
	fin.close();
 
}
void thanks()
	{
		clrscr();
		cout<<"\n\n\n\n\n\n\n\n\n\n\t**********   T H A N K   Y O U   F O R   W O R K I N G   *******";
		cout<<"\n\n\n\n\n\n\n\t\t\t                        press any key to exit";
		getch();
	}
void welcome()
	{
	textmode(C40);
	textbackground(BLACK);
	textcolor(MAGENTA);
	clrscr();
	cout<<endl<<endl<<endl<<endl;
	cout<<"\n\n           *** WELCOME TO ***";
	cout<<endl;
	cout<<"\n\n COMPUTER PROJECT ON STREAM ALLOATMENT";
	cout<<"\n\n BY :\n";
	cout<<"\n  #  ABHISEK DE        XII 'Sc'     #";
	cout<<"\n  #  SOUVIK PODDER     XII 'Sc'     #";
	cout<<"\n  #  ARNAB SEN         XII 'Sc'     #";
	cout<<"\n  #  ARKA KUNDU        XII 'Sc'     # ";
	cout<<"\n\n\n\npress any key to continue...";
	getch();
 
	}

