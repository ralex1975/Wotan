#pragma once
#ifndef TEST_APPLICATION_HPP_
#define TEST_APPLICATION_HPP_

#include <boost/test/unit_test.hpp>

namespace testSuite
{
	class application
	{
	public:
		static void getProcessIds();
		static void createProcess();
		static void getProcessWindows();
		static boost::unit_test_framework::test_suite* suite();
	};
}

#endif
