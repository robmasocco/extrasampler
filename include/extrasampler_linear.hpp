/**
 * @brief Linear extrapolation oversampler.
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

#ifndef LINEAR_EXTRASAMPLER_H
#define LINEAR_EXTRASAMPLER_H

class Extrapolator
{
	private:
		double prevsample_T;
		double prevsample_S;
		double a;
		double b;
		
	public:
		Extrapolator();
		Extrapolator(double T, double S);
		double get(double T);
		void updateSample(double T, double S);
};

#endif
