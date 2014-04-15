#include <iostream>
#include <string>

struct tagKMC_MoveAbsolute;

/*------------------- kmcl_plcopenpart1 ------------------------------------------*/
/*! @defgroup kmcl_plcopenpart1 Motion library PLC Open Part 1
	This section describes functions covering PLC Open Part 1 technical specification.
	@{
*/

typedef int (*KMC_FMoveAbsoluteRun)(tagKMC_MoveAbsolute*);

//! \brief
//! Defines the MC_MoveAbsolute function block instance.
typedef struct tagKMC_MoveAbsolute
{
    KMC_FMoveAbsoluteRun f;
} KMC_MoveAbsolute;

int foo(tagKMC_MoveAbsolute*)
{
    std::cout << "It works" << std::endl;
    return 1;
}

int main()
{
    KMC_MoveAbsolute test = {foo};
    
    test.f(&test);
}
