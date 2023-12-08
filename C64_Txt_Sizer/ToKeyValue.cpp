#include "ToKeyValue.h"

ToKeyValue::ToKeyValue(const vector<string>& lines_)
	:mContent(lines_)
{
}

tuple<bool, string> ToKeyValue::GetAsString(const char* key_) const
{
	for (const auto& line : mContent)
	{
		if (line.starts_with(key_))
			return std::make_tuple(true, string{ line , line.find_first_of("=") + 1 });
	}
	WinErrBox(std::format("{} not found in config file. Program mailfunction. Exiting. \nDebug or delete config and let rewrite by this app.", key_).c_str()
		, BtnChoice::Ok).Show({ BtnThrow::Ok });
	
	return std::make_tuple(false, string{ "" });
}

tuple<bool, string> ToKeyValue::GetAsStringNoSpaces(const char* key_) const
{
	auto [success, value] = GetAsString(key_);
	if (success)
	{
		while (value.front() == ' ')
			value.erase(value.begin());
		while (value.back() == ' ')
			value.pop_back();
	}
	return std::make_tuple(success, value);
}

tuple<vector<string>, vector<string>> ToKeyValue::GetAllEntries() const
{
	vector<string> keys;
	vector<string> values;

	for (const auto& line : mContent)
	{
		const auto key = string{ line , 0, line.find_first_of("=") };
		const auto value = string{ line , line.find_first_of("=") + 1 };
		if(key.empty() || value.empty())
			WinErrBox(std::format("ToKeyValue::GetAllEntries() found empty entry. \nkey: {}\nvalue: {}\nOk to continue (skip this entry), cancel to abort.", key, value).c_str()
				, BtnChoice::OkCancel).Show({ BtnThrow::Ok });
		else {
			keys.emplace_back(key);
			values.emplace_back(value);
		}
	}

	return std::make_tuple(keys, values);
}
