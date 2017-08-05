#pragma once
#ifndef HISTORICAL_DATA_CLIENT_HPP_
#define HISTORICAL_DATA_CLIENT_HPP_


#include <iostream>
#include <locale>
#include <string>
#include <list>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include "tws/client.hpp"
#include "tws/enums/whatToShow.hpp"
#include "tws/time/duration.hpp"
#include "tws/time/bar.hpp"

namespace Wotan
{
	struct data
	{
		std::string date_	;
		double open_		;
		double high_		;
		double low_			;
		double close_		;
		int volume_			;
		int barCount_		;
		double WAP_			;
		int hasGaps_		;
	};

	class historicalDataClient : public client
	{

	public:

		historicalDataClient();
		~historicalDataClient();

		void request(const Contract & c, const boost::posix_time::ptime & endDate, 
			const duration & dur, bar::size sz, whatToShow wts = whatToShow::TRADES);

	protected:
		virtual void historicalData(TickerId reqId, const std::string & date, double open, double high,
			double low, double close, int volume, int barCount, double WAP, int hasGaps);

	private:
		boost::posix_time::time_facet * facet_;
		std::list<data> data_;
	};
}

#endif