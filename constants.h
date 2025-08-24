#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


const int INF_ROOTS = -1;
const int IMG_ROOTS = -2;
const int NO_ROOTS  = 0;
const int ONE_ROOT  = 1;
const int TWO_ROOTS = 2;

const double PERM_MSR_INACC = 1e-5; //Допустимая погрешность в подсчётах действительных чисел

const int POWER_OF_EQUATION = 2; //Степень уравнения
const int TOTAL_COEF = POWER_OF_EQUATION + 1;

const int NUMBER_TESTS = 5;


struct equation {

    //loc    - list of coefficents
    //lor_re - list of roots_real
    //lor_im - list of roots_imaginary

    double loc[TOTAL_COEF];
    double lor_re[POWER_OF_EQUATION];
    double lor_im[POWER_OF_EQUATION];

    int number_of_roots;

};

#endif // CONSTANTS_H_INCLUDED
