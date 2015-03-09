#include <graphics.h>
#include <conio.h>
#include <mylib.h>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

int Thoat();

/*=========================================================================*/
int main_menu()
{
    //Thanh phan cua menu
	string Menu[] = {
		" 1.Nhap day so nguyen ",
		" 2.Tao day so ngau nhien ",
		" 3.Liet ke day so ra man hinh ",
		" 4.Xoa phan tu trong day so ",
		" 5.Loc phan tu trung nhau ",
		" 6.Sap xep day ",
		" 7.Ghi day so ra file text ",
		" 8.Load du lieu tu file text vao bo nho ",
		" 9.Kiem tra day so tang dan ",
		" 10.Them phan tu X day so van tang dan ",
		" 11.THOAT "	
	};
	
	int p=0, x=15, y=3, SoChucNang=11;
	int mauChuHien=0, mauNenHien=11, mauChuMD=15, mauNenMD=0;
	
	while(1)
	{
		XoaManHinh();
		BackGroundColor(mauNenMD);
		TextColor(mauChuMD);
		gotoxy(30,1); cout<<"MAIN MENU";
		//In menu va thiet lap mau sac
		for (int i = 0; i < SoChucNang; ++i)
		{
			gotoxy(x,y+i);
			if (i == p)
			{
				BackGroundColor(mauNenHien);
				TextColor(mauChuHien);
				cout << Menu[i] << endl;
			}
			
			else
			{
				BackGroundColor(mauNenMD);
				TextColor(mauChuMD);
				cout << Menu[i] << endl;
			}
		}
		//Thiet lap mau ve mac dinh
		BackGroundColor(mauNenMD);
		TextColor(mauChuMD);
		
		//Thiet lap Up/Down/Enter/Escape
		while(1)
		{
			if (GetAsyncKeyState(VK_UP) != 0)	//Up
			{
				p -= 1;
				if (p == -1)
				{
					p = SoChucNang-1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)	//Down
			{
				p += 1;
				if (p == SoChucNang)
				{
					p = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)	//Enter
			{
				XoaManHinh();
				switch(p)
				{
					case 0: cout<<"Nhap day so nguyen"; break;
					case 1: cout<<"Tao day so ngau nhien"; break;
					case 2: cout<<"Liet ke day so ra man hinh"; break;
					case 3: cout<<"Xoa phan tu trong day so"; break;
					case 4: cout<<"Loc phan tu trung nhau"; break;
					case 5: cout<<"Sap xep day"; break;
					case 6: cout<<"Ghi day so ra file text"; break;
					case 7: cout<<"Load du lieu tu file text vao bo nho"; break;
					case 8: cout<<"Kiem tra day so tang dan"; break;
					case 9: cout<<"Them phan tu X day so van tang dan"; break;
					case 10: return Thoat(); break;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE) != 0) return Thoat(); break;	//Escape
		}
		Sleep(150);
	}
}

//Xu ly thoat chuong trinh
int Thoat()
{
	XoaManHinh();
	string chon[] = { " KHONG ", " CO "};
	int m=0 ;
	int mauChu=0, mauNen=11, ChuMD=15, NenMD=0;
	while(1)
	{
		BackGroundColor(NenMD);
		TextColor(ChuMD);
		gotoxy(25,2); cout<<"BAN MUON THOAT CHUONG TRINH?";
		
		//In menu va thiet lap mau sac
		gotoxy(33,4);
		for (int i = 0; i < 2; ++i)
		{	
			if (i == m)
			{
				BackGroundColor(mauNen);
				TextColor(mauChu);
				cout << chon[i] ;
			}
			else
			{
				BackGroundColor(NenMD);
				TextColor(ChuMD);
				cout << chon[i] ;
			}
		}
		//Thiet lap mau ve mac dinh
		BackGroundColor(NenMD);
		TextColor(ChuMD);
		
		//Thiet lap Left/Right/Enter
		while(1)
		{
			if (GetAsyncKeyState(VK_LEFT) != 0)	//Left
			{
				m -= 1;
				if (m == -1)
				{
					m = 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RIGHT) != 0)	//Right
			{
				m += 1;
				if (m == 2)
				{
					m = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)	//Enter
			{
				switch (m)
				{
					case 0: main_menu(); break;
					case 1: return 0; break;
				}
			}
			break;
		}
		Sleep(150);
	}
}

int main()
{
	fflush(stdin);
	main_menu();
}