#include "formula.h"

volatile double const axd11 = 0.9703;
volatile double const axd12 = 9.8515 * (pow(10, (-5)));
volatile double const axd13 = 4.9257 * (pow(10, (-9)));
volatile double const axd21 = -2.9604;
volatile double const axd22 = 0.999;
volatile double const axd23 = 9.9993 * (pow(10, (-5)));
volatile double const axd31 = 4.9257 * (pow(10, (-9)));
volatile double const axd32 = -0.0049;
volatile double const axd33 = 1;

volatile double const bxd11 = -1.8314 * (pow(10, (-4)));
volatile double const bxd12 = 0.0297;
volatile double const bxd21 = -3.7178;
volatile double const bxd22 = 2.9604;
volatile double const bxd31 = 0.0092;
volatile double const bxd32 = 98.5149;

volatile double const kd_dig = 200;
volatile double const kp_dig = 37500;

volatile uint16_t const MAX_FREQ_VALUE = 1500;
volatile uint16_t const MIN_FREQ_VALUE = 858;

volatile double z1 = 0;
volatile double z2 = 0;
volatile double z3 = 0;
volatile double y = 0;
volatile double u = 0;
volatile double x = 0;
volatile double b0 = 0 ;

volatile double ref = 0 ;
volatile double u0 = 0 ;

volatile double *adc = &y;

static void INTEGRAL(double *INT) {
    //INTERGRAL INT
}

static void z1Value(double *z1p ,double *z2p ,double *z3p ,double *up ,double *yp){
    *z1p = (*z1p * axd11) + (*z2p * axd12) + (*z3p * axd13) + (*up * bxd11) + (*yp * bxd12);
    INTEGRAL(&z1p);
}

static void z2Value(double *z1p ,double *z2p ,double *z3p ,double *up ,double *yp){
    *z2p = (*z1p * axd21) + (*z2p * axd22) + (*z3p * axd23) + (*up * bxd21) + (*yp * bxd22);
    INTEGRAL(&z2p);
}

static void z3Value(double *z1p ,double *z2p ,double *z3p ,double *up ,double *yp){
    *z3p = (*z1p * axd31) + (*z2p * axd32) + (*z3p * axd33) + (*up * bxd31) + (*yp * bxd32);
    INTEGRAL(&z3p);
}

static void xValue(double *xp , double *rep , double *z1p){
    *xp = (*rep - *z1p) * kp_dig ;
}

static void yValue(double *yp , double *z2p){
    *yp = *z2p * kd_dig ;
}

static void u0Value(double *u0p, double *xp , double *yp){
    *u0p = *xp - *yp ;
}

static void uValue(double *up, double *u0p, double *z3p , double *b0p){
    *up = ( *u0p - *z3p ) / *b0p ;
}

uint16_t CALCULATOR(uint16_t* ADC_VALUE) {

	uint16_t RESPONSE = 0;
	*adc = *ADC_VALUE;

    z1Value(&z1,&z2,&z3,&u,&y);
    z2Value(&z1,&z2,&z3,&u,&y);
    z3Value(&z1,&z2,&z3,&u,&y);
    xValue(&x,&ref,&z1);
    yValue(&y,&z2);
    u0Value(&u0,&x,&y);
    uValue(&u,&u0,&z3,&b0);

	if (RESPONSE < MIN_FREQ_VALUE)
		return MIN_FREQ_VALUE;
	else if (RESPONSE > MAX_FREQ_VALUE)
		return MAX_FREQ_VALUE;
	return RESPONSE;
}
