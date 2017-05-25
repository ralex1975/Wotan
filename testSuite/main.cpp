#ifndef MAIN_CPP_
#define MAIN_CPP_

#define BOOST_LIB_NAME boost_unit_test_framework
#include <boost/config/auto_link.hpp>
#undef BOOST_LIB_NAME

#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>

#include "application.hpp"
#include "javaAccessBridge.hpp"
#include "datetime.hpp"
#include "tws.hpp"

// WARN: do not include in a namespace
boost::unit_test::test_suite * init_unit_test_suite(int, char*[])
{
	int argc = boost::unit_test::framework::master_test_suite().argc;
	char ** argv = boost::unit_test::framework::master_test_suite().argv;

	std::ostringstream header;
	header << "launching Wotan test suite " << std::endl;

	std::string rule = std::string(41, '=');
	BOOST_TEST_MESSAGE(rule);
	BOOST_TEST_MESSAGE(header.str());
	BOOST_TEST_MESSAGE(rule);

	boost::unit_test::test_suite * test = BOOST_TEST_SUITE("Wotan test suite");

	// individual tests
	test->add(testSuite::application::suite());
	test->add(testSuite::datetime::suite());
	test->add(testSuite::javaAccessBridge::suite());
	test->add(testSuite::tws::suite());

	return test;
}

#endif