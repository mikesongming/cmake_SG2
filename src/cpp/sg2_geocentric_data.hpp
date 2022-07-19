#pragma once

#include <cstdint>
#include <tuple>

extern "C" {
    int64_t _sg2_gc_data_sz();
    int64_t _sg2_gc_offset();
    int64_t _sg2_gc_delta();
    int64_t _sg2_gc_count();
    double _sg2_gc_sinL(unsigned l);
    double _sg2_gc_cosL(unsigned l);
    double _sg2_gc_R(unsigned l);
    int64_t* _sg2_gc_tuple(unsigned l);
}

namespace sg2
{

inline int64_t _geocentric_data_byte_size() {
    return _sg2_gc_data_sz();
}

inline int64_t _geocentric_data_offset() {
    return _sg2_gc_offset();
}

inline int64_t _geocentric_data_delta() {
    return _sg2_gc_delta();
}

inline int64_t _geocentric_data_count() {
    return _sg2_gc_count();
}

inline double _geocentric_data_sinL(unsigned l)
{
    return _sg2_gc_sinL(l);
}

inline double _geocentric_data_cosL(unsigned l)
{
    return _sg2_gc_cosL(l);
}

inline double _geocentric_data_R(unsigned l)
{
    return _sg2_gc_R(l);
}

inline std::tuple<double, double, double> _geocentric_data_tuple(unsigned l)
{
    int64_t* tp = _sg2_gc_tuple(l);
    return std::make_tuple(
        *(reinterpret_cast<double*>(tp)),
        *(reinterpret_cast<double*>(tp+1)),
        *(reinterpret_cast<double*>(tp+2))
    );
}

} // namespace sg2

