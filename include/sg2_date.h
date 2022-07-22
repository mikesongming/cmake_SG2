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

#ifndef SG2_DATE_HXX_
#define SG2_DATE_HXX_

#include <cstdint>
#include <string>

namespace sg2 {

struct date;
struct julian;
struct ymdh;
struct ydoyh;

struct date {
    int64_t msec; // millisecond since 1970

    date() = default;
    date(int64_t msec): msec(msec) {};
    date(double jd);
    date(ymdh const & d);
    date(ydoyh const & d);

    operator std::string() const;
};

struct julian {
    double value; // julian date in factionnal days

    julian() = default;
    julian(double jd): value(jd) {};
    julian(ymdh const & d);
    julian(ydoyh const & d);
    julian(date const d);
};

/* Date YMD + H en heure décimale UT */
struct ymdh {
    int year;
    int month;
    int day_of_month;
    double hour;

    ymdh() = default;
    ymdh(short year, short month, char day_of_month, double hour);
    ymdh(double jd);
    ymdh(date const & d);
    ymdh(ydoyh const & p_ydoyh);
};

struct ymdhmsn {
    int year;
    int month;
    int day_of_month;
    int hour;
    int min;
    int sec;
    int msec;

    ymdhmsn() = default;
    ymdhmsn(date const date);

    operator std::string() const;
};

struct ydoyh {
    short year;
    short day_of_year;
    double hour;

    ydoyh() = default;
    ydoyh(ymdh const & p_ymdh);
};

}

#endif /* SG2_DATE_HXX_ */
