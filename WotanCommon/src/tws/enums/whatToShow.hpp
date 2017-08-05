#pragma once
#ifndef TWS_ENUMS_WHATTOSHOW_HPP_
#define TWS_ENUMS_WHATTOSHOW_HPP_

#include "pattern/enumManager.hpp"

namespace Wotan
{
	// see https://interactivebrokers.github.io/tws-api/basic_contracts.html#fop
	enum whatToShow
	{
		TRADES = 1,
		MIDPOINT = 2,
		BID = 3,
		ASK = 4,
		BID_ASK = 5,
		HISTORICAL_VOLATILITY = 6,
		OPTION_IMPLIED_VOLATILITY = 7
	};

	template <>
	const std::vector<std::pair<whatToShow, std::string> >
		enumConversions<whatToShow>::enumToStringVector =
	{
		 { whatToShow::TRADES					, "TRADES" }
		,{ whatToShow::MIDPOINT					, "MIDPOINT" }
		,{ whatToShow::BID						, "BID" }
		,{ whatToShow::ASK						, "ASK" }
		,{ whatToShow::BID_ASK					, "BID_ASK" }
		,{ whatToShow::HISTORICAL_VOLATILITY	, "HISTORICAL_VOLATILITY" }
		,{ whatToShow::OPTION_IMPLIED_VOLATILITY, "OPTION_IMPLIED_VOLATILITY" }
	};
}

#endif