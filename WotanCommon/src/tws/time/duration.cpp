#pragma once

#include "StdAfx.h"

#include "duration.hpp"

namespace Wotan
{
	duration::duration(uint64_t length, duration::type unit)
	: length_(length)
	, unit_(unit) {}

	std::ostream & operator<<(std::ostream &os, const duration & dur)
	{
		return os << dur.length_ << " " << dur.unit_;
	}
}