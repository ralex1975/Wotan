#pragma once

#include "StdAfx.h"

#include "historicalDataClient.hpp"

namespace Wotan
{
	void historicalDataClient::historicalData(TickerId reqId, const std::string& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps) 
	{
		data dt;

		dt.date_		= date		;
		dt.open_		= open		;
		dt.high_		= high		;
		dt.low_			= low		;
		dt.close_		= close		;
		dt.volume_		= volume	;
		dt.barCount_	= barCount	;
		dt.WAP_			= WAP		;
		dt.hasGaps_		= hasGaps	;

		data_.push_back(dt);

		if (state_ = ST_HISTORICALDATAREQUESTS)
		{
			// finished ?
			int i = 0;
		}
	}

	historicalDataClient::historicalDataClient()
	{
		facet_ = new boost::posix_time::time_facet();
		facet_->format("%Y%m%d %H:%M:%S");
	}

	historicalDataClient::~historicalDataClient()
	{
		delete facet_;
	}

	void historicalDataClient::request(
		const Contract & c, 
		const boost::posix_time::ptime & endDate, 
		const std::string & durationStr, 
		const std::string & barSizeSetting, 
		whatToShow wts)
	{
		std::stringstream stream;
		stream.imbue(std::locale(std::locale::classic(), facet_));
		stream << endDate;

		client_->reqHistoricalData(4001, c, stream.str().c_str(), 
			durationStr, barSizeSetting, 
			Wotan::enumManager<whatToShow>::toString(wts) , 
			1, 1, TagValueListSPtr());

		state_ = ST_HISTORICALDATAREQUESTS_ACK;
	}
}
