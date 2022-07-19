#include <catch2/catch.hpp>

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
            REQUIRE(res_dp[i] == Approx(std::acos(dpvals[i])));
        }
    }

    SECTION("single precision acos")
    {
        vdt::fast_acosfv(size, spvals, res_sp);
        for (uint32_t i = 0; i < size; i++)
        {
            REQUIRE(res_sp[i] == Approx(std::acosf(spvals[i])));
        }
    }
}
