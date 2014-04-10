#include "udf.h"

DEFINE_CG_MOTION(gear2, dt, vel, omega, time, dtime)
{
Domain *domain;
domain = Get_Domain(1);
omega[2]=100.0;
}

DEFINE_CG_MOTION(gear1, dt, vel, omega, time, dtime)
{
Domain *domain;
domain = Get_Domain(1);
omega[2]=-100.0;
}
