#include "doctest.h"
#include <iostream>
#include <sstream>
#include "NumberWithUnits.hpp"
using namespace ariel;

#include <string>
using namespace std;


ifstream units_file{"units.txt"};


TEST_CASE("checks operator <<(cout)"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits n1(789, "USD");

    stringstream stream;

    stream << n1;
    CHECK((stream.str() == "789[USD]") == true);
    stream.str("");

    NumberWithUnits n2(600, "cm");

    stream << n2 << ", " << n1;
    CHECK((stream.str() == "600[cm], 789[USD]") == true);


    stream.str("");

}


TEST_CASE("checks operator+(const NumberWithUnits operator+(const NumberWithUnits& other)"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n1(4, "km");
    NumberWithUnits n2(600, "cm");

    NumberWithUnits n3(8, "hour");
    NumberWithUnits n4(679, "min");
    
    //GOOD cases
    CHECK_NOTHROW(n1 + n2);
    CHECK_NOTHROW(n2 + n1);
    CHECK_NOTHROW(n3 + n4);
    CHECK_NOTHROW(n4 + n3);

    //BAD cases
    CHECK_THROWS(n1 + n3);
    CHECK_THROWS(n2 + n3);
    CHECK_THROWS(n3 + n2);
    CHECK_THROWS(n1 + n4);

}

TEST_CASE("checks operator-(const NumberWithUnits& other)"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n1(4, "km");
    NumberWithUnits n2(600, "cm");

    NumberWithUnits n3(8, "hour");
    NumberWithUnits n4(679, "min");
    
    //GOOD cases
    CHECK_NOTHROW(n1 - n2);
    CHECK_NOTHROW(n2 - n1);
    CHECK_NOTHROW(n3 - n4);
    CHECK_NOTHROW(n4 - n3);

    //BAD cases
    CHECK_THROWS(n1 - n3);
    CHECK_THROWS(n2 - n3);
    CHECK_THROWS(n3 - n2);
    CHECK_THROWS(n1 - n4);

}

TEST_CASE("checks operator+="){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n1(4, "km");
    NumberWithUnits n2(600, "cm");

    NumberWithUnits n3(8, "hour");
    NumberWithUnits n4(679, "min");
    
    //GOOD cases
    CHECK_NOTHROW(n1 += n2);
    CHECK_NOTHROW(n2 += n1);
    CHECK_NOTHROW(n3 += n4);
    CHECK_NOTHROW(n4 += n3);

    //BAD cases
    CHECK_THROWS(n1 += n3);
    CHECK_THROWS(n2 += n3);
    CHECK_THROWS(n3 += n2);
    CHECK_THROWS(n1 += n4);

}

TEST_CASE("checks operator++ (prefix)"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n1(4, "km");
    NumberWithUnits n2(600, "cm");

    NumberWithUnits n3(8, "hour");
    NumberWithUnits n4(679, "min");
    
    double temp = ++n1._unit_num;
    CHECK(temp == 5);

    double temp1 = ++n2._unit_num;
    CHECK(temp1 == 601);
    
    double temp2 = ++n3._unit_num;
    CHECK(temp2 == 9);

    double temp3 = ++n4._unit_num;
    CHECK(temp3 == 680);

}
