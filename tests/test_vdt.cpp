#include <catch2/catch_all.hpp>

#include <algorithm>
#include <cmath>
#include <vector>
#include "vdtMath.h"

using Catch::Matchers::Approx;

SCENARIO("compare VDT and libm outputs", "[vdt][approx]")
{
    constexpr unsigned size = 10;
    auto direct_dpvals_g = GENERATE(chunk(size, take(size, random(-10.0, 10.0))));
    auto inverse_dpvals_g = GENERATE(chunk(size, take(size, random(-1.0, 1.0))));
    auto direct_spvals_g = GENERATE(chunk(size, take(size, random(-10.0f, 10.0f))));
    auto inverse_spvals_g = GENERATE(chunk(size, take(size, random(-1.0f, 1.0f))));

    double *direct_dpvals = new double[size];
    double *inverse_dpvals = new double[size];
    float *direct_spvals = new float[size];
    float *inverse_spvals = new float[size];

    std::copy(direct_dpvals_g.begin(), direct_dpvals_g.end(), direct_dpvals);
    std::copy(inverse_dpvals_g.begin(), inverse_dpvals_g.end(), inverse_dpvals);
    std::copy(direct_spvals_g.begin(), direct_spvals_g.end(), direct_spvals);
    std::copy(inverse_spvals_g.begin(), inverse_spvals_g.end(), inverse_spvals);

    double *res_dp = new double[size];
    float *res_sp = new float[size];

    GIVEN("acos") {
        WHEN("double precision margin 1e-9") {
            constexpr double dp_margin = 1e-9;
            vdt::fast_acosv(size, inverse_dpvals, res_dp);

            std::vector<double> vdt_res_dp(res_dp, res_dp+size);
            std::vector<double> expected_res_dp(size); 
            for (unsigned i = 0; i < size; i++)
                expected_res_dp[i] = std::acos(inverse_dpvals[i]);

            REQUIRE_THAT(vdt_res_dp, Approx(expected_res_dp).margin(dp_margin));
        }

        WHEN("single precision margin 1e-9") {
            constexpr float sp_margin = 1e-9;
            vdt::fast_acosfv(size, inverse_spvals, res_sp);

            std::vector<float> vdt_res_sp(res_sp, res_sp+size);
            std::vector<float> expected_res_sp(size);
            for (unsigned i = 0; i < size; i++)
                expected_res_sp[i] = std::acosf(inverse_spvals[i]);
            
            REQUIRE_THAT(vdt_res_sp, Approx(expected_res_sp).margin(sp_margin));
        }
    }
}

SCENARIO("benchmark VDT and libm", "[vdt][benchmark]")
{
    constexpr unsigned size = 10;
    auto direct_dpvals_g = GENERATE(chunk(size, take(size, random(-10.0, 10.0))));
    auto inverse_dpvals_g = GENERATE(chunk(size, take(size, random(-1.0, 1.0))));
    auto direct_spvals_g = GENERATE(chunk(size, take(size, random(-10.0f, 10.0f))));
    auto inverse_spvals_g = GENERATE(chunk(size, take(size, random(-1.0f, 1.0f))));

    double *direct_dpvals = new double[size];
    double *inverse_dpvals = new double[size];
    float *direct_spvals = new float[size];
    float *inverse_spvals = new float[size];

    std::copy(direct_dpvals_g.begin(), direct_dpvals_g.end(), direct_dpvals);
    std::copy(inverse_dpvals_g.begin(), inverse_dpvals_g.end(), inverse_dpvals);
    std::copy(direct_spvals_g.begin(), direct_spvals_g.end(), direct_spvals);
    std::copy(inverse_spvals_g.begin(), inverse_spvals_g.end(), inverse_spvals);

    double *res_dp = new double[size];
    float *res_sp = new float[size];

    GIVEN("acos") {
        WHEN("double precision") {
            BENCHMARK("sequential std::acos")
            {
                return [](unsigned sz, double* vs, double* rs) {
                    for (unsigned i = 0; i < sz; i++)
                        rs[i] = std::acos(vs[i]);
                } (size, inverse_dpvals, res_dp);
            };

            BENCHMARK("sequential vdt::fast_acos")
            {
                return [](unsigned sz, double* vs, double* rs) {
                    for (unsigned i = 0; i < sz; i++)
                        rs[i] = vdt::fast_acos(vs[i]);
                } (size, inverse_dpvals, res_dp);
            };

            BENCHMARK("vdt::fast_acosv")
            {
                return vdt::fast_acosv(size, inverse_dpvals, res_dp);
            };
        }

        WHEN("single precision") {
            BENCHMARK("sequential std::acos")
            {
                return [](unsigned sz, float* vs, float* rs) {
                    for (unsigned i = 0; i < sz; i++)
                        rs[i] = std::acosf(vs[i]);
                } (size, inverse_spvals, res_sp);
            };

            BENCHMARK("sequential vdt::fast_acos")
            {
                return [](unsigned sz, float* vs, float* rs) {
                    for (unsigned i = 0; i < sz; i++)
                        rs[i] = vdt::fast_acosf(vs[i]);
                } (size, inverse_spvals, res_sp);
            };

            BENCHMARK("vdt::fast_acosfv")
            {
                return vdt::fast_acosfv(size, inverse_spvals, res_sp);
            };
        }
    }
}
