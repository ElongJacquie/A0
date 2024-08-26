#include <stdio.h>
#include "complex.h"

int main() {
    COMP_int z1 = {3, 4};
    COMP_int z2 = {1, 2};
    COMP_int sum_int = add_int(z1, z2);

    printf("z1: ");
    print_euler_int(z1);
    printf("z2: ");
    print_euler_int(z2);
    printf("Sum: ");
    print_euler_int(sum_int);

    COMP_float z3 = {3.5, 4.5};
    COMP_float z4 = {1.1, 2.2};
    COMP_float sum_float = add_float(z3, z4);

    printf("z3: ");
    print_euler_float(z3);
    printf("z4: ");
    print_euler_float(z4);
    printf("Sum: ");
    print_euler_float(sum_float);

    return 0;
}
