#include <catch2/catch.hpp>

#if defined(SG2_RESOURCES)

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

#include "sg2_geocentric_data.hpp"
#include <cstdint>
#include <fstream>
#include <tuple>
#include <vector>

struct GeocentricDataReader
{
    int64_t offset, delta, count;
    std::vector<std::tuple<double,double,double>> top10_records;

    GeocentricDataReader(const std::string &gc_data_file)
    {
        std::ifstream ifs_gc_data;
        ifs_gc_data.open(gc_data_file, std::ios::binary | std::ios::in);

        ifs_gc_data.read(reinterpret_cast<char *>(&offset), 8);
        ifs_gc_data.read(reinterpret_cast<char *>(&delta), 8);
        ifs_gc_data.read(reinterpret_cast<char *>(&count), 8);

        for (size_t i = 0; i < 10; i++)
        {
            double sinL, cosL, R;
            ifs_gc_data.read(reinterpret_cast<char *>(&sinL), 8);
            ifs_gc_data.read(reinterpret_cast<char *>(&cosL), 8);
            ifs_gc_data.read(reinterpret_cast<char *>(&R), 8);

            top10_records.push_back(std::make_tuple(sinL, cosL, R));
        }
    };
};


TEST_CASE("Geocentric data IO by NASM", "[sg2][nasm]")
{
    std::string gc_data_file = MACRO_STRINGIFY(SG2_RESOURCES) "/geocentric.data";
    GeocentricDataReader gc_data(gc_data_file);

    UNSCOPED_INFO("Read binary data: " << gc_data_file);
    UNSCOPED_INFO("offset: " << gc_data.offset << ", "
        << "delta: "  << gc_data.delta << ", "
        << "count: " << gc_data.count);
    for (size_t i = 0; i < 10; i++)
    {
        double sinL, cosL, R;
        std::tie(sinL, cosL, R) = gc_data.top10_records[i];
        UNSCOPED_INFO("sinL: " << sinL << ", "
                    << "cosL: " << cosL << ", "
                    << "R: " << R);
    }

    REQUIRE(gc_data.count > 10);
    REQUIRE(gc_data.top10_records.size() == 10);

    SECTION("NASM read metadata correctly")
    {
        REQUIRE(sg2::_geocentric_data_offset() == gc_data.offset);
        REQUIRE(sg2::_geocentric_data_delta()  == gc_data.delta );
        REQUIRE(sg2::_geocentric_data_count()  == gc_data.count );
    }
    SECTION("NASM read top 10 records correctly")
    {
        for (size_t i = 0; i < 10; i++)
        {
            double sinL, cosL, R;
            std::tie(sinL, cosL, R) = gc_data.top10_records[i];
            
            REQUIRE(sg2::_geocentric_data_sinL(i) == Approx(sinL).margin(1e-8));
            REQUIRE(sg2::_geocentric_data_cosL(i) == Approx(cosL).margin(1e-8));
            REQUIRE(sg2::_geocentric_data_R(i) == Approx(R).margin(1e-8));

            auto t = sg2::_geocentric_data_tuple(i);
            REQUIRE(std::get<0>(t) == Approx(sinL).margin(1e-8));
            REQUIRE(std::get<1>(t) == Approx(cosL).margin(1e-8));
            REQUIRE(std::get<2>(t) == Approx(R).margin(1e-8));
        }
    }
    SECTION("NASM read valid 'sinL', 'cosL'")
    {
        for (size_t i = 0; i < sg2::_geocentric_data_count(); i++)
        {
            double sinL = sg2::_geocentric_data_sinL(i);
            double cosL = sg2::_geocentric_data_cosL(i);
            REQUIRE(sinL*sinL+cosL*cosL == Approx(1));
        }
    }
}

#else

SCENARIO("Geocentric data IO by NASM", "[sg2][nasm]")
{
    INFO("No resource binary file");
    GIVEN("No resource binary file")
    {
        CHECK(false);
    }
}

#endif // SG2_RESOURCES
