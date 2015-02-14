#include <assert.h>
#include <iostream>
#include <functional>
#include <string>
#include <limits>
#include <memory>
#include <unordered_map>
#include <functional>

using namespace std;

class Unique
{
private:

    string m_Name;

public:

	typedef shared_ptr<Unique> Ptr;

	string GetName()
	{
		return m_Name;
	}

	void SetName(string name)
	{
		m_Name = name;
	}

};

class SignalSender : public Unique
{
private:

	string m_Data;

public:

	typedef shared_ptr<SignalSender> Ptr;

	static Ptr Create(string name, string data)
	{
		auto ptr = make_shared<SignalSender>();
		ptr->SetName(name);
		ptr->SetData(data);
		return ptr;
	}

	string GetData()
	{
		return m_Data;
	}

	void SetData(string data)
	{
		m_Data = data;
	}
};

class Signal : Unique
{
private:

	unordered_map<
		string, 
		pair<weak_ptr<Unique>, function<void(SignalSender::Ptr)>>
	> m_Listeners;

public:

	typedef shared_ptr<Signal> Ptr;

	static Ptr Create(string name);

	virtual ~Signal();

	template<typename Reciver>
	void Connect(Unique::Ptr reciver, void(Reciver::*method)(SignalSender::Ptr));

	void Disconnect(Unique::Ptr reciver);

	void Clear();

	void Emit(SignalSender::Ptr sender);
};

Signal::Ptr Signal::Create(string name)
{
	auto ptr = make_shared<Signal>();
	ptr->SetName(name);
	return ptr;
}

Signal::~Signal()
{
	Clear();
}

template<typename Reciver>
void Signal::Connect(Unique::Ptr reciver, void(Reciver::*method)(SignalSender::Ptr))
{
	Unique* pReciver = reciver.get();
	string name = GetName() + reciver->GetName();

	if(m_Listeners.find(name) == m_Listeners.end())
	{
		m_Listeners.insert
		(
			make_pair
			(
				name, 
				make_pair< weak_ptr<Unique>, function<void(SignalSender::Ptr)>>
				(
					reciver, 
					[pReciver, method](SignalSender::Ptr sender){(static_cast<Reciver*>(pReciver)->*method)(sender);}
				)
			)
		);
	}
	else
	{
		// name conflict, stop then ..
		assert(false);
	}
}

void Signal::Disconnect(Unique::Ptr reciver)
{
	m_Listeners.erase(GetName() + reciver->GetName());
}

void Signal::Clear()
{
	m_Listeners.clear();
}

void Signal::Emit(SignalSender::Ptr sender)
{
	cout<<"===================================="<<endl;
	cout<<"Emit: "<<endl;
	// for each listener, call(sender).
	for(auto it = m_Listeners.begin(); it != m_Listeners.end();)
	{
		if(!it->second.first.expired())
		{
			// reciver alive, continue .. 
			it->second.second(sender);
			++it;
		}
		else 
		{
			// reciver dead, erase .. 
			it = m_Listeners.erase(it);
		}
	}
	cout<<"===================================="<<endl;
}

class SignalReciver : public Unique
{
public:

	typedef shared_ptr<SignalReciver> Ptr;

	static Ptr Create(string name)
	{
		auto ptr = make_shared<SignalReciver>();
		ptr->SetName(name);
		return ptr;
	}

	virtual void Callback(SignalSender::Ptr sender)
	{
		cout<<GetName()<<" recives '"<<sender->GetData()<<"' from "<<sender->GetName()<<endl;
	}
};

int main()
{
	SignalReciver::Ptr SR0 = SignalReciver::Create("SR0");
	SignalReciver::Ptr SR1 = SignalReciver::Create("SR1");
	SignalReciver::Ptr SR2 = SignalReciver::Create("SR2");

	SignalSender::Ptr SC0 = SignalSender::Create("SC0", "Hello there!");

	Signal::Ptr S0 = Signal::Create("Signal0");

	S0->Connect(SR0, &SignalReciver::Callback);
	S0->Connect(SR1, &SignalReciver::Callback);
	S0->Connect(SR2, &SignalReciver::Callback);

	S0->Emit(SC0);

	S0->Disconnect(SR0);

	S0->Emit(SC0);

	S0->Connect(SR0, &SignalReciver::Callback);

	SR0.reset();
	SR1.reset();

	S0->Emit(SC0);
	
	cout << "Press ENTER to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return 0;
}