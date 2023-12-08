#pragma once

#include "Defines.h"
//#include "ReadConfig.h"

#include <string>
#include <cstdint>

using std::string;

enum class ParamType : uint8_t {
	UNSET,
	Bool,
	Int64,
	uInt64,
	String
};

struct PathFilename {
	string path{};
	const char* filename{ nullptr };
	FileName enumFileName{ FileName::UNSET };
	bool toEditByUser{ true };

	bool IsValid() const
	{
		if (
			path.empty() ||
			filename == nullptr /*||
			enumFileName == FileName::UNSET*/
			)
			return false;

		return true;
	}
};

struct Key {
	const char* key{ nullptr };
	ParamType  paramType{ ParamType::UNSET };

	bool IsValid() const
	{
		if (key == nullptr || paramType == ParamType::UNSET)
			return false;

		return true;
	}
};

struct KeyDefaultValue {
	const char* key{ nullptr };
	const char* defaultValue{ nullptr };
	ParamType  paramType{ ParamType::UNSET };

	bool IsValid() const
	{
		if (key == nullptr || defaultValue == nullptr || paramType == ParamType::UNSET)
			return false;

		return true;
	}
};
