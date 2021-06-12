/**
 * @brief Quadratic fixed-time extrapolation oversampler source code.
 *
 * @author Marco Passeri <mbass.pass@gmail.com>
 * @author Roberto Masocco <robmasocco@gmail.com>
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
#include <stdexcept>

#include "../include/extrasampler_quadratic_fixed-time.hpp"

/**
 * @brief Creates a quadratic extrasampler, assuming constant sampling time.
 *
 * @param tau Sampling time, must be nonzero.
 */
template <typename NumericType>
QuadFixTimeExtrasampler<NumericType>::QuadFixTimeExtrasampler(NumericType tau)
{
    if (tau == (NumericType)0)
        throw std::invalid_argument;
    // Set private members.
    tau_ = tau;
    this->reset();
    // Initialize coefficients matrix, computed with given tau.
    inv_tau_mat_[0][0] = 1 / (2 * tau * tau);
    inv_tau_mat_[0][1] = -1 / (tau * tau);
    inv_tau_mat_[0][2] = 1 / (2 * tau * tau);

    inv_tau_mat_[1][0] = -5 / (2 * tau);
    inv_tau_mat_[1][1] = 4 / tau;
    inv_tau_mat_[1][2] = -3 / (2 * tau);

    inv_tau_mat_[2][0] = 3;
    inv_tau_mat_[2][1] = -3;
    inv_tau_mat_[2][2] = 1;
}

/**
 * @brief Resets the intenal state of the extrasampler.
 */
template <typename NumericType>
void QuadFixTimeExtrasampler<NumericType>::reset(void)
{
    sample_0_ = 0;
    sample_1_ = 0;
    a_ = 0;
    b_ = 0;
    c_ = 0;
    last_abs_time_ = 0;
    samples_rcvd_ = 0;
}

/**
 * @brief Computes a new predicted sample extrapolated from the stored ones.
 *
 * @param time Time at which to compute the new sample.
 * @return New extrapolated sample.
 */
template <typename NumericType>
NumericType QuadFixTimeExtrasampler<NumericType>::get_sample(NumericType time)
{
    // The extrapolator requires two samples to be stored.
    if (samples_rcvd_ < 2)
        return NAN;
    // Perform a quadratic approximation using relative time from last sample.
    NumericType t = time - last_abs_time_;
    return a_ * t * t + b_ * t + c_;
}

/**
 * @brief Updates stored samples when a new one is acquired.
 *
 * @param new_time Time at which the new sample was acquired.
 * @param new_sample New acquired sample.
 */
template <typename NumericType>
void QuadFixTimeExtrasampler<NumericType>::update_samples(NumericType new_time, NumericType new_sample)
{
    // Correctly store first two samples.
    if (samples_rcvd_ == 0)
    {
        sample_0_ = new_sample;
        samples_rcvd_++;
    }
    else if (samples_rcvd_ == 1)
    {
        sample_1_ = new_sample;
        samples_rcvd_++;
    }
    else
    {
        // Recompute approximation coefficients using the new sample and the previous ones.
        a_ = inv_tau_mat_[0][0] * sample_0_ + inv_tau_mat_[0][1] * sample_1_ + inv_tau_mat_[0][2] * new_sample;
        b_ = inv_tau_mat_[1][0] * sample_0_ + inv_tau_mat_[1][1] * sample_1_ + inv_tau_mat_[1][2] * new_sample;
        c_ = inv_tau_mat_[2][0] * sample_0_ + inv_tau_mat_[2][1] * sample_1_ + inv_tau_mat_[2][2] * new_sample;
        // Update stored data.
        last_abs_time_ = new_time;
        sample_0_ = sample_1_;
        sample_1_ = new_sample;
    }
}

/**
 * @brief Returns the extrapolator's sampling time.
 *
 * @return tau value.
 */
template <typename NumericType>
NumericType QuadFixTimeExtrasampler<NumericType>::get_tau(void)
{
    return tau_;
}
