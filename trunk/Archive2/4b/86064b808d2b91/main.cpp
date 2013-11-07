#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Cat {
    string name;
    int age;
};

struct Pencil {
    float sharpness;
    float length;
};

struct ListOfThings {
    enum Type {
    CatList,
	PencilList
    }type;
    void *listData;
};

int main()
{
    vector<Cat> cats;
    cats.push_back({"Joey", 4});
    cats.push_back({"Mitzi", 6});
    cats.push_back({"Garfield", 10});
    vector<Pencil> pencils;
    pencils.push_back({1.0f, 17.6f});
    pencils.push_back({0.6f, 12.1f});
    pencils.push_back({1.6f, 24.6f});
    pencils.push_back({0.2f, 18.0f});
    vector<ListOfThings> myThings;
    myThings.push_back({ListOfThings::CatList, &cats});
    myThings.push_back({ListOfThings::PencilList, &pencils});
    
    cout << "Hey look, I just found the lists of the things I own. I made them a while ago. Let's take a look at them!\n\n";
    
    for (const ListOfThings& list : myThings) {
	if (list.type == ListOfThings::CatList) {
	    cout << "Ahh... A list of cats... curious...\n";
	    for (const Cat& cat : *static_cast<vector<Cat>*>(list.listData))
		cout << cat.name << ", age: " << cat.age << '\n';
	}
	else if (list.type == ListOfThings::PencilList) {
	    cout << "Hmm... A bunch of pencils...\n";
	    for (const Pencil& pencil : *static_cast<vector<Pencil>*>(list.listData)) {
		cout << "sharpness: " << pencil.sharpness << ", length: " << pencil.length << '\n';
	    }
	}
    }
}