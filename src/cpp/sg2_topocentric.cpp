/*
 * Copyright 2011-2021 MINES ParisTech
 * Copyright 2011 Philippe Blanc <philippe.blanc@mines-paristech.fr>
 * Copyright 2014-2021 Benoit Gschwind <benoit.gschwind@mines-paristech.fr>
 *
 * This file is part of libsg2.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */


#include "sg2_topocentric.h"
#include "sg2_constants.h"
#include "sg2_math.h"


namespace sg2 {

topocentric_data::topocentric_data(geocentric_data const & geoc, geopoint const & gp)
{
    double xi = (gp.ellipse.a / AU);

    double omega_g_kp_kd = geoc.nu - geoc.r_alpha + gp.lambda;
    double cos_geoc_delta_kd = math::cos(geoc.delta);

    double Delta_r_alpha_kp_kd = (-gp.x * math::sin(omega_g_kp_kd)
            / cos_geoc_delta_kd * xi);
    r_alpha = geoc.r_alpha + Delta_r_alpha_kp_kd;

    delta = geoc.delta + (gp.x * math::cos(omega_g_kp_kd) * math::sin(geoc.delta)
                             - gp.y * cos_geoc_delta_kd) * xi;

    omega = omega_g_kp_kd - Delta_r_alpha_kp_kd;

    double cos_omega_kp_kd = math::cos(omega);
    double cos_delta_kp_kd = math::cos(delta);
    double sin_delta_kp_kd = math::sin(delta);
    double tan_delta_kp_kd = sin_delta_kp_kd / cos_delta_kp_kd;

    gamma_S0 = math::asin(gp.sin_phi_kp * sin_delta_kp_kd
                       + gp.cos_phi_kp * cos_delta_kp_kd * cos_omega_kp_kd);

    alpha_S = math::atan2(math::sin(omega), cos_omega_kp_kd * gp.sin_phi_kp - tan_delta_kp_kd * gp.cos_phi_kp)
                    + PI;

    if (gamma_S0 > 0.0) {
        toa_ni = SOLAR_CONSTANT / (geoc.R * geoc.R);
        toa_hi = toa_ni * math::sin(gamma_S0);
    } else {
        toa_ni = 0.0;
        toa_hi = 0.0;
    }
}

double topocentric_correction_refraction_SAE(double const gamma_S0, double const P, double const T);
double topocentric_correction_refraction_ZIM(double const gamma_S0, double const P, double const T);

double topocentric_data::topocentric_correction_refraction(double const P,
        double const T, correction_refraction_e method) const
{
    switch (method) {
    case REFRACTION_SAE:
        return topocentric_correction_refraction_SAE(gamma_S0, P, T);
        break;
    case REFRACTION_ZIM:
        return topocentric_correction_refraction_ZIM(gamma_S0, P, T);
        break;
    case REFRACTION_NONE:
        return gamma_S0;
        break;
    default:
        return NAN;
        break;
    }
}


double topocentric_correction_refraction_SAE(double const gamma_S0, double const P, double const T)
{
    double const gamma_S0_seuil = -0.010035643198967;
    double const R = 0.029614018235657;
    /*(tan(gamma_S0_seuil + 0.0031376 / (gamma_S0_seuil+ 0.089186))) */
    double K;
    double tan_gamma_S0 = 0.0;
    double gamma_S0_2 = 0.0, gamma_S0_3 = 0.0, gamma_S0_4 = 0.0;
    unsigned long k;

    K = (P / 1010.0) * (283. / (273. + T)) * 2.96706e-4;

    if (gamma_S0 > gamma_S0_seuil) {
        return gamma_S0 + K / (math::tan(gamma_S0 + 0.0031376 / (gamma_S0 + 0.089186)));
    } else {
        return gamma_S0 + (K / R) * math::tan(gamma_S0_seuil) / math::tan(gamma_S0);
    }

}

double topocentric_correction_refraction_ZIM(double const gamma_S0, double const P, double const T)
{
    static const double gamma_S0_seuil = -0.010035643198967;
    static const double R = 0.029614018235657;
    /*(tan(gamma_S0_seuil + 0.0031376 / (gamma_S0_seuil+ 0.089186))) */
    double K;
    double tan_gamma_S0 = 0.0;
    double gamma_S0_2 = 0.0, gamma_S0_3 = 0.0, gamma_S0_4 = 0.0;
    unsigned long k;

    K = (P / 1013.0) * (283. / (273. + T)) * 4.848136811095360e-006;

    if (gamma_S0 <= -0.010036) {
        return gamma_S0 + (-20.774 / tan_gamma_S0) * K;
    } else if (gamma_S0 <= 0.087266) {
        gamma_S0_2 = gamma_S0 * gamma_S0;
        gamma_S0_3 = gamma_S0_2 * gamma_S0;
        gamma_S0_4 = gamma_S0_4 * gamma_S0;
        return gamma_S0
                + (1735 - 2.969067e4 * gamma_S0 + 3.394422e5 * gamma_S0_2
                + -2.405683e6 * gamma_S0_3 + 7.66231727e6 * gamma_S0_4) * K;
    } else if (gamma_S0 <= 1.483529864195180) {
        return gamma_S0 + K * (58.1 / tan_gamma_S0 - 0.07 / pow(tan_gamma_S0, 3.0) + 0.000086 / pow(tan_gamma_S0, 5.0));
    } else {
        return NAN;
    }
}

} // namespace sg2
