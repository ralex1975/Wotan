#pragma once
#ifndef TEST_DATETIME_HPP_
#define TEST_DATETIME_HPP_

#include <boost/test/unit_test.hpp>

namespace testSuite
{
	class datetime
	{
	public:
		static void parseDatetime();
		static boost::unit_test_framework::test_suite* suite();
	};
}

#endif
