#ifndef TEST_APPLICATION_CPP_
#define TEST_APPLICATION_CPP_

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#include "application.hpp"

#include "application/processHelper.hpp"

namespace testSuite
{
	void application::getProcessIds()
	{
		BOOST_TEST_MESSAGE("Testing getProcessIds...");

		try
		{
			Wotan::processHelper hlp;
			std::list<Wotan::pid> pids;
			std::string p("svchost.exe");
			BOOST_TEST_MESSAGE("looking for processes " + p);
			hlp.getProcessIds(pids, p);
			BOOST_TEST_MESSAGE("found " + boost::lexical_cast<std::string>(pids.size()) + " processes");
		}
		catch (const std::exception&)
		{
			BOOST_ERROR("\n" << " Failed to write log!");
		}

		BOOST_TEST_MESSAGE("test getProcessIds finished");
	}
	void application::createProcess()
	{
		BOOST_TEST_MESSAGE("Testing createProcess...");

		try
		{
			Wotan::processHelper hlp;
			std::string name("C:\\Windows\\System32\\notepad.exe");
			BOOST_TEST_MESSAGE("creating new instance: " + name);
			Wotan::pid p = hlp.launchProcess(name);
			BOOST_TEST_MESSAGE("created process with id " + boost::lexical_cast<std::string>(p) + " processes");
			unsigned int exitCode;

 			if (hlp.terminateProcess(p, exitCode))
			{
				BOOST_TEST_MESSAGE("process id " + 
					boost::lexical_cast<std::string>(p) + 
					" stopped with exit code " + 
					boost::lexical_cast<std::string>(exitCode));
			}
		}
		catch (const std::exception&)
		{
			BOOST_ERROR("\n" << " Failed to write log!");
		}

		BOOST_TEST_MESSAGE("test createProcess finished");
	}
	void application::getProcessWindows()
	{
		BOOST_TEST_MESSAGE("Testing createProcess...");

		try
		{
			// connect the gateway
			std::string appLocation = "C:\\Jts\\ibgateway\\964\\";
			std::string appName = "ibgateway.exe";
			std::list<Wotan::pid> processes;
			Wotan::processHelper hlp;
			hlp.getProcessIds(processes, appName);

			if (processes.size() != 0)
			{
				BOOST_ERROR("\n" << " process already started !");
				return;
			}
			else
			{
				processes.push_back(hlp.launchProcess(appLocation + appName));				// launch a new instance
				boost::this_thread::sleep(boost::posix_time::milliseconds(5000));			// sleep
			}

			auto windows = hlp.getToplevelWindows(*processes.begin());

			for (auto & win : windows)
			{
				if (win.name == "IB Gateway")
				{
					auto t = hlp.getChildWindows(win);
				}
			}
		}
		catch (const std::exception&)
		{
			BOOST_ERROR("\n" << " Failed to write log!");
		}

		BOOST_TEST_MESSAGE("test createProcess finished");
	}

	boost::unit_test_framework::test_suite* application::suite()
	{
		boost::unit_test_framework::test_suite * suite = BOOST_TEST_SUITE("application Tests");
		suite->add(BOOST_TEST_CASE(&application::getProcessIds));
		suite->add(BOOST_TEST_CASE(&application::createProcess));
		suite->add(BOOST_TEST_CASE(&application::getProcessWindows));
		return suite;
	}
}

#endif