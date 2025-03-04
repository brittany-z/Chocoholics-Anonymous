#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "terminal.h"
#include "people.h"
#include "name.h"
#include "utilities.h"
#include "services.h"
#define MAXTESTS 100


//Name tests:
TEST_CASE("Testing Name.gen_num()") {

  Name Test;
  for(int i = 0; i < MAXTESTS; i++) {
    CHECK(Test.gen_num(static_cast<char>(i))[0] == static_cast<char>(i));
    CHECK(Test.gen_num(static_cast<char>(i)).length() == 9);
  }

}

TEST_CASE("Testing Name.get_key()") {

  Name Test;
  for(int i = 0; i < MAXTESTS; i++) {
    std::string id = Test.gen_num(static_cast<char>(i));
    CHECK(id == Test.get_key());
  }
  
}

TEST_CASE("Testing Name.copy_name() and Name.get_name()") {

  Name Test;
  std::string name = "Jim Bob";
  Test.copy_name(name);
  CHECK(name == Test.get_name());

  name = "";
  Test.copy_name(name);
  CHECK(name == Test.get_name());

}

//Utilities tests:
TEST_CASE("Testing exceed_max()") {

  CHECK(exceed_max(0, 0) == false);
  CHECK(exceed_max(0, 5) == false);
  CHECK(exceed_max(5, 0) == true);

}

TEST_CASE("Testing equal_max()") {

  CHECK(equal_max(0, 0) == true);
  CHECK(equal_max(0, 5) == false);
  CHECK(equal_max(5, 0) == false);

}

//Address tests:

//Provider tests:
TEST_CASE("Testing provider.add_service()") {

	Provider_service Ptest;
	Provider test;
	CHECK(test.add_service(Ptest) == 1);

}


//Member tests:
TEST_CASE("Testing member.check_week()") {

  Member Test;
  CHECK(Test.check_week() == false);

}

TEST_CASE("Testing member.check_susp()") {

  Member Test;
  CHECK(Test.check_susp() == false);

}

TEST_CASE("Testing Member add_service") {
    Member mem;
    Member_service serv;
    CHECK(mem.add_service(serv));
}

//Service tests:
TEST_CASE("Testing service.get_fee()") {

  Service Test;
  CHECK(Test.get_fee() == 0);

}

//Serv_date tests:
TEST_CASE("Testing Serv_date.compare_date()") {

  Serv_date Test1;
  Serv_date Test2;
  
  CHECK(Test1.compare_date(Test2) == 1);
  CHECK(Test2.compare_date(Test1) == 1);
}


TEST_CASE("Testing Serv_date.check_week()") {

    Serv_date test1;
    test1.set_test();
    Serv_date test2;
    test2.set_false_test();

    CHECK(test1.check_week());
    CHECK(!test2.check_week());
}

//Provider_service tests:


TEST_CASE("Testing Provider_service.get_memkey()") {
	
	Name test_name;
	std::string check = test_name.gen_num('1');
	Service test_serv;
	Serv_date test_date;
	Provider_service test_service(test_name, test_serv, test_date);
	CHECK(check == test_service.get_memkey());

}


TEST_CASE("Testing Provider_service.check_recv_week()") {

	Name test_name;
	Service test_serv;
	Serv_date test_date;
  Provider_service test(test_name, test_serv, test_date);
	CHECK(test.check_recv_week() == true);

}


TEST_CASE("Testing Provider_service.check_recv_week()") {

  Provider_service test1;
  test1.set_false_test();
  Provider_service test2;
  test2.set_true_test();

  CHECK(!test1.check_recv_week());
  CHECK(test2.check_recv_week());

}


//Data_center tests

TEST_CASE("Testing Data_center.add_person()") {

  Data_center center;
  Address test;
  
  CHECK(center.add_person(test, 1) == 1);
  CHECK(center.add_person(test, 2) == 1);
  CHECK(center.add_person(test, 3) == 0);

}


TEST_CASE("Testing Data_center.remove()") {

	Data_center center;
	Address test;
	std::string id = test.gen_num('1');
	CHECK(center.add_person(test, 1) == 1);
	CHECK(center.remove(id) == 0);
	CHECK(center.remove("ruhrohwhyudodis") == -1);

}

TEST_CASE("Testing Data_center.update()") {

  Data_center center;
	CHECK(center.read_files() == 1);
	Address test;
	Address test2;
	std::string id = test.gen_num('1');
	std::string id2 = test2.gen_num('2');
	CHECK(center.add_person(test, 1) == 1);
	CHECK(center.add_person(test2, 2) == 1);
	CHECK(center.update("1invalidID", test) == 0);
	CHECK(center.update("109472837", test) == 1);
	CHECK(center.update("02321234",test) == -1);
	CHECK(center.update("298578401", test2) == 1);
	
}


TEST_CASE("Testing Data_center.read_files()") {
    Data_center center;
    CHECK(center.read_files() == 1);
}

TEST_CASE("Testing Data_center.check_valid()") {
	  Data_center center;
    center.read_files();
	  CHECK(center.check_valid("1234") == -1);

    CHECK(!center.check_valid("128461839"));
}

TEST_CASE("Testing Data_center.person_report()") {
    Data_center center;
    center.read_files();
    center.set_serv_test();
    CHECK(center.person_report("128461839"));
}

