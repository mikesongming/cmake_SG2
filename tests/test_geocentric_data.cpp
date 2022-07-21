#include <catch2/catch_all.hpp>

#if defined(SG2_RESOURCES)

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

#include <cstdint>
#include <cmath>
#include <fstream>
#include <set>
#include <tuple>
#include <vector>

#include "sg2_geocentric_data.hpp"

using Catch::Matchers::Approx;

struct GeocentricDataReader
{
    int64_t offset, delta, count;
    std::vector<std::tuple<double,double,double>> records;

    GeocentricDataReader(const std::string &gc_data_file)
    {
        std::ifstream ifs_gc_data;
        ifs_gc_data.open(gc_data_file, std::ios::binary | std::ios::in);

        ifs_gc_data.read(reinterpret_cast<char *>(&offset), 8);
        ifs_gc_data.read(reinterpret_cast<char *>(&delta), 8);
        ifs_gc_data.read(reinterpret_cast<char *>(&count), 8);

        for (size_t i = 0; i < count; i++)
        {
            double sinL, cosL, R;
            ifs_gc_data.read(reinterpret_cast<char *>(&sinL), 8);
            ifs_gc_data.read(reinterpret_cast<char *>(&cosL), 8);
            ifs_gc_data.read(reinterpret_cast<char *>(&R), 8);

            records.push_back(std::make_tuple(sinL, cosL, R));
        }
    };
};


SCENARIO("validate geocentric data loaded by NASM", "[sg2][nasm]")
{
    std::string gc_data_file = MACRO_STRINGIFY(SG2_RESOURCES) "/geocentric.data";
    GeocentricDataReader gc_data(gc_data_file);

    GIVEN("records read by fstream") {

        THEN("metadata is equal") {
            REQUIRE(sg2::_geocentric_data_offset() == gc_data.offset);
            REQUIRE(sg2::_geocentric_data_delta()  == gc_data.delta );
            REQUIRE(sg2::_geocentric_data_count()  == gc_data.count );
        }
        THEN("sampled values are equal") {
            constexpr unsigned size = 10;
            auto l = GENERATE_COPY(take(size, random(0, static_cast<int>(gc_data.count))));
            INFO("line: " << l);

            double sinL, cosL, R;
            std::tie(sinL, cosL, R) = gc_data.records[l];
            std::vector<double> expected {sinL, cosL, R};
            
            std::vector<double> nasm_vals {sg2::_geocentric_data_sinL(l),
                sg2::_geocentric_data_cosL(l), sg2::_geocentric_data_R(l)};
            
            REQUIRE_THAT(nasm_vals, Approx(expected).margin(1e-9));
        }
        THEN("square sum of sinL and cosL equals 1.0")
        {
            std::set<int> square_sums;

            for (size_t i = 0; i < sg2::_geocentric_data_count(); i++)
            {
                double sinL = sg2::_geocentric_data_sinL(i);
                double cosL = sg2::_geocentric_data_cosL(i);
                square_sums.insert(static_cast<int>(std::round((sinL*sinL+cosL*cosL))));
            }

            REQUIRE(square_sums.size() == 1);
            REQUIRE((*square_sums.begin()) == 1);
        }
    }
}

#else

SCENARIO("validate geocentric data loaded by NASM", "[sg2][nasm]")
{
    INFO("No resource binary file");
    GIVEN("No resource binary file")
    {
        CHECK(false);
    }
}

#endif // SG2_RESOURCES
