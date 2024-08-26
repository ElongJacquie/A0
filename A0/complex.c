#include<math.h>
#include "complex.h"
#include<stdio.h>

double norm2_int(COMP_int z){
return sqrt((z.real * z.real) +(z.imag * z.imag));
}
double norm2_float(COMP_float z){
return sqrt((z.real * z.real) +(z.imag * z.imag));
}

COMP_int add_int(COMP_int z1 , COMP_int z2){
COMP_int result;
result.real = z1.real + z2.real;
result.imag = z1.imag + z2.imag;
return result;
}

COMP_float add_float(COMP_float z1 , COMP_float z2){
COMP_float result;
result.real = z1.real + z2.real;
result.imag = z1.imag + z2.imag;
return result;
}
void print_euler_int(COMP_int z){
double r = norm2_int(z);
double theta = atan2(z.imag,z.real);
printf("z = %2.f * exp(i*%2.f)\n",r ,theta);
}
void print_euler_float(COMP_float z){
double r = norm2_float(z);
double theta = atan2(z.imag,z.real);
printf("z = %2.f * exp(i*%2.f)\n",r ,theta);
}

