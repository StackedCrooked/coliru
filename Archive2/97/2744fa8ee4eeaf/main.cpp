class Building {


    GroundFloor *groundfloor;
	Floor *floors[4];
	Lift *lift;

	int numVisitors;
	int maxCapacity;

	public:
	Building(int N, int Nf, int Ng, int No, int Nl) : maxCapacity(N), numVisitors(0) {
		groundfloor = new GroundFloor(Ng);
		for (int i=0;i<4;i++)
			floors[i] = new Floor(Nf, No, i+1);
		lift = new Lift(Nl,groundfloor,floors);
		cout << "A new building is ready for serving citizens!" << endl;
	}
	~Building() {
		delete groundfloor;
		for (int i=0;i<4;i++)
			delete floors[i];
		delete lift;
		cout << "Service not available any longer. Go elsewhere!" << endl;
	}
};