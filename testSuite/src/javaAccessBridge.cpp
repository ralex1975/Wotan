#ifndef TEST_APPLICATION_CPP_
#define TEST_APPLICATION_CPP_

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#include "javaAccessBridge.hpp"

#include "application/processHelper.hpp"

namespace testSuite
{
	void javaAccessBridge::test()
	{
		BOOST_TEST_MESSAGE("Testing test...");

		try
		{
			//BOOL bRet = initializeAccessBridge();
			//if (!bRet)
			//{
			//	MessageBox(NULL, "ERROR at initializeAccessBridge", "ERROR", 0);
			//}
			//shutdownAccessBridge();
		}
		catch (const std::exception&)
		{
			BOOST_ERROR("\n" << " Failed to run test!");
		}

		BOOST_TEST_MESSAGE("test test finished");
	}
	boost::unit_test_framework::test_suite* javaAccessBridge::suite()
	{
		boost::unit_test_framework::test_suite * suite = BOOST_TEST_SUITE("javaAccessBridge Tests");
		suite->add(BOOST_TEST_CASE(&javaAccessBridge::test));
		return suite;
	}
}

#endif