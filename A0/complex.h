#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct{
   int real;
   int imag;
}COMP_int;


typedef struct{
   int real;
   int imag;
}COMP_float;

double norn2_int(COMP_int z );
double norn2_float(COMP_float z );
COMP_int add_int(COMP_int z1 , COMP_int z2);
COMP_float add_float(COMP_float z1 , COMP_float z2);
void print_euler_int(COMP_int z);
void print_euler_float(COMP_float z);

#endif // COMPLEX_H

