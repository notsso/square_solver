#ifndef FUNCTIONAL_FUNCTIONS_H_INCLUDED
#define FUNCTIONAL_FUNCTIONS_H_INCLUDED

/**
 * @brief              Comparison of 2 numbers with permittable inaccuracy PERM_MSR_INACC with NAN processing.
 * @param [in] root_1  First number with double type
 * @param [in] root_2  Second number with double type
 * @return             1 if numbers equals with permittable inaccuracy PERM_MSR_INACC
 *                     or they both equals NAN, otherwise 0
 */
int compare_roots(double root_1, double root_2);

/**
 * @brief               Comparison of 2 arrays
 * @param [in] array_1  First array of double type
 * @param [in] array_2  Second array of double type
 * @return              1 if len(array_1) equals len(array_2) and
 *                      every element of array_1 equals with permittable inaccuracy PERM_MSR_INACC
 *                      to an element with same index in array_2
 */
int compare_arrays(const double *array_1, const double *array_2);

/**
 * @brief                                Solves square equation with coefficents from first argument,
 *                                       writes roots into other arguments.
 * @param [in]  equation                 Structure from constants.h
 * @param [in]  equation.loc             Array of double[TOTAL_COEF] of equation coefficents
 * @param [out] equation.lor_re          Array of double[POWER_OF_EQUATION] of real roots
 * @param [out] equation.lor_im          Array of double[POWER_OF_EQUATION] of imaginary roots
 * @param [out] equation.number_of_roots Number of roots that equals to the one of root constants
 * @return                               Always 1
 */
int solve_equation(struct equation *eq);

/**
 * @brief               Comparison of number with 0 with permittable inaccuracy PERM_MSR_INACC.
 * @param  [in] number  Number with double type
 * @return              1 if (-PERM_MSR_INACC; PERM_MSR_INACC) contains number, else 0
 */
int compare_double_zero(double number);

/**
 * @brief                       Fills array_double[len] with number_to_fill.
 * @param [out] array_double    Array to fill
 * @param [in]  number_to_fill  Number to fill
 * @return                      Always 1
 */
int fill_array_double(double *array_double, double number_to_fill);

/**
 * @brief                    Calculates length of array of double
 * @param [in] array_double  Array of double with unknown length
 * @return                   Length of array
 */
int len_array_double(const double *array_double);


#endif // FUNCTIONAL_FUNCTIONS_H_INCLUDED
