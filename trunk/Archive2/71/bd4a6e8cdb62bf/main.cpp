class add_modes
{
public:
    typedef function<void(const int, const string&)> PT;
	typedef vector<pair<int, pair<string, PT>>> Modes;
private:
	Modes& m;
public:
	add_modes(Modes& m):m(m) { }
	add_modes& operator()(const int i, const string& n, PT f)
	{
		m.push_back(make_pair(i, make_pair(n, f)));
		return *this;
	}
};

//вызов обработчика
try
    {
		const auto m = m_m.at(id);
		m.second.second(m.first, m.second.first);
	}
	catch(out_of_range&)
	{
		return;
	}