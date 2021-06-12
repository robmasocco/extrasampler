/**
 * @brief Small tester to check that compilation works.
 *
 * @author Roberto Masocco <robmasocco@gmail.com>
 *
 * @date June 12, 2021
 */

#include <iostream>
#include <cmath>
#include <math.h>

#include "../include/extrasampler_linear.hpp"
#include "../include/extrasampler_quadratic_fixed-time.hpp"

/* The works. */
int main(void)
{
    LinearExtrasampler<double> linear();
    QuadFixTimeExtrasampler<double> quad(0.1);
    std::cout << "It compiles!" << std::endl;
    std::cout << "Quad has tau: " << quad.get_tau() << "." << std::endl;
    if (!isnan(quad.get_sample(1.0)))
    {
        std::cout << quad.get_sample(1.0) << " should be NAN!" << std::endl;
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
