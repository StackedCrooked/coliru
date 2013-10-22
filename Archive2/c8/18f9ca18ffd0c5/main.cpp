#include <iostream>
using namespace std;
class Very_Strange_Elevator{
public:
    int value;
	Very_Strange_Elevator(int init){
		value=init;
	}
	int up(int summand){
		for(;summand>0;summand--)
			value+=(value==0?2:1);
		return value;
	}
	int down(int subtractor){
		for(;subtractor>0;subtractor--)
			value-=(value==0?2:1);
		return value;
	}
	int teleport(int newValue){
		return value=newValue;
	}
};
int main(void){
	int init,down,up; cin>>init>>down>>up;

	Very_Strange_Elevator vSE(init);
	vSE.down(down);
	vSE.up(up);
	cout<<vSE.value;

	return 0;
}