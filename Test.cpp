#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "terminal.h"
#include "people.h"
#include "name.h"
#include "utilities.h"
#include "services.h"


TEST_CASE("Testing read_files") {
    Data_center center;
    CHECK(center.read_files() == 1);
}

TEST_CASE("Testing check_valid for invalid member") {
	Data_center center;
    center.read_files();
	CHECK(center.check_valid("1234") == -1);
}

TEST_CASE("Testing check_valid valid member") {
    Data_center center;
    center.read_files();
    CHECK(!center.check_valid("128461839"));
}

TEST_CASE("Testing Member add_service") {
    Member mem;
    Member_service serv;
    CHECK(mem.add_service(serv));
}

TEST_CASE("Testing member report") {
    Data_center center;
    center.read_files();
    center.set_serv_test();
    CHECK(center.person_report("128461839"));
}



