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

#ifndef SG2_GEOCENTRIC_HXX_
#define SG2_GEOCENTRIC_HXX_

#include "sg2_date.h"

namespace sg2 {

/* Geocentric coordinates */
struct geocentric_data {
    date ut;           /* Universal Time */
    date tt;           /* Terrestrial Time */
    double R;          /* Radius Sun-Earth (ua) */
    double L;          /* Heliocentric Earth true longitude (rad) */
    double Delta_psi;  /* Nutation in Geocentric Sun longitude (rad) */
    double epsilon;    /* Earth true obliquity (rad) */
    double Theta_a;    /* Geocentric Earth true longitude (rad) */
    double r_alpha;    /* Geocentric right ascension (rad) */
    double delta;      /* Geocentric declination (rad) */
    double nu;         /* Apparent sideral time (rad) */
    double EOT;        /* Equation of Time (rad) : difference between apparent solar time and mean solar time */

    geocentric_data() = default;
    geocentric_data(date const & ut);
    geocentric_data(date const & ut, date const & tt);

    geocentric_data(geocentric_data const &) = default;

    auto operator=(geocentric_data const &) -> geocentric_data & = default;

    void _init_all();

};

} // namespace sg2

#endif /* SG2_GEOCENTRIC_HXX_ */
