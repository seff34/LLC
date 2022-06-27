#include "formula.h"

double axd11 = 0.9703;
double axd12 = 9.8515 * (pow(10,(-5)));
double axd13 = 4.9257 * (pow(10,(-9)));
double axd21 = -2.9604;
double axd22 = 0.999;
double axd23 = 9.9993 * (pow(10,(-5)));
double axd31 = 4.9257 * (pow(10,(-9)));
double axd32 = -0.0049;
double axd33 = 1;

double bxd11 = -1.8314 * (pow(10,(-4)));
double bxd12 = 0.0297;
double bxd21 = -3.7178;
double bxd22 = 2.9604;
double bxd31 = 0.0092;
double bxd32 = 98.5149;

double z1 = 0;
double z2 = 0;
double z3 = 0;
double y = 0;
double u = 0;

double kd_dig = 200;
double kp_dig = 37500;

uint16_t MAX_FREQ_VALUE = 1500 ;
uint16_t MIN_FREQ_VALUE = 858 ;


double INTEGRAL_FORMULA(double VALUE){

	return VALUE;
}

double Z1_VALUE() {

    z1 = (z1 * axd11) + (z2 * axd12) + (z3 * axd13) + (u * bxd11) + (y * bxd12);
    z1 = INTEGRAL_FORMULA(z1);
    return z1;
}

double Z2_VALUE() {

    z2 = (z1 * axd21) + (z2 * axd22) + (z3 * axd23) + (u * bxd21) + (y * bxd22);
    z2 = INTEGRAL_FORMULA(z2);
    return z2;
}

double Z3_VALUE() {

    z3 = (z1 * axd31) + (z2 * axd32) + (z3 * axd33) + (u * bxd31) + (y * bxd31);
    z3 = INTEGRAL_FORMULA(z3);
    return z3;
}

uint16_t CALCULATOR(uint16_t *ADC_VALUE){

	uint16_t RESPONSE = 0 ;
	z1 = Z1_VALUE();
	z2 = Z1_VALUE();
	z3 = Z1_VALUE();


	if ( RESPONSE < MIN_FREQ_VALUE )
		return MIN_FREQ_VALUE;
	else if ( RESPONSE > MAX_FREQ_VALUE )
		return MAX_FREQ_VALUE;
	return RESPONSE;
}




