#ifndef TEST_DATETIME_CPP_
#define TEST_DATETIME_CPP_

#include <boost/date_time/posix_time/posix_time.hpp>

#include "datetime.hpp"

namespace testSuite
{
	void datetime::parseDatetime()
	{
		BOOST_TEST_MESSAGE("Testing parseDatetime...");

		try
		{
			// expect 20170522 19:33:49
			boost::posix_time::ptime dt(boost::gregorian::date(2002, boost::gregorian::Jan, 10),
				boost::posix_time::time_duration(22, 10, 3));

			boost::posix_time::time_facet * facet = new boost::posix_time::time_facet();
			facet->format("%Y%m%d %H:%M:%S");

			std::stringstream stream;
			stream.imbue(std::locale(std::locale::classic(), facet));
			stream << dt;
			std::string t = stream.str();

			if (t != "20020110 22:10:03") 
			{
				throw std::exception("failed to parse datetime");
			}

		}
		catch (const std::exception & ex)
		{
			BOOST_ERROR("\n" << " error: " << ex.what());
		}

		BOOST_TEST_MESSAGE("test parseDatetime finished");
	}
	boost::unit_test_framework::test_suite* datetime::suite()
	{
		boost::unit_test_framework::test_suite * suite = BOOST_TEST_SUITE("datetime Tests");
		suite->add(BOOST_TEST_CASE(&datetime::parseDatetime));
		return suite;
	}
}

#endif