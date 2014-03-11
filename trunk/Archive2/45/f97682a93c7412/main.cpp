#include "a4p3.cc"

int main() {
    SBL sbl;
	SBL_init(sbl);
	assert(SBL_empty(sbl));

	SBL_arrive("a3", sbl);
	SBL_arrive("a8", sbl);
	SBL_arrive("a7", sbl);
	SBL_arrive("c3", sbl);
	SBL_arrive("a5", sbl);
	SBL_arrive("a1", sbl);
	SBL_arrive("a9", sbl);
	SBL_arrive("b3", sbl);
	SBL_arrive("a2", sbl);
	SBL_arrive("a4", sbl);

	//SBL_printInArrivalOrder(sbl);
	//std::cout << '\n';
	//SBL_printInAlphabeticalOrder(sbl);

	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);
	SBL_leave(sbl);

	SBL_printInAlphabeticalOrder(sbl);
	SBL_printInArrivalOrder(sbl);
	assert(SBL_empty(sbl));
}
