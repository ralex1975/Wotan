#pragma once
#ifndef TEST_JAB_HPP_
#define TEST_JAB_HPP_

#include <boost/test/unit_test.hpp>

#include <bridge/AccessBridgePackages.h>

namespace testSuite
{
	class javaAccessBridge
	{
	public:
		static void test();
		static boost::unit_test_framework::test_suite* suite();
	};
}

#endif
