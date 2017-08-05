#pragma once

#include "StdAfx.h"

#include "bar.hpp"

namespace Wotan
{
	std::ostream & operator<<(std::ostream & os, const bar::size & dur)
	{
		return os << dur;
	}
}