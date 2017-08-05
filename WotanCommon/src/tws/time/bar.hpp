#pragma once
#ifndef TIME_BAR_HPP_
#define TIME_BAR_HPP_

#include <ostream>

#include "pattern/enumManager.hpp"

namespace Wotan
{
	class bar
	{
	public:
		// from https://interactivebrokers.github.io/tws-api/historical_bars.html#available_products_hd
		enum size : char
		{
			oneSecond = 1,
			fiveSeconds = 2,
			tenSeconds = 3,
			fifteenSeconds = 4,
			thirtySeconds = 5,
			oneMinute = 6,
			twoMinutes = 7,
			threeMinutes = 8,
			fiveMinutes = 9,
			tenMinutes = 10,
			fifteenMinutes = 11,
			twentyMinutes = 12,
			thirtyMinutes = 13,
			oneHour = 14,
			twoHours = 15,
			threeHours = 16,
			fourHours = 17,
			eightHours = 18,
			oneDay = 19,
			oneWeek = 20,
			oneMonth = 21
		};
	};

	template <>
	const std::vector<std::pair<bar::size, std::string> >
		enumConversions<bar::size>::enumToStringVector =
	{
		 { bar::size::oneSecond		, "1 secs"	}
		,{ bar::size::fiveSeconds	, "5 secs"	}
		,{ bar::size::tenSeconds	, "10 secs" }
		,{ bar::size::fifteenSeconds, "15 secs" }
		,{ bar::size::thirtySeconds	, "30 secs" }
		,{ bar::size::oneMinute		, "1 min"	}
		,{ bar::size::twoMinutes	, "2 mins"	}
		,{ bar::size::threeMinutes	, "3 mins"	}
		,{ bar::size::fiveMinutes	, "5 mins"	}
		,{ bar::size::tenMinutes	, "10 mins" }
		,{ bar::size::fifteenMinutes, "15 mins" }
		,{ bar::size::twentyMinutes	, "20 mins" }
		,{ bar::size::thirtyMinutes	, "30 mins" }
		,{ bar::size::oneHour		, "1 hour"	}
		,{ bar::size::twoHours		, "2 hour"	}
		,{ bar::size::threeHours	, "3 hour"	}
		,{ bar::size::fourHours		, "4 hour"	}
		,{ bar::size::eightHours	, "8 hour"	}
		,{ bar::size::oneDay		, "1 day"	}
		,{ bar::size::oneWeek		, "1 week"	}
		,{ bar::size::oneMonth		, "1 month" }
	};

	std::ostream & operator<<(std::ostream & os, const bar::size & dur);
}

#endif