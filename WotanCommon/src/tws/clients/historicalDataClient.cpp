#pragma once

#include "StdAfx.h"

#include "historicalDataClient.hpp"

namespace Wotan
{
	void historicalDataClient::historicalData(TickerId reqId, const std::string& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps) 
	{
		// when the ts is finished, we receive a date in the format
		// finished-20141201  00:00:00-20150101  00:00:00
		// we need to return a code to the calling procedure accordingly
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
		const duration & dur,
		bar::size sz, 
		whatToShow wts)
	{
		std::stringstream dtStream;
		dtStream.imbue(std::locale(std::locale::classic(), facet_));
		dtStream << endDate;

		std::stringstream durStream;
		durStream << dur;

		client_->reqHistoricalData(4001, c, 
			dtStream.str().c_str(), durStream.str(),
			Wotan::enumManager<whatToShow>::toString(wts),
			Wotan::enumManager<bar::size>::toString(sz),
			1, 1, TagValueListSPtr());

		state_ = ST_HISTORICALDATAREQUESTS_ACK;
	}
}