#include "vdtMath.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    constexpr uint32_t size=10;
    
    //dp
    double dpvals[size]={1,.9,.8,.6,1e-200,0,-0.00004,-.2,-.8,-0.9999999999};
    double *res_dp = new double[size];
    std::cout << "Double Precision" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "i\tdiff\tnon-vec\tvec" << std::endl;

    vdt::fast_acosv(size, dpvals, res_dp);
    for (uint32_t i = 0; i < size; i++)
    {
        std::cout << i
                  << "\t" << res_dp[i] - vdt::fast_acos(dpvals[i])
                  << "\t" << vdt::fast_acos(dpvals[i])
                  << "\t" << res_dp[i]
                  << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    //sp 
    float spvals[size]={1.f,.9f,.8f,.12f,1e-20f,0.f,-0.004f,-.2f,-.8f,-0.9999999999f};
    float *res_sp = new float[size];
    std::cout << "Single Precision" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "i\tdiff\tnon-vec\tvec" << std::endl;
    
    vdt::fast_acosfv(size, spvals, res_sp);
    for (uint32_t i = 0; i < size; i++)
    {
        std::cout << i
                  << "\t" << res_sp[i] - vdt::fast_acosf(spvals[i])
                  << "\t" << vdt::fast_acosf(spvals[i])
                  << "\t" << res_sp[i]
                  << std::endl;
    }

    return 0;
}
