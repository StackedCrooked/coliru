struct KnuthSeq
{
	int operator()(int i)
	{
		return seqElems_[i];
	}

private:
	static uint seqElems_[20];
};

int KnuthSeq::seqElems_[20] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841,
	295214, 88573, 265720, 797161, 2391484, 7174453, 21523360, 64570081,
	193710244, 581130733, 1743392200};