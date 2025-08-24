#include <txlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "functional_functions.h"
#include "constants.h"



int compare_roots(double root_1, double root_2) {

    int check = 0;

    check = check + isnan(root_1) + isnan(root_2);

    assert(check <= 2);
    assert(check >= 0);

    switch(check) {

        case 2:
            return 1;

        case 1:
            return 0;

        case 0:
            return compare_double_zero(root_1 - root_2);

        default:
            return 0;

    }
}

int compare_arrays(const double *array_1, const double *array_2) {

    int len1 = sizeof(array_1) / sizeof(array_1[0]);
    int len2 = sizeof(array_2) / sizeof(array_2[0]);

    if (len1 != len2) {

        return 0;

    }

    int check = 1; //Отметка сравнения

    for (int i = 0; i < len1; i++) {

        if (!(compare_roots(array_1[i], array_2[i]))) {

            check = 0;
            break;

        }

    }

    return check;

}

int solve_equation(struct equation *eq) {

    const double a = eq->loc[0];
    const double b = eq->loc[1];
    const double c = eq->loc[2];

    double d = 0, sqrt_d = 0;

    if (compare_double_zero(a)) { /*if (a == 0)*/

        if (compare_double_zero(b)) { /*if (b == 0)*/

            if (compare_double_zero(c)) {

                eq->number_of_roots = INF_ROOTS;

            } else {

                eq->number_of_roots = NO_ROOTS;

            }


        } else { /*if (b != 0)*/

            eq->lor_re[0] = -c / b;

            eq->number_of_roots = ONE_ROOT;

        }

    } else { /*if (a != 0)*/

        d = b * b - 4 * a * c;

        if (d < 0) {

            sqrt_d = sqrt(-d);

            eq->lor_re[0] = eq->lor_re[1] = -b / (2 * a);

            eq->lor_im[1] = sqrt_d / (2 * a);
            eq->lor_im[0] = -eq->lor_im[1];

            eq->number_of_roots = IMG_ROOTS;

        } else if (compare_double_zero(d)) { /*if (d == 0)*/

            eq->lor_re[0] = eq->lor_re[1] = (-b) / (2 * a);

            if (compare_double_zero(eq->lor_re[0])) {

                eq->lor_re[0] = eq->lor_im[1] = 0;

            }

            eq->number_of_roots = ONE_ROOT;

        } else { /*if (d > 0)*/

            sqrt_d = sqrt(d);

            eq->lor_re[0] = (-b - sqrt_d) / (2*a);
            eq->lor_re[1] = (-b + sqrt_d) / (2*a);

            eq->number_of_roots = TWO_ROOTS;

        }
    }

    return 1;

}

int compare_double_zero(double number) {

    return (fabs(number) < PERM_MSR_INACC);

}

int fill_array_double(double *array_double, double number_to_fill) {

    int len = len_array_double(array_double);

    for (int i = 0; i < len; i++) {

        array_double[i] = number_to_fill;

    }

    return 1;

}

int len_array_double(const double *array_double) {

    if (sizeof(array_double) == 1) {

        return 0;

    }

    return sizeof(array_double) / sizeof(array_double[0]);

}
