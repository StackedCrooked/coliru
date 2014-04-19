#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <functional>

class EventManager
{
public:
    template<class F>
    void AddClient(F client)
	{
		clients.emplace_back(new EventClient<F>(std::move(client)));
	}
	
	void Emit()
	{
		std::for_each(clients.begin(), clients.end(), [](auto& client){ client->Respond(); });
	}
	
private:
	struct IEventClient
    {
		virtual ~IEventClient() { }
		virtual void Respond() = 0;
	};
	
	template<class F>
	struct EventClient : IEventClient
	{
        F f;
		EventClient(F&& f) : f(std::move(f)) { }
		void Respond() override { f(); }
	};
	
	std::vector<std::unique_ptr<IEventClient>> clients;
};

struct Foo { void operator()() const { std::cout << "Foo\n"; } };

struct Bar { int operator()() { std::cout << "Bar\n"; return 0; } };

struct Baz
{
	Baz() { id = ID++; obj_valid = true; std::cout << "ctor(id=" << id << ")\n"; };
	~Baz() { std::cout << "dtor(id=" << id << ")\n"; obj_valid = false; };
	
	//Baz(const Baz& b) { id = b.id; obj_valid = b.obj_valid; std::cout << "cctor(id=" << id << ")\n"; };
	Baz(Baz&& b) { id = std::move(b.id); obj_valid = std::move(b.obj_valid); b.id = -1; b.obj_valid = false; std::cout << "mctor(id=" << id << ")\n"; };
    
    Baz(const Baz& b) = delete;
	Baz& operator=(const Baz&) = delete;
	
	void f(const std::string& s) const { std::cout << "Baz::f(\"" << s << "\", id=" << id << ", obj_valid=" << obj_valid << ")\n"; }	
	
	static int ID;
	int id{-1};
	bool obj_valid{false};
};

int Baz::ID;


int main()
{
	EventManager eventMan;

	eventMan.AddClient([]{ std::cout << "lambda\n"; });
    eventMan.AddClient(std::bind([](int i){ std::cout << "lambda+bind\n"; }, 1234));
	
	std::function<void()> f1 = []{ std::cout << "std::function\n"; };
	eventMan.AddClient(f1);
    
	std::function<double(double)> f2 = [](double d){ std::cout << "std::function+bind\n"; return d;};
    eventMan.AddClient(std::bind(f2, .5));
	
	eventMan.AddClient(Foo());
	eventMan.AddClient(Bar());

	eventMan.AddClient(std::bind(&Baz::f, Baz(), "baz_t")); // ctor and move
	eventMan.AddClient(std::bind(&Baz::f, std::make_shared<Baz>(), "baz_p")); // same with shared_ptr

	{
		//Baz baz; // ctor
		//eventMan.AddClient(std::bind(&Baz::f, baz, "baz_o")); // copy ctor and move
	}
	
	{
		Baz baz;
		eventMan.AddClient(std::bind(&Baz::f, std::move(baz), "baz_m")); // invokes copy ctor
	}
	
	{
		Baz baz;
		eventMan.AddClient(std::bind(&Baz::f, std::ref(baz), "baz_r")); // no copy, goes out of scope, UB
	}
	
	eventMan.Emit();
}