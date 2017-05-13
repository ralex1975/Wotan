#ifndef TEST_APPLICATION_CPP_
#define TEST_APPLICATION_CPP_

#include <boost/lexical_cast.hpp>

#include "application.hpp"

#include "application/processHelper.hpp"

namespace testSuite
{
	void application::getProcessIds()
	{
		BOOST_TEST_MESSAGE("Testing getProcessIds...");

		try
		{
			Wotan::processHelper ph;
			std::list<unsigned int> pids;
			std::string p("svchost.exe");
			BOOST_TEST_MESSAGE("looking for processes " + p);
			ph.getProcessIds(pids, p);
			BOOST_TEST_MESSAGE("found " + boost::lexical_cast<std::string>(pids.size()) + " processes");
		}
		catch (const std::exception&)
		{
			BOOST_ERROR("\n" << " Failed to write log!");
		}

		BOOST_TEST_MESSAGE("test getProcessIds done");
	}

	boost::unit_test_framework::test_suite* application::suite()
	{
		boost::unit_test_framework::test_suite * suite = BOOST_TEST_SUITE("application Tests");
		suite->add(BOOST_TEST_CASE(&application::getProcessIds));
		return suite;
	}
}



#endif