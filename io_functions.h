#ifndef IO_FUNCTIONS_H_INCLUDED
#define IO_FUNCTIONS_H_INCLUDED

/**
 * @brief   Scanning symbols until it finds
 *          answer about continuation of program work.
 * @return  1 if 'Y' was found, 0 if 'N' or EOF was found
 */
int continue_working();

/**
 * @brief                            Check function solve_equation on correctness.
                                     Writes debug information if solution isn't right.
 * @param [in] loc                   Array[TOTAL_COEF] of coefficents
 * @param [in] fact_lor_re           Array[POWER_OF_EQUATION] of real parts of roots,
                                     that are considered right
 * @param [in] fact_lor_im           Array[POWER_OF_EQUATION] of imaginary parts of roots,
                                     that are considered right
 * @param [in] fact_number_of_roots  Number of roots, that are considered right
 * @return                           Always 1
 */
int solve_test(const struct equation *fact_eq);

/**
 * @brief                      Writes numbers with type double into list_of_coef.
 * @param [in] list_of_coef    Array[TOTAL_COEF] of coefficents
 * @return                     Always 1
 */
int input_coefficents(struct equation *eq);

/**
 * @brief                  Prints roots of previously solved square equation
                           with premade format depending on its number or roots.
 * @param [in] number_of_roots  Number of roots
 * @param [in] lor_re           Array[POWER_OF_EQUATION] of real parts of roots
 * @param [in] lor_im           Array[POWER_OF_EQUATION] of imaginary parts of roots
 * @return                 Always 1
 */
int print_results(const struct equation *eq);

int run_tests(const struct equation *equations);

#endif // IO_FUNCTIONS_H_INCLUDED
