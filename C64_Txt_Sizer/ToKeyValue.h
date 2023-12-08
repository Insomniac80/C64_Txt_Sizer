#pragma once

#include "WinErrBox.hpp"

#include <string>
#include <vector>
#include <tuple>
#include <format>

using std::string;
using std::vector;
using std::tuple;

class ToKeyValue
{
public:

	ToKeyValue() = delete;

	explicit ToKeyValue(const vector<string>& lines_);

	tuple<bool, string> GetAsString(const char* key_) const;

	// GetAsString(), but removes all spaces at beginning and end
	tuple<bool, string> GetAsStringNoSpaces(const char* key_) const;

	tuple<vector<string>, vector<string>> GetAllEntries() const;

private:

	const vector<string> mContent;

};

