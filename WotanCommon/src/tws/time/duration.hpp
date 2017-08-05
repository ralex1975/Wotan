#pragma once
#ifndef TIME_DURATION_HPP_
#define TIME_DURATION_HPP_

#include <ostream>

#include "pattern/enumManager.hpp"

namespace Wotan
{
	class duration
	{
	public:
		enum type : char
		{
			seconds = 1,
			days	= 2,
			weeks	= 3,
			months	= 4,
			years	= 5
		};

		duration(uint64_t length, type unit);

	private:
		friend std::ostream & operator<<(std::ostream &os, const duration& p);

		uint64_t	length_	;
		type		unit_	;
	};

	template <>
	const std::vector<std::pair<duration::type, std::string> >
		enumConversions<duration::type>::enumToStringVector =
	{
		 { duration::type::seconds	, "S" }
		,{ duration::type::days		, "D" }
		,{ duration::type::weeks	, "W" }
		,{ duration::type::months	, "M" }
		,{ duration::type::years	, "Y" }
	};
}

#endif