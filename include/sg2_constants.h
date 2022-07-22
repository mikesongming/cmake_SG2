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

#ifndef SG2_TYPEDEF_HXX_
#define SG2_TYPEDEF_HXX_


namespace sg2 {

static constexpr double const PI = 3.1415926535897932384626433832795028841971;
static constexpr double const D_PI = PI*2.0;

constexpr inline double DEG(double RAD) {
	return RAD*180.0/PI;
}

constexpr inline double RAD(double DEG) {
	return DEG*PI/180.0;
}

/* Top of atmosphere broadband irradiance on normal incidence (W/m2) */
static constexpr double const SOLAR_CONSTANT = 1362.0;
/* Astronomical unit : annual average of the Sun-Earth distance (m) */
static constexpr double const AU = 149597870691.0; /* +/- 6 m (McCarthy et Petit, 2003) */

/** 1970-01-01T12:00 **/
static double const EPOCH_JD = 2440587.5;

static double const Delta_tau = -9.9337353631981704e-005;

struct ellps;
extern ellps const ELLPS_WGS84;
extern ellps const ELLPS_RGF83;
extern ellps const ELLPS_NTF;
extern ellps const ELLPS_AA;
extern ellps const ELLPS_SPA;
extern ellps const ELLPS_NGP;
extern ellps const ELLPS_SPHERE;

} // namespace sg2

#endif /* SG2_TYPEDEF_HXX_ */
