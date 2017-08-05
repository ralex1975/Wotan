#pragma once
#ifndef TWS_ENUMS_SECTYPE_HPP
#define TWS_ENUMS_SECTYPE_HPP

#include "pattern/enumManager.hpp"

namespace Wotan
{
	// see https://interactivebrokers.github.io/tws-api/basic_contracts.html#fop
	enum secType : char
	{
		stocks			= 1,
		options			= 2,
		futures			= 3,
		indexes			= 4,
		futuresOnOption	= 5,
		cash			= 6,
		bag				= 7,
		news			= 8,
		bonds			= 9,
		mutualFunds		= 10,
		commodities		= 11,
		dutchWarrants	= 12
	};

	template <>
	const std::vector<std::pair<secType, std::string> >
		enumConversions<secType>::enumToStringVector =
	{
		 { secType::stocks			, "STK"		}
		,{ secType::options			, "OPT"		}
		,{ secType::futures			, "FUT"		}
		,{ secType::indexes			, "IND"		}
		,{ secType::futuresOnOption	, "FOP"		}
		,{ secType::cash			, "CASH"	}
		,{ secType::bag				, "BAG"		}
		,{ secType::news			, "NEWS"	}
		,{ secType::bonds			, "BOND"	}
		,{ secType::mutualFunds		, "FUND"	}
		,{ secType::commodities		, "CMDTY"	}
		,{ secType::dutchWarrants	, "IOPT"	}
	};
}

#endif