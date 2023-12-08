#pragma once

#include "Structs.h"
#include "TxtFileToStrings.h"
#include "CreateFile.h"
#include "ForDebug.h"
#include "ToKeyValue.h"

#include <cstdint>
#include <vector>
#include <string>

using std::vector;
using std::string;

class ReadConfig
{

public:

	ReadConfig() = delete;

	explicit ReadConfig(const PathFilename& pathFilename_);

	bool GetValueAsBool(const char* key_) const;
	int64_t GetValueAsInt(const char* key_) const;
	uint64_t GetValueAsUint(const char* key_) const;
	string GetValueAsString(const char* key_) const;

private:

	enum class FailureReason : uint8_t {
		KeyNotFound,
		ToNumberFailed,
		OutOfRange
	};

	vector<string> ReadFromFile(const PathFilename& pathFilename_) const;

	void ReadFailedExit(const char* keyFailed_, FailureReason failureReason_) const;

	string GetFailureString(const char* keyFailed_, FailureReason failureReason_) const;

	ToKeyValue mConfig;

};

struct Configuration {
	Configuration() = delete;
	explicit Configuration(const ReadConfig& config_)
		: askBeforeOverwriting(config_.GetValueAsBool(KEY_ASKBEFOREOVERWRITING))
		, overwriteSourceFile(config_.GetValueAsBool(KEY_OVERWRITESOURCEFILE))
		, appendToFilename(config_.GetValueAsString(KEY_APPENDONNEWFILE))
		, overwriteNewFile(config_.GetValueAsBool(KEY_OVERWRITENEWFILE))
		, ignoreWrittenFiles(config_.GetValueAsBool(KEY_IGNOREWRITTENFILES))
		, optMaxCharsInLine(config_.GetValueAsUint(KEY_OPTION_MAXCHARSLINE))
		, optToUpperCase(config_.GetValueAsBool(KEY_OPTION_TOUPPERCASE))
		, optProcessUmlauts(config_.GetValueAsBool(KEY_OPTION_UMLAUTS))
		, uiListFilesOnEnd(config_.GetValueAsBool(KEY_LISTALLCHOSENFILES))
	{}

	const bool askBeforeOverwriting;
	const bool overwriteSourceFile;
	const string appendToFilename;
	const bool overwriteNewFile;
	const bool ignoreWrittenFiles;
	const uint64_t optMaxCharsInLine;
	const bool optToUpperCase;
	const bool optProcessUmlauts;
	const bool uiListFilesOnEnd;
};

