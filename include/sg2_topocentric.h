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

#ifndef SG2_TOPOCENTRIC_HXX_
#define SG2_TOPOCENTRIC_HXX_

#include "sg2_geocentric.h"
#include "sg2_geopoint.h"

namespace sg2 {

enum correction_refraction_e {
    REFRACTION_NONE = 0,
    REFRACTION_SAE = 1,
    REFRACTION_ZIM = 2
};

struct topocentric_data {
    double r_alpha;  /* Topocentric right sun ascension (rad) */
    double delta;    /* Topocentric sun declination (rad) */
    double omega;    /* Topocentric local hour angle (rad) */
    double gamma_S0; /* Topocentric sun elevation angle without correction of atm. corr. (rad)*/
    double alpha_S;  /* Topocentric sun azimuth (rad) */
    double toa_ni;   /* irradiation at top of atmosphere normal incidence (W/m2) */
    double toa_hi;   /* irradiation at top of atmosphere horizontal incidence (W/m2) */

    topocentric_data() = default;
    topocentric_data(topocentric_data const &) = default;
    topocentric_data(geocentric_data const & geoc, geopoint const & gp);

    auto operator=(topocentric_data const &) -> topocentric_data & = default;

    double topocentric_correction_refraction(double const P, double const T, correction_refraction_e method = REFRACTION_NONE) const;

};

} // namespace sg2

#endif /* SG2_TOPOCENTRIC_HXX_ */
