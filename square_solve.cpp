#include <txlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "io_functions.h"
#include "functional_functions.h"
#include "constants.h"

/*
struct equation {

    //loc    - list of coefficents
    //lor_re - list of roots_real
    //lor_im - list of roots_imaginary

    double loc[TOTAL_COEF];
    double lor_re[POWER_OF_EQUATION];
    double lor_im[POWER_OF_EQUATION];

    int number_of_roots;

};
*/


int main () {

    /*struct equation equations[NUMBER_TESTS] = {
        {{1, 2, 1},  {-1, -1},   {NAN, NAN}, TWO_ROOTS},
        {{1, 4, 4},  {-2, -2},   {NAN, NAN}, ONE_ROOT},
        {{1, -5, 6}, {2, 3},     {NAN, NAN}, TWO_ROOTS},
        {{2, 0, 0},  {0, 0},     {NAN, NAN}, ONE_ROOT},
        {{0, 0, 0},  {NAN, NAN}, {NAN, NAN}, INF_ROOTS}
    };

    printf("%lg, %lg \n", equations[0].loc[0], equations[1].loc[1]);
    printf("Пройдено тестов: %d\n", run_tests(equations)); */

    while (1) {

        struct equation eq;

        fill_array_double(eq.loc, 0);
        fill_array_double(eq.lor_re, NAN);
        fill_array_double(eq.lor_im, NAN);

        printf("Введите коэффиценты квадратного уравнения: \n");

        if (input_coefficents(&eq) == -1) { //Проверка результата работы функции ввода. 1 - норм, -1 - не норм
            printf("Принудительное завершение");
            return 0;
        }

        printf("a = %lg, b = %lg, c = %lg\n", eq.loc[0], eq.loc[1], eq.loc[2]);

        solve_equation(&eq);

        print_results(&eq);

        int cont = continue_working(); //Вопрос пользователю о завершении работы

        if (cont == 0) {

            printf("пака");

            return 0;

        }

    }

}
