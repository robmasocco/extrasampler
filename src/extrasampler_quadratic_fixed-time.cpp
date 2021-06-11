/**
 * @brief Quadratic fixed-time extrapolation oversampler source code.
 *
 * @author Roberto Masocco <robmasocco@gmail.com>
 * @author Marco Passeri <mbass.pass@gmail.com>
 *
 * @date June 11, 2021
 */
/**
 * This is free software.
 * You can redistribute it and/or modify this file under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this file; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA.
 */

#include <math.h>

#include "../include/extrasampler_quadratic_fixed-time.hpp"

Extrapolator::Extrapolator(double T)
{
    tau = T;
    this->reset();

    invTMtx[0][0] = 1 / (2 * tau * tau);
    invTMtx[0][1] = -1 / (tau * tau);
    invTMtx[0][2] = 1 / (2 * tau * tau);

    invTMtx[1][0] = -5 / (2 * tau);
    invTMtx[1][1] = 4 / tau;
    invTMtx[1][2] = -3 / (2 * tau);

    invTMtx[2][0] = 3;
    invTMtx[2][1] = -3;
    invTMtx[2][2] = 1;
}

void Extrapolator::reset(void)
{
    Ss0 = 0;
    Ss1 = 0;

    samplerecvd = 0;

    a = 0;
    b = 0;
    c = 0;
}

void Extrapolator::updateSample(double T, double S)
{
    if (samplerecvd == 0)
    {
        Ss0 = S;
        samplerecvd++;
    }
    else if (samplerecvd == 1)
    {
        Ss1 = S;
        samplerecvd++;
    }
    else
    {
        a = invTMtx[0][0] * Ss0 + invTMtx[0][1] * Ss1 + invTMtx[0][2] * S;
        b = invTMtx[1][0] * Ss0 + invTMtx[1][1] * Ss1 + invTMtx[1][2] * S;
        c = invTMtx[2][0] * Ss0 + invTMtx[2][1] * Ss1 + invTMtx[2][2] * S;

        lastabsT = T;

        Ss0 = Ss1;
        Ss1 = S;
    }
}

double Extrapolator::get(double T)
{
    if (samplerecvd < 2)
        return NAN;
    double t = T - lastabsT;

    return a * t * t + b * t + c;
}
