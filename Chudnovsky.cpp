#include <iostream>
#include <mpir.h>

void calculate_pi_chudnovsky(int digits) {
    // Variable declarations
    mpf_set_default_prec(6 * digits);  // Precision setting for high-precision numbers
    mpf_t pi, sum, term, temp;
    mpz_t k_factorial, numerator, denominator;
    
    mpf_init(pi);
    mpf_init(sum);
    mpf_init(term);
    mpf_init(temp);
    mpz_init(k_factorial);
    mpz_init(numerator);
    mpz_init(denominator);
    
    mpf_set_ui(sum, 0);

    for (int k = 0; k < digits; ++k) {
        // k_factorial = (6k)!
        mpz_fac_ui(k_factorial, 6 * k);

        // numerator = (13591409 + 545140134k) * (6k)!
        mpz_set_ui(numerator, 545140134);
        mpz_mul_ui(numerator, numerator, k);
        mpz_add_ui(numerator, numerator, 13591409);
        mpz_mul(numerator, numerator, k_factorial);

        // denominator = (3k)! * (k!)^3 * (-640320)^(3k)
        mpz_fac_ui(denominator, 3 * k);
        mpz_t temp_z;
        mpz_init(temp_z);
        mpz_fac_ui(temp_z, k);
        mpz_pow_ui(temp_z, temp_z, 3);
        mpz_mul(denominator, denominator, temp_z);

        mpz_pow_ui(temp_z, temp_z, 0);
        mpz_ui_pow_ui(temp_z, 640320, 3 * k);
        mpz_mul(denominator, denominator, temp_z);
        if (k % 2 != 0) mpz_neg(denominator, denominator);

        // term = numerator / denominator
        mpf_set_z(term, numerator);
        mpf_div_z(term, term, denominator);

        // sum += term
        mpf_add(sum, sum, term);

        mpz_clear(temp_z);
    }

    // pi = 1 / (sum * 12)
    mpf_set_ui(temp, 12);
    mpf_mul(sum, sum, temp);
    mpf_ui_div(pi, 1, sum);

    // Print results
    gmp_printf("Pi: %.Ff\n", pi);

    // Clear memory
    mpf_clear(pi);
    mpf_clear(sum);
    mpf_clear(term);
    mpf_clear(temp);
    mpz_clear(k_factorial);
    mpz_clear(numerator);
    mpz_clear(denominator);
}

int main() {
    int digits;
    std::cout << "Enter the number of digits for precision: ";
    std::cin >> digits;

    calculate_pi_chudnovsky(digits);

    return 0;
}
