/*
 * Copyright 2014-2021 MINES ParisTech
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

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <tuple>

#include "sg2.h"

void usage() {
    std::cout << "Usage: sg2_query <lat> <lon> <alt> <jd>" << std::endl;
}

/*
 * > ./sg2_query 120 60 34 2458500.2352202
 * Time related data (i.e. solar system geometry)
 * geoc.ut            = 2019-01-16T17:38:43.025
 * geoc.tt            = 2019-01-16T17:38:43.190
 * ...
 * sun_rise          = 2019-01-15T23:22:26.576
 * sun_transite      = 2019-01-16T8:9:37.059
 * sun_set           = 2019-01-16T16:55:19.225
 */

int main(int argc, char ** argv) {

    if(argc != 5) {
        usage();
        return -1;
    }

    double lat = atof(argv[1]);
    double lon = atof(argv[2]);
    double alt = atof(argv[3]);
    double jd = atof(argv[4]);

    sg2::julian xjd{jd};

    /** location related data **/
    sg2::geopoint geopoint{lon, lat, alt, sg2::ELLPS_WGS84};

    /** time related data **/
    sg2::geocentric_data geoc{sg2::date{xjd.value}};

    /** local-time related data **/
    sg2::topocentric_data topoc{geoc, geopoint};

    /**
     * Computing solar system state.
     **/

    auto sunrise = sg2::sunrise(geoc.ut, geopoint);

    std::cout << "Time related data (i.e. solar system geometry)" << std::endl;
    std::cout << "geoc.ut            = " << geoc.ut << std::endl;
    std::cout << "geoc.tt            = " << geoc.tt << std::endl;

    std::cout << "geoc.R             = " << geoc.R << std::endl;
    std::cout << "geoc.L             = " << geoc.L << std::endl;

    std::cout << "geoc.delta         = " << geoc.delta << std::endl;
    std::cout << "geoc.EOT           = " << geoc.EOT << std::endl;
    std::cout << "geoc.Theta_a       = " << geoc.Theta_a << std::endl;
    std::cout << "geoc.epsilon       = " << geoc.epsilon << std::endl;
    std::cout << "geoc.nu            = " << geoc.nu << std::endl;
    std::cout << "geoc.r_alpha       = " << geoc.r_alpha << std::endl;
    std::cout << "geoc.Delta_psi     = " << geoc.Delta_psi << std::endl;

    std::cout << "Location related data" << std::endl;

    std::cout << "geopoint.lambda   = " << geopoint.lambda << std::endl;
    std::cout << "geopoint.phi      = " << geopoint.phi << std::endl;
    std::cout << "geopoint.u        = " << geopoint.u << std::endl;
    std::cout << "geopoint.x        = " << geopoint.x << std::endl;
    std::cout << "geopoint.y        = " << geopoint.y << std::endl;

    std::cout << "Sun related data" << std::endl;

    std::cout << "topoc.delta       = " << topoc.delta << std::endl;
    std::cout << "topoc.alpha_S     = " << topoc.alpha_S << std::endl;
    std::cout << "topoc.gamma_S0    = " << topoc.gamma_S0 << std::endl;
    std::cout << "topoc.omega       = " << topoc.omega << std::endl;
    std::cout << "topoc.r_alpha     = " << topoc.r_alpha << std::endl;
    std::cout << "topoc.toa_hi      = " << topoc.toa_hi << std::endl;
    std::cout << "topoc.toa_ni      = " << topoc.toa_ni << std::endl;

    std::cout << "Extra data" << std::endl;
    double x = (xjd.value + (lon/360.0) - (topoc.omega/(sg2::D_PI)));
    std::cout << "tst-tu            = " << (x-std::floor(x+0.5)) << std::endl;

    std::cout << "sun_rise          = " << std::get<0>(sunrise) << std::endl;
    std::cout << "sun_transite      = " << std::get<1>(sunrise) << std::endl;
    std::cout << "sun_set           = " << std::get<2>(sunrise) << std::endl;

    return 0;

}


