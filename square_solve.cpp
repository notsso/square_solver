#include <txlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>



const int INF_ROOTS = -1;
const int IMG_ROOTS = -2;
const int NO_ROOTS  = 0;
const int ONE_ROOT  = 1;
const int TWO_ROOTS = 2;

const double PERM_MSR_INACC = 1e-5; /*Допустимая ошибка в подсчётах действительных чисел*/

const int POWER_OF_EQUATION = 2; /*Степень уравнения*/


/*Декларация*/
int compare_double_zero(double number);

int compare_double_zero(double number) {

    if (number < PERM_MSR_INACC && number > -PERM_MSR_INACC) {
        return 1;
    } else {
        return 0;
    }

}

/*Декларация*/
int solve_equation(double *list_of_coef, double *lor_re, double *lor_im);

int solve_equation(double *list_of_coef, double *lor_re, double *lor_im) {

    double a = list_of_coef[0];
    double b = list_of_coef[1];
    double c = list_of_coef[2];

    double d = 0, sqrt_d = 0;

    if (compare_double_zero(a)) { /*if (a == 0)*/

        if (compare_double_zero(b)) { /*if (b == 0)*/

            return (compare_double_zero(c)) ? INF_ROOTS : NO_ROOTS; /*if (c == 0)*/

        } else { /*if (b != 0)*/

            lor_re[0] = -c / b;

            return ONE_ROOT;

        }

    } else { /*if (a != 0)*/

        d = b*b - 4*a*c;

        if (d < 0) {

            lor_re[0] = -b / (2*a);
            lor_im[0] = -d / (2*a);

            lor_re[1] = -b / (2*a);
            lor_im[1] = d / (2*a);

            return IMG_ROOTS;

        } else if (compare_double_zero(d)) { /*if (d == 0)*/

            lor_re[0] = lor_re[1] = -b / (2*a);

            return ONE_ROOT;

        } else { /*if (d > 0)*/

            sqrt_d = sqrt(d);

            lor_re[0] = (-b - sqrt_d) / (2*a);
            lor_re[1] = (-b + sqrt_d) / (2*a);

            return TWO_ROOTS;

        }
    }

}

/*Декларация*/
int print_results(int number_of_roots, double *lor_re, double *lor_im);

int print_results(int number_of_roots, double *lor_re, double *lor_im) {

    switch(number_of_roots) {

        case INF_ROOTS:
            printf("Любое число \n");
            break;

        case IMG_ROOTS:
            printf("Действительных решений нет. Воображаемые: \n");
            printf("Первый корень: x1 = %f + %lfi \n", lor_re[0], lor_im[0]);
            printf("Второй корень: x2 = %f - %lfi \n", lor_re[1], -lor_im[1]);
            break;

        case TWO_ROOTS:
            printf("2 действительных корня \n");
            printf("Первый корень: x1 = %lf \n", lor_re[0]);
            printf("Второй корень: x2 = %lf \n", lor_re[1]);
            break;

        case ONE_ROOT:
            printf("1 действительное решение \n");
            printf("x1 = %lf \n", lor_re[0]);
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

/*Декларация*/
int input_coefficents(double *list_of_coef);

int input_coefficents(double *list_of_coef) {

    char ch = ' ';

    double temp_coef = NAN;               /*Текущее вводимое число*/
    int dot_before = 0, ch_after_dot = 0; /*Отметка для ввода чисел с точкой, Счётчик для ввода чисел с точкой*/
    int index_of_abc = 0;                 /*Текущий коэффицент по номеру*/


    do {

        ch = getchar();
        while (!((isdigit(ch)) || ch == '.' || isspace(ch) || ch == '\n' || ch == EOF)) {

            if (ch == EOF) {
                return -1;
            }

            printf("Некорректный ввод \n");
            ch = getchar();
        }

        switch (ch) {

            case '\n':
                if (isnan(temp_coef)) {
                    break;
                }
                list_of_coef[index_of_abc] = temp_coef;
                temp_coef = NAN;
                dot_before = 0;
                ch_after_dot = 0;
                index_of_abc += 1;
                break;


            case ' ':
                if (isnan(temp_coef)) {
                    printf("Вы ничего не ввели \n");
                    break;
                }
                list_of_coef[index_of_abc] = temp_coef;
                temp_coef = NAN;
                dot_before = 0;
                ch_after_dot = 0;
                index_of_abc += 1;
                break;


            case '.':
                if (isnan(temp_coef)) {
                    printf("Вы ничего не ввели \n");
                    break;
                }
                dot_before = 1;
                ch_after_dot += 1;
                break;


            default:
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

    } while (index_of_abc < POWER_OF_EQUATION + 1);

    return 1;

}


int main () {

    double list_of_coef[POWER_OF_EQUATION]     = {};
    double list_of_roots_re[POWER_OF_EQUATION] = {}; /*Рещения. Первое число - реальная часть, второе - воображаемая*/
    double list_of_roots_im[POWER_OF_EQUATION] = {};

    for (int i = 0; i < POWER_OF_EQUATION; i++) {

        list_of_coef[i]  = 0;
        list_of_roots_re[i] = NAN;
        list_of_roots_im[i] = NAN;

    }

    int number_of_roots = 0;

    printf("Введите коэффиценты квадратного уравнения: \n");

    if (input_coefficents(list_of_coef) == -1) {
        printf("Принудительное завершение");
        return 0;
    }

    number_of_roots = solve_equation(list_of_coef, list_of_roots_re, list_of_roots_im);

    print_results(number_of_roots, list_of_roots_re, list_of_roots_im);

    return 0;
}

