#pragma once
#ifndef TWS_ENUMS_SECTYPE_HPP
#define TWS_ENUMS_SECTYPE_HPP

#include "pattern/enumManager.hpp"

namespace Wotan
{
	namespace secType
	{
		enum secType : char
		{
			STK		= 1,
			OPT		= 2,
			FUT		= 3,
			IND		= 4,
			FOP		= 5,
			CASH	= 6,
			BAG		= 7,
			NEWS	= 8,
			unknown = 0
		};
	}
	

	template <>
	const std::vector<std::pair<secType::secType, std::string> >
		enumConversions<secType::secType>::enumToStringVector =
	{
		 { secType::STK	, "STK"		}
		,{ secType::OPT	, "OPT"		}
		,{ secType::FUT	, "FUT"		}
		,{ secType::IND	, "IND"		}
		,{ secType::FOP	, "FOP"		}
		,{ secType::CASH, "CASH"	}
		,{ secType::BAG	, "BAG"		}
		,{ secType::NEWS, "NEWS"	}
	};
}

#endif