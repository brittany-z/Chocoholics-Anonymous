#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "terminal.h"
#include "people.h"
#include "name.h"
#include "utilities.h"
#include "services.h"

TEST_CASE("Testing check_valid") {
	Data_center center;
	CHECK(center.check_valid("1234", true) == -1);
}


