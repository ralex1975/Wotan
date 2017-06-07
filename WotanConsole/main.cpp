#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <list>
#include <exception>
#include <string>
#include <string.h>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#ifdef _WIN32
#include "StdAfx.hpp"
#include <Windows.h>
#include <tlhelp32.h>
#else
#include <unistd.h>
#endif

#include "tws/clients/historicalDataClient.hpp"
#include "tws/enum.hpp"
#include "application/logger.hpp"

boost::condition_variable cv_;
std::atomic<bool> terminate_;
boost::mutex m_;

void loop(Wotan::client & cl)
{
	while (cl.isConnected())
	{
		cl.processMessages();
	}

	terminate_ = true;
}

int main(int argc, char ** argv)
{
	int ret = 1;

	try
	{
		Wotan::logger::initialize("dtccConsole_%Y%m%d.log", Wotan::severity::info);
		LOG_INFO() << "Application is starting...";

		auto cl = Wotan::historicalDataClient();

		if (cl.connect("127.0.0.1", 4001, 0))
		{
			boost::thread(boost::bind(loop, std::ref(cl))).detach();
		}
		
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

		Contract contract;
		contract.symbol = "EUR";
		contract.secType = Wotan::enumManager<Wotan::secType::secType>::toString(Wotan::secType::CASH);
		contract.currency = "USD";
		contract.exchange = "IDEALPRO";

		boost::posix_time::ptime dt(boost::gregorian::date(2015, boost::gregorian::Jan, 01),
			boost::posix_time::time_duration(00, 00, 00));

		cl.request(contract, dt, "1 M", "1 day", Wotan::whatToShow::MIDPOINT);

		// barrier
		boost::unique_lock<boost::mutex> lk(m_);
		while (!terminate_) cv_.wait(lk);

		LOG_INFO() << "Application is shutting down...";
	}
	catch (std::exception & ex)
	{
		LOG_ERROR() << "An error has occurred: " << ex.what();
	}

	system("pause");
	return ret;
}
#endif
