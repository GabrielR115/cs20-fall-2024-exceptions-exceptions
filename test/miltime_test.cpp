#include <catch2/catch_test_macros.hpp>

#include "miltime.h"

TEST_CASE("Military hour is computed correctly from standard time") {
    Time time1(1, 30, PM);
    REQUIRE(time1.getMilitaryHour() == 13);

    Time time2(11, 45, PM);
    REQUIRE(time2.getMilitaryHour() == 23);

    Time time3(12, 0, AM);
    REQUIRE(time3.getMilitaryHour() == 0);

    Time time4(1, 0, AM);
    REQUIRE(time4.getMilitaryHour() == 1);
}

TEST_CASE("Standard time is converted correctly from military time") {
    Time time1(0, 30);
    REQUIRE(time1.getHour() == 12);
    REQUIRE(time1.getMeridian() == AM);
    REQUIRE(time1.getMilitaryHour() == 0);

    Time time2(11, 45);
    REQUIRE(time2.getHour() == 11);
    REQUIRE(time2.getMeridian() == AM);
    REQUIRE(time2.getMilitaryHour() == 11);

    Time time3(12, 0);
    REQUIRE(time3.getHour() == 12);
    REQUIRE(time3.getMeridian() == PM);
    REQUIRE(time3.getMilitaryHour() == 12);

    Time time4(13, 0);
    REQUIRE(time4.getHour() == 1);
    REQUIRE(time4.getMeridian() == PM);
    REQUIRE(time4.getMilitaryHour() == 13);
}
