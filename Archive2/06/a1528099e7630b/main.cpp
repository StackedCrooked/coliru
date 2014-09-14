#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
	srand(unsigned(time(0)));

//------------------------------------()

	int *pointerN = new int;
	if (!pointerN) exit(0);

	cout << "Введите N :";
	cin >> *pointerN;

	int *pointerM = new int;
	if (!pointerM) exit(0);

	cout << "Введите M :";
	cin >> *pointerM;

//---------------------------------------()

	int *massivA = new int[*pointerN];
	if (!massivA) exit(0);

	int *massivB = new int[*pointerM];
	if (!massivB) exit(0);

//----------------------------------------(инициализация)

	for (int i = 0; i < *pointerN; i++)
	{
		massivA[i] = rand() % 100;
		cout << massivA[i] << '\t';
	}
	cout << endl << endl;

	for (int i = 0; i < *pointerM; i++)
	{
		massivB[i] = rand() % 100;
		cout << massivB[i] << '\t';
	}
	cout << endl << endl;

//---нужно собрать: Элементы обоих массивов------------------------------(1)

	int *massivC = new int[*pointerN + *pointerM];
	if (!massivC) exit(0);

	for (int i = 0; i < *pointerN; i++)
		massivC[i] = massivA[i];

	for (int i = 0; i < *pointerM; i++)
		massivC[*pointerN + i] = massivB[i];

	for (int i = 0; i < *pointerN + *pointerM; i++)
		cout << massivC[i] << '\t';
	cout << endl << endl;

//---нужно собрать: Общие элементы двух массивов-------------------------(2)

	//int flag;
	//int size = 0;
	//for (int i = 0; i < *pointerN; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerM; j++)
	//	{
	//		if (massivA[i] == massivB[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (flag)
	//	{
	//		size++;
	//	}
	//}
	//for (int i = 0; i < *pointerM; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerN; j++)
	//	{
	//		if (massivB[i] == massivA[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (flag)
	//	{
	//		size++;
	//	}
	//}

	//if (!size)
	//{
	//	cout << "нет совпадающих элементов массива" << endl << endl;
	//	exit(0);
	//}

	//int *massivC = new int[size];
	//if (!massivC) exit(0);

	//int move = 0;
	//for (int i = 0; i < *pointerN; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerM; j++)
	//	{
	//		if (massivA[i] == massivB[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (flag)
	//	{
	//		massivC[move] = massivA[i];
	//		move++;
	//	}
	//}
	//for (int i = 0; i < *pointerM; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerN; j++)
	//	{
	//		if (massivB[i] == massivA[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (flag)
	//	{
	//		massivC[move] = massivB[i];
	//		move++;
	//	}
	//}


	//for (int i = 0; i < size; i++)
	//	cout << massivC[i] << '\t';
	//cout << endl << endl;

//---нужно собрать: Элементы массива A, которые не включаются в B--------(3)

	//int flag;
	//int size = 0;
	//for (int i = 0; i < *pointerN; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerM; j++)
	//	{
	//		if (massivA[i] == massivB[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		size++;
	//	}
	//}

	//int *massivC = new int[size];
	//if (!massivC) exit(0);

	//int move = 0;
	//for (int i = 0; i < *pointerN; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerM; j++)
	//	{
	//		if (massivA[i] == massivB[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		massivC[move] = massivA[i];
	//		move++;
	//	}
	//}

	//for (int i = 0; i < size; i++)
	//	cout << massivC[i] << '\t';
	//cout << endl << endl;

//---нужно собрать: Элементы массива B, которые не включаются в A--------(4)

	//int flag;
	//int size = 0;
	//for (int i = 0; i < *pointerM; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerN; j++)
	//	{
	//		if (massivB[i] == massivA[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		size++;
	//	}
	//}

	//int *massivC = new int[size];
	//if (!massivC) exit(0);

	//int move = 0;
	//for (int i = 0; i < *pointerM; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerN; j++)
	//	{
	//		if (massivB[i] == massivA[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		massivC[move] = massivB[i];
	//		move++;
	//	}
	//}

	//for (int i = 0; i < size; i++)
	//	cout << massivC[i] << '\t';
	//cout << endl << endl;

//---нужно собрать: Элементы массивов A и B, коотрые не являются общими дял них----------(5)
	
	//int flag;
	//int size = 0;
	//for (int i = 0; i < *pointerN; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerM; j++)
	//	{
	//		if (massivA[i] == massivB[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		size++;
	//	}
	//}
	//for (int i = 0; i < *pointerM; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerN; j++)
	//	{
	//		if (massivB[i] == massivA[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		size++;
	//	}
	//}

	//if (!size)
	//{
	//	cout << "нет не совпадающих элементов массива" << endl << endl;
	//	exit(0);
	//}

	//int *massivC = new int[size];
	//if (!massivC) exit(0);

	//int move = 0;
	//for (int i = 0; i < *pointerN; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerM; j++)
	//	{
	//		if (massivA[i] == massivB[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		massivC[move] = massivA[i];
	//		move++;
	//	}
	//}
	//for (int i = 0; i < *pointerM; i++)
	//{
	//	flag = 0;
	//	for (int j = 0; j < *pointerN; j++)
	//	{
	//		if (massivB[i] == massivA[j])
	//		{
	//			flag = 1;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		massivC[move] = massivB[i];
	//		move++;
	//	}
	//}


	//for (int i = 0; i < size; i++)
	//	cout << massivC[i] << '\t';
	//cout << endl << endl;

	delete[] massivA;
	delete[] massivB;
	delete[] massivC;
	delete pointerN;
	delete pointerM;

    return 0;
}