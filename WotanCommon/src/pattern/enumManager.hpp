#ifndef ENUM_MANAGER_HPP
#define ENUM_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

// an enum factory class
namespace Wotan
{
	const int ENUM_NOT_FOUND = -1;  const std::string NEW = "  ";

	template <typename _enum>
	class enumConversions;

	template <typename _enum>
	struct enumManager 
	{
		static std::string toString(const _enum en);
		static _enum toEnum(const std::string& str);
		static const std::map<_enum, std::string> enumToStringMap;
		static const std::map<std::string, _enum> stringToEnumMap;
	private:
		static std::map<_enum, std::string> initializeEnumToStringMap();
		static std::map<std::string, _enum> initializeStringToEnumMap();
	};

	template <typename _enum>
	const std::map<_enum, std::string> enumManager<_enum>::enumToStringMap = enumManager<_enum>::initializeEnumToStringMap();

	template<typename _enum>
	std::map<_enum, std::string> enumManager<_enum>::initializeEnumToStringMap() 
	{
		std::map<_enum, std::string> m;
		for (const auto& x : enumConversions<_enum>::enumToStringVector)
			m[x.first] = x.second;
		return m;
	}

	template <typename _enum>
	const std::map<std::string, _enum> enumManager<_enum>::stringToEnumMap = enumManager<_enum>::initializeStringToEnumMap();

	template<typename _enum>
	std::map<std::string, _enum> enumManager<_enum>::initializeStringToEnumMap() 
	{
		std::map<std::string, _enum> m;
		for (const auto& x : enumConversions<_enum>::enumToStringVector)
			m[x.second] = x.first;
		return m;
	}

	template <typename _enum>
	std::string enumManager<_enum>::toString(const _enum en)
	{
		auto it = enumManager<_enum>::enumToStringMap.find(en);  // std::map::find is the fastest lookup method
		if (it != enumManager<_enum>::enumToStringMap.end())
			return it->second;
		return "[[[_enum to string not found." + NEW + "Programmer made an error]]]";
	}

	template<typename _enum>
	_enum enumManager<_enum>::toEnum(const std::string& str)
	{
		auto it = enumManager<_enum>::stringToEnumMap.find(str);
		if (it != enumManager<_enum>::stringToEnumMap.end())
			return it->second;
		return static_cast<_enum> (ENUM_NOT_FOUND);
	}

	template <typename _enum>
	class enumConversions : public enumManager<_enum> {
	private:
		enumConversions();  // to prevent instantiation
	public:
		static const std::vector<std::pair<_enum, std::string>> enumToStringVector;
	};
}

template<typename _enum, class = typename std::enable_if<std::is_enum<_enum>::value>::type>
std::ostream & operator << (std::ostream & os, const _enum en) {
	return os << dtcc::enumConversions<_enum>::toString(en);
}

#endif
