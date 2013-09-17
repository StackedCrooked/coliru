#include <functional>
#include <vector>
#include <iostream>

struct IListener
{
    virtual void OnEvent(const char *) {}
	virtual void OnEventFail(int) {}
};

struct Sender
{
	typedef std::function<void(const char *)> EventCallback;
	std::vector<EventCallback> vCallback;
	std::vector<IListener *> vListener;


	void AddListener(IListener *l)
	{
		vListener.push_back(l);
	}

	void AddCallback(EventCallback cb)
	{
		vCallback.push_back(cb);
	}

	void AddCallback(IListener *l)
	{
		vCallback.push_back(std::bind(&IListener::OnEvent, l, std::placeholders::_1));
	}

	void SendEvent()
	{
		std::cout << " |- Dispatch to callbacks" << std::endl;
		{
			auto copy = vCallback;
			for (auto each: vCallback)
				each("an event");

			vCallback.clear();
		}
		std::cout << " |- Dispatch to listeners" << std::endl;
		{
			auto copy = vListener;
			for (auto each: vListener)
				each->OnEvent("an event");
		}
		std::cout << " \\- done." << std::endl << std::endl;
	}
};

void func_callback(const char *ev)
{
	std::cout << " |--(ev): func_callback() received event: " << ev << std::endl;
}

struct Intruder : public IListener
{
	virtual ~Intruder() {}

	void OnEvent(const char *ev) override
	{
		std::cout << " |--(ev): Intruder::OnEvent() received event: " << ev << std::endl;
	}
};

struct Listener : public IListener
{
	virtual ~Listener() {}

	void OnEvent(const char *ev) override
	{
		std::cout << " |--(ev): Listener::OnEvent() received event: " << ev << std::endl;
	}

	Listener()
	{
		Sender s;
		Intruder i;

		s.AddCallback([&](const char *ev)
		{
			std::cout << " |--(ev): <anonymous> received event: " << ev << " (redirect, inject) " << std::endl << " |     ";
			this->OnEvent(ev);

			std::cout << " |        <anonymous> adding intruder" << std::endl;
			s.AddListener(&i);
		});

		s.AddCallback(func_callback);
		s.AddCallback(this);
		s.AddListener(this);

		std::cout << "--- First Event" << std::endl;
		s.SendEvent();

		std::cout << "--- Second Event" << std::endl;
		s.SendEvent();
	}
};

int main(int, char **)
{
	Listener l;
	return 0;
}
