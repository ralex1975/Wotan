#ifndef TEST_TWS_CPP_
#define TEST_TWS_CPP_

#include <boost/thread/thread.hpp> 

#include "tws.hpp"

namespace testSuite
{
	void tws::test()
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
	boost::unit_test_framework::test_suite* tws::suite()
	{
		boost::unit_test_framework::test_suite * suite = BOOST_TEST_SUITE("javaAccessBridge Tests");
		suite->add(BOOST_TEST_CASE(&tws::test));
		return suite;
	}
}

#endif