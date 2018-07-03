 #include <stdio.h>
 #include <stdlib.h>
typedef struct {
	int setpoint;
	int t;
	int U;
	int dt;
	int K_p;
	int K_i;
	int K_d;
	int out;
	int integral;
}PID_st_t;

PID_st_t PID_st;
PID_st_t* P_PID=&PID_st; 

int main(int point)
{

int pre_error =0;

for(int i = 0; i<sizeof(P_PID->t); i++)
{
P_PID->integral += (P_PID->setpoint - point) * P_PID->dt;

P_PID->U =  P_PID->K_p * P_PID->setpoint - point
				+ 
				P_PID->K_i * P_PID->integral
				+ 
				(((P_PID->setpoint - point) - pre_error) * P_PID->K_d) / P_PID->dt;

pre_error = P_PID->setpoint - point;
}

return P_PID->U;
}
