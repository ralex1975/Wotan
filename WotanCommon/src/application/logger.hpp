/*
* logger.hpp
*
*  Created on: Sep 25, 2016
*      Author: vermosen
*/
#pragma once
#ifndef APPLICATION_LOGGER_HPP_
#define APPLICATION_LOGGER_HPP_

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/value_ref.hpp>

#include "pattern/enumManager.hpp"

namespace Wotan
{
	enum severity : short
	{
		debug	= 0,
		info	= 1,
		warning = 2,
		error	= 3,
		fatal	= 4
	};

	template <>
	const std::vector<std::pair<severity, std::string> >
		enumConversions<severity>::enumToStringVector =
	{
		 { severity::debug	, "debug"		}
		,{ severity::info	, "information" }
		,{ severity::warning, "warning"		}
		,{ severity::error	, "error"		}
		,{ severity::fatal	, "fatal"		}
	};

	//enum verbosity : short
	//{
	//	none	= 0,
	//	low		= 1,
	//	medium	= 2,
	//	high	= 3
	//};

	//template <>
	//const std::vector<std::pair<verbosity, std::string> >
	//	enumConversions<verbosity>::enumToStringVector =
	//{
	//	 { verbosity::none	, "none"	}
	//	,{ verbosity::low	, "low"		}
	//	,{ verbosity::medium, "medium"	}
	//	,{ verbosity::high	, "high"	}
	//};
}

namespace
{
	// define the keywords to use in filter and formatter
	BOOST_LOG_ATTRIBUTE_KEYWORD(severity_t	, "Severity"	, Wotan::severity)
	BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp	, "TimeStamp"	, boost::log::attributes::utc_clock::value_type)
	BOOST_LOG_ATTRIBUTE_KEYWORD(processid	, "PID"			, boost::log::attributes::current_process_id::value_type)
	BOOST_LOG_ATTRIBUTE_KEYWORD(threadid	, "Thread"		, boost::log::attributes::current_thread_id::value_type)
}

// macros to get log streams
#define LOG_DEBUG()		BOOST_LOG_SEV(Wotan::logger::getLogger(), Wotan::severity::debug	)
#define LOG_INFO()		BOOST_LOG_SEV(Wotan::logger::getLogger(), Wotan::severity::info		)
#define LOG_WARNING()	BOOST_LOG_SEV(Wotan::logger::getLogger(), Wotan::severity::warning	)
#define LOG_ERROR()		BOOST_LOG_SEV(Wotan::logger::getLogger(), Wotan::severity::error	)
#define LOG_FATAL()		BOOST_LOG_SEV(Wotan::logger::getLogger(), Wotan::severity::fatal	)
#define LOG()			LOG_INFO()

namespace Wotan
{
	// logger type with severity level and multithread support
	class logger
	{
	public:
		typedef boost::log::sources::severity_logger_mt<severity>							logger_t;
		typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend>	sink_t	;

		static void			initialize	(const std::string & fileName, severity threshold = warning);
		static logger_t &	getLogger	();
		static bool			levelFilter	(boost::log::value_ref<severity, tag::severity_t> const& level);

	private:
		static severity threshold_	;
		static logger_t logger_		;
		static bool		initialized_;
	};
} // namespace Wotan

#endif // APPLICATION_LOGGER_HPP_

