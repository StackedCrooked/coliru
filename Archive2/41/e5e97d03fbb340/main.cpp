#include <iostream>
#include <string>
#include <vector>
class UnsortedType
{
Private:
int length;
int info[MAX_ITEMS];
int currentPos;

public: 
UnsortedType();
void MakeEmpty( );
bool IsFull( ) const;
bool IsEmpty( ) const;
int GetLength( ) const;
void RetrieveItem( int& item, bool& found );
void InsertItem( int item );
void DeleteItem( int item );
void ResetList( );
void GetNextItem( int& item );
};
UnsortedType::UnsortedType()
{
length = 0;
}
bool UnsortedType::IsFull()
{
return (length == MAX_ITEMS);
}
bool UnsortedType::IsEmpty()
{
return (length == 0);
}
void UnsortedType::InsertItem(int item)
{
info[length] = item;
length++;
}
void UnsortedType::RetrieveItem(int& item, bool& found)
{
bool moreToSearch;
int location = 0;
found = false;
moreToSearch = (location < length);
while (moreToSearch && !found){
if (info[location] == item){
found = true;
item = info[location];}
else {
location++;
moreToSearch = (location < length);
}
}
}
void UnsortedType::DeleteItem ( int item )
{
int location = 0 ;
while (info[location] != item)
location++;
info [location] = info [length - 1 ] ;
length-- ;
}
void PrintList(UnsortedType list)
{
int length;
int item;
list.ResetList();
length = list.GetLength();
for (int i = 1; i <= length; i++) {
list.GetNextItem(item);
cout << item << " ";
}
}
void UnsortedType::ResetList ( )
{
currentPos = -1 ;
}
void UnsortedType::GetNextItem ( int& item )
{
currentPos++ ;
item = info [currentPos] ;
}
int UnsortedType::GetLength( ) const
{
return length;}
int main()
{
UnsortedType list; int k;
for (int i=0; i<5; i++) {
cout << "enter an item: ";
cin >> k;
list.InsertItem(k);
}
list.PrintList();
cout << "\nItem to delete: ";
cin >> k;
list.DeleteItem(k);
list.PrintList();
system("pause");
return 0;
}