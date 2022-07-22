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

#include "sg2_date.h"

#include "sg2_constants.h"
#include "sg2_utils.h"
#include "sg2_err.h"

#include <array>
#include <cmath>
#include <cstdio>


namespace sg2 {

inline int _date_leapyear(int year) {
    return (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)));
}

/* return the julian day at 12h */
inline int _ymd_to_julian_day(int year, int month, int day)
{
    int k;
    double Y, M, D, H;

    Y = year;
    M = month;
    D = day;
    if (M < 3) {
        M += 12;
        Y -= 1;
    }

    return 1721028.0 + D + floor((153.0 * M - 2.0) / 5.0) + 365.0 * Y
            + floor(Y / 4.0) - floor(Y / 100.0) + floor(Y / 400.0);
}

inline void _julian_day_to_ymd(int jd, int & year, int & month, int & day)
{
    double H, L, N, I, J, K;

    L = jd + 68569.0;
    N = floor(4 * L / 146097.0);
    L = L - floor((146097.0 * N + 3.0) / 4.0);
    I = floor(4000 * (L + 1) / 1461001.0);
    L = L - floor(1461.0 * I / 4.0) + 31.0;

    J = floor(80.0 * L / 2447.0);
    K = L - floor(2447.0 * J / 80.0);
    L = floor(J / 11.0);
    J = J + 2.0 - 12.0 * L;
    I = 100.0 * (N - 49.0) + I + L;

    year = I;
    month = J;
    day = K;

}


date::date(double jd)
{
    msec = (jd-EPOCH_JD)*24.0*60.0*60.0*1e3;
}

date::date(ymdh const & d)
{
    int64_t xjd = _ymd_to_julian_day(d.year, d.month, d.day_of_month);
    msec = (xjd-EPOCH_JD)*(24LL*60LL*60LL*1000LL) + d.hour*60.0*60.0*1e3;
}

date::date(ydoyh const & d): date(ymdh(d)) {};

date::operator std::string() const
{
    return static_cast<std::string>(ymdhmsn{*this});
}

julian::julian(ymdh const & d)
{
    int64_t xjd = _ymd_to_julian_day(d.year, d.month, d.day_of_month);
    value = xjd - 0.5 + d.hour / 24.0;
}

julian::julian(ydoyh const & d): julian(ymdh(d)) {};

julian::julian(date const d)
{
    value = d.msec/(24.0*60.0*60.0*1e3)+EPOCH_JD;
}

ymdh::ymdh(short year, short month, char day_of_month, double hour):
    year(year), month(month), day_of_month(day_of_month), hour(hour) {};

ymdh::ymdh(double jd)
{
    _julian_day_to_ymd(floor(jd + 0.5), year, month, day_of_month);
    hour = (jd + 0.5 - floor(jd + 0.5)) * 24.0;
}

ymdh::ymdh(date const & d)
{
    int jd = d.msec / (1e3 * 60.0 * 60.0 * 24.0) + EPOCH_JD + 0.5;
    _julian_day_to_ymd(jd, year, month, day_of_month);
    hour = static_cast<double>(d.msec % 1000LL)/(60.0*60.0*1e3);
}

ymdh::ymdh(ydoyh const & p_ydoyh)
{
    double B = static_cast<double>(_date_leapyear(p_ydoyh.year));
    year = p_ydoyh.year;
    hour = p_ydoyh.hour;

    if (p_ydoyh.day_of_year < 32) {
        month = 1;
    } else {
        month = 1
                + (short) (floor((303.0 + 5.
                * (((double) p_ydoyh.day_of_year) - 59.0 - B))/ 153.0));
    }

    if (month < 2) {
        day_of_month = p_ydoyh.day_of_year - 31 * (month - 1);
    } else {
        day_of_month = p_ydoyh.day_of_year
                - ((short) (floor((153.0 * ((double) month) - 2.0) / 5.0)
                        - 32.0 + B));
    }
}

ymdhmsn::ymdhmsn(date const date)
{
    int64_t xnsec = date.msec;

    // Find the nearest integer jd.
    int jd = xnsec / (1e3 * 60.0 * 60.0 * 24.0) + EPOCH_JD + 0.5;
    _julian_day_to_ymd(jd, year, month, day_of_month);

    /* in this order we avoid a lot of modulo */
    xnsec %= (1000LL * 60LL * 60LL * 24LL);
    hour = xnsec / (1000LL * 60LL * 60LL);
    xnsec -= hour * (1000LL * 60LL * 60LL);
    min = xnsec / (1000LL * 60LL);
    xnsec -= min * (1000LL * 60LL);
    sec = xnsec / (1000LL);
    xnsec -= sec * (1000LL);
    msec = (int)xnsec;

}

ymdhmsn::operator std::string() const
{
    std::array<char, 32> buf;
    snprintf(&buf[0], buf.size(), "%04d-%02d-%02dT%02d:%02d:%02d.%03d", year, month, day_of_month, hour, min, sec, msec);
    return std::string(&buf[0]);
}

ydoyh::ydoyh(ymdh const & p_ymdh)
{
    int k;
    double K;

    K = 2 - _date_leapyear(p_ymdh.year);
    year = p_ymdh.year;
    hour = p_ymdh.hour;
    day_of_year = (short) floor(275.0 * ((double) p_ymdh.month) / 9.0)
            - K * ((double) (p_ymdh.month > 2)) + ((double) p_ymdh.day_of_month)
            - 30.0;
}

}
