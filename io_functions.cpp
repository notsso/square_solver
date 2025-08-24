#include <txlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "io_functions.h"
#include "functional_functions.h"
#include "constants.h"

int continue_working() {

    char ch = '1';

    printf("вуд ю лайк ту континью? (Y/N)\n");

    ch = getchar();
    while (!(ch == 'Y' or ch == 'N' or ch == EOF)) {

        printf("хлебом не корми дай сломать что-нибудь, vvedi snova \n");
        ch = getchar();

    }

    return ch == 'Y';

}

int solve_test(const struct equation *fact_eq) {

    struct equation eq;

    for (int i = 0; i < TOTAL_COEF; i++) {

        eq.loc[i] = fact_eq->loc[i];

    }

    eq.number_of_roots = 0;

    fill_array_double(eq.lor_re, NAN);
    fill_array_double(eq.lor_im, NAN);

    solve_equation(&eq);

    if (!(eq.number_of_roots == fact_eq->number_of_roots
          && compare_arrays(eq.lor_re, fact_eq->lor_re)
          && compare_arrays(eq.lor_im, fact_eq->lor_im))) {

        printf("warning\n\n");

        printf("a = %lg, b = %lg, c = %lg\n\n", eq.loc[0], eq.loc[1], eq.loc[2]);

        printf("number_of_roots = %d,  real_number_of_roots = %d\n\n", eq.number_of_roots, fact_eq->number_of_roots);

        printf("first_root      = %15lg, real_first_root      = %15lg\n", eq.lor_re[0], fact_eq->lor_re[0]);
        printf("second_root     = %15lg, real_second_root     = %15lg\n\n", eq.lor_re[1], fact_eq->lor_re[1]);

        printf("im_first_root   = %15lg, real_im_first_root   = %15lg\n", eq.lor_im[0], fact_eq->lor_im[0]);
        printf("im_second_root  = %15lg, real_im_second_root  = %15lg\n\n\n", eq.lor_im[1], fact_eq->lor_im[1]);

        return 0;

    }

    return 1;

}

int run_tests(const struct equation *eq) {

    int passed = 0;

    for (int i = 0; i < NUMBER_TESTS; i++) {

        passed += solve_test(&eq[i]);

    }

    return passed;

}

int input_coefficents(struct equation *eq) {

    char ch = ' ';

    double temp_coef = NAN;               //Текущее вводимое число
    int dot_before = 0, ch_after_dot = 0; //Отметка для ввода чисел с точкой, Счётчик для ввода чисел с точкой
    int index_of_abc = 0;                 //Текущий коэффицент по номеру
    int sign = 1;                         //Отметка знака числа


    do {

        ch = getchar();
        while (!((isdigit(ch)) || ch == '.' || ch == ' ' || ch == '\n' || ch == '-' || ch == EOF)) {

            if (ch == EOF) {
                return -1;
            }

            printf("Некорректный ввод \n");
            ch = getchar();
        }

        switch (ch) {

            case ' ':
                if (isnan(temp_coef)) {
                    printf("Вы ничего не ввели \n");
                    break;
                }
            case '\n':
                if (isnan(temp_coef)) {
                    break;
                }
                eq->loc[index_of_abc] = temp_coef * sign;
                temp_coef = NAN;
                sign = 1;
                dot_before = 0;
                ch_after_dot = 0;
                index_of_abc += 1;
                break;


            case '.':
                if (isnan(temp_coef)) {
                    printf("Вы ничего не ввели\n");
                    break;
                }
                if (dot_before) {
                    printf("Вы ввели 2 точки, некорректный ввод\n");
                    temp_coef = NAN;
                    sign = 1;
                    dot_before = 0;
                    ch_after_dot = 0;
                    break;
                }
                dot_before = 1;
                ch_after_dot += 1;
                break;

            case '-':
                sign = -1;
                break;


            default:
                //ch - '0' : перевод цифры из char в int
                if (isnan(temp_coef)) {
                    temp_coef = ch - '0';
                } else if (dot_before) {
                    temp_coef += (ch - '0') * pow(10, -ch_after_dot);
                    ch_after_dot += 1;
                } else {
                    temp_coef = temp_coef * 10 + (ch - '0');
                }
                break;

        }

    } while (index_of_abc < TOTAL_COEF);

    return 1;

}

int print_results(const struct equation *eq) {

    switch(eq->number_of_roots) {

        case INF_ROOTS:
            printf("Любое число \n");
            break;

        case IMG_ROOTS:
            printf("Действительных решений нет. Воображаемые: \n");
            printf("Первый корень: x1 = %f - %lgi \n", eq->lor_re[0], -eq->lor_im[0]);
            printf("Второй корень: x2 = %f + %lgi \n", eq->lor_re[1], eq->lor_im[1]);
            break;

        case TWO_ROOTS:
            printf("2 действительных корня \n");
            printf("Первый корень: x1 = %lg \n", eq->lor_re[0]);
            printf("Второй корень: x2 = %lg \n", eq->lor_re[1]);
            break;

        case ONE_ROOT:
            printf("1 действительное решение \n");
            printf("x1 = %lg \n", eq->lor_re[0]);
            break;

        case NO_ROOTS:
            printf("Решений нет \n");
            break;

        default:
            printf("Произошла ошибка \n");
            break;

    }

    return 1;

}

