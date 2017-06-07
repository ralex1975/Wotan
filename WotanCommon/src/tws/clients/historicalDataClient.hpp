#pragma once
#ifndef HISTORICAL_DATA_CLIENT_HPP_
#define HISTORICAL_DATA_CLIENT_HPP_

#include "tws/client.hpp"

#include <iostream>
#include <locale>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include "pattern/enumManager.hpp"

namespace Wotan
{
	struct data
	{
		std::string date_;
		double open_;
		double high_;
		double low_;
		double close_;
		int volume_;
		int barCount_;
		double WAP_;
		int hasGaps_;
	};

	enum whatToShow
	{
		TRADES = 1,
		MIDPOINT = 2,
		BID = 3,
		ASK = 4,
		BID_ASK = 5,
		HISTORICAL_VOLATILITY = 6,
		OPTION_IMPLIED_VOLATILITY = 7,
		unknown = 0
	};

	template <>
	const std::vector<std::pair<whatToShow, std::string> >
		Wotan::enumConversions<whatToShow>::enumToStringVector =
	{
		{ whatToShow::TRADES						, "TRADES" }
		,{ whatToShow::MIDPOINT						, "MIDPOINT" }
		,{ whatToShow::BID							, "BID" }
		,{ whatToShow::ASK							, "ASK" }
		,{ whatToShow::BID_ASK						, "BID_ASK" }
		,{ whatToShow::HISTORICAL_VOLATILITY		, "HISTORICAL_VOLATILITY" }
		,{ whatToShow::OPTION_IMPLIED_VOLATILITY	, "OPTION_IMPLIED_VOLATILITY" }
	};

	class historicalDataClient : public client
	{

	public:

		historicalDataClient();
		~historicalDataClient();

		void request(const Contract & c, const boost::posix_time::ptime & endDate, 
			const std::string& durationStr, const std::string&  barSizeSetting, whatToShow wts = whatToShow::TRADES);

	protected:
		virtual void historicalData(TickerId reqId, const std::string& date, double open, double high,
			double low, double close, int volume, int barCount, double WAP, int hasGaps);

	private:
		boost::posix_time::time_facet * facet_;
		std::vector<data> data_;
	};
}

#endif