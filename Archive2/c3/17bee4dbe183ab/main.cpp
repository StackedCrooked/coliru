#include <iostream>
#include <thread>
#include <list>
#include <functional>
#include <chrono>
using namespace std;

void outputToSomeContainer(int val, list<int>& result){
   result.push_back(val);
}

class async{
	list<thread> a;
public:
	async(){}
	async(async&& a): a(move(a.a))
	{}
	void addTask(function<void()>&&f){
		a.emplace_back(move(f));
	}
	void wait(){
		for(auto&& i: a)
			i.join();
	}
};

async async_O_n_Sort(const list<char>& unsorted, function<void(int)> outputToContainer){
	async a;
	for(int i: unsorted)//O(n)
		a.addTask([i, outputToContainer](){this_thread::sleep_for(chrono::milliseconds(5+i*10));outputToContainer(i);});
	return a;
}

int main() {
	list<char> unsorted {1, 0, 6, 3, 4};
    list<int> sorted;
	auto a = async_O_n_Sort(unsorted, bind(outputToSomeContainer, placeholders::_1, ref(sorted)));
	cout<<"А мы веселые пельменья, мы похоже на варенья"<<endl;
	a.wait();
    for(int i: sorted)
        cout<<i<<endl;
	return 0;
}