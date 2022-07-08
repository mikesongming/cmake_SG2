# cmake_SG2

A cmake project for SG2 algorithm, a translation from the original Autotools project
[gschwind/sg2](https://github.com/gschwind/sg2).

## original building process

1. configure: -std=c++11 -fPIC -O3 -DSG2_HAVE_VDT
2. build ligsg2.so:
    - sources: src/{sg2.cxx,sg2_date.cxx,sg2_geopoint.cxx,sg2_topocentric.cxx,sg2_data_handler.cxx,sg2_geocentric.cxx,sg2_utils.cxx}, resources/geocentric.data
    - includes: src/{sg2.hxx,sg2_date.hxx,sg2_geocentric.hxx,sg2_math.hxx,sg2_typedef.hxx,sg2_data_handler.hxx,sg2_err.hxx,sg2_geopoint.hxx,sg2_topocentric.hxx,sg2_utils.hxx}
3. bind python:
    - deps: python/pysg2.cxx,third-parties/python-bind-helper/python-bind-helper.hxx
    - exports: sun_position, sun_rise, sg2::ellips, sg2.error, ymdh_to_jd, jd_to_ymdh, topocentric_correction_refraction_SAE, topocentric_correction_refraction_ZIM
4. optional exectuable:
    - sg2_query: src/sg2_query.cxx
    - sg2_convert_data: src/sg2_convert_data.cxx
    - sg2_benchmark: src/sg2_benchmark.cxx
