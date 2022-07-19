#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include <cmath>
#include "vdtMath.h"

TEST_CASE("VDT can be imported by fetchcontent", "[vdt]")
{
    constexpr uint32_t size=10;
    double dpvals[size]={1,.9,.8,.6,1e-200,0,
        -0.00004,-.2,-.8,-0.9999999999};
    double *res_dp = new double[size];
    float spvals[size]={1.f,.9f,.8f,.12f,1e-20f,0.f,
        -0.004f,-.2f,-.8f,-0.9999999999f};
    float *res_sp = new float[size];

    SECTION("double precision acos")
    {
        vdt::fast_acosv(size, dpvals, res_dp);
        for (uint32_t i = 0; i < size; i++)
        {
            REQUIRE(res_dp[i] == Catch::Approx(std::acos(dpvals[i])));
        }

        BENCHMARK("sequential std::acos")
        {
            return [](uint32_t sz, double* vs, double* rs) {
                for (uint32_t i = 0; i < sz; i++)
                    rs[i] = std::acos(vs[i]);
            } (size, dpvals, res_dp);
        };

        BENCHMARK("sequential vdt::fast_acos")
        {
            return [](uint32_t sz, double* vs, double* rs) {
                for (uint32_t i = 0; i < sz; i++)
                    rs[i] = vdt::fast_acos(vs[i]);
            } (size, dpvals, res_dp);
        };

        BENCHMARK("vdt::fast_acosv")
        {
            return vdt::fast_acosv(size, dpvals, res_dp);
        };
    }

    SECTION("single precision acos")
    {
        vdt::fast_acosfv(size, spvals, res_sp);
        for (uint32_t i = 0; i < size; i++)
        {
            REQUIRE(res_sp[i] == Catch::Approx(std::acosf(spvals[i])));
        }

        BENCHMARK("sequential std::acos")
        {
            return [](uint32_t sz, float* vs, float* rs) {
                for (uint32_t i = 0; i < sz; i++)
                    rs[i] = std::acosf(vs[i]);
            } (size, spvals, res_sp);
        };

        BENCHMARK("sequential vdt::fast_acos")
        {
            return [](uint32_t sz, float* vs, float* rs) {
                for (uint32_t i = 0; i < sz; i++)
                    rs[i] = vdt::fast_acosf(vs[i]);
            } (size, spvals, res_sp);
        };

        BENCHMARK("vdt::fast_acosfv")
        {
            return vdt::fast_acosfv(size, spvals, res_sp);
        };
    }
}
