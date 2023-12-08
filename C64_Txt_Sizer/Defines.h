#pragma once

#include <cstdint>

enum class FileName : uint8_t {
	ConfigProgram,
	UNSET
};

////// when adding to any config, add also in CreateFile, 
//static constexpr auto FILENAME_CONFIG_PROGRAM = "CopierConfig.ini";
//static constexpr auto KEY_ENTRY_LIBFOLDERPATH = "LibraryPath";
//static constexpr auto VALUE_DEFAULT_ENTRY_LIBFOLDERPATH = "PathToLib";
//
//static constexpr auto FILENAME_CONFIG_FOLDER = "CopierToLib_ProjectConf.ini";
//static constexpr auto KEY_ENTRY_LIBFOLDERNAME = "LibraryFolderName";
//static constexpr auto VALUE_DEFAULT_ENTRY_LIBFOLDERNAME = "NameOfFolder";
//
//static constexpr auto FILENAME_BLACKLIST = "CopierToLib_Blacklist.ini";
//
//static constexpr auto FILENAME_WHITELIST = "CopierToLib_Whitelist.ini";
//
//static constexpr auto FILENAME_TIMESTAMPS = "CopierToLib_Timestamps.ini";
//
//static constexpr auto SUBFOLDER_SOURCE_TOCOPY = "src";




static constexpr auto SUBFOLDER_SEPARATOR = "\\";

static constexpr auto CONFIG_NAME = "C64TxtSizerConfig.ini";

static constexpr auto KEY_LISTALLCHOSENFILES = "ListAllChosenFiles";
static constexpr auto VALUE_LISTALLCHOSENFILES_DEFAULT = "true";

static constexpr auto KEY_ASKBEFOREOVERWRITING = "AskBeforeOverwriting";
static constexpr auto VALUE_ASKBEFOREOVERWRITING_DEFAULT = "true";

static constexpr auto KEY_OVERWRITESOURCEFILE = "OverwriteSourceFile";
static constexpr auto VALUE_OVERWRITESOURCEFILE_DEFAULT = "false";

static constexpr auto KEY_APPENDONNEWFILE = "AppendOnWrittenFile";
static constexpr auto VALUE_APPENDONNEWFILE_DEFAULT = "_processed";

static constexpr auto KEY_OVERWRITENEWFILE = "OverwriteIfNewFileExists";
static constexpr auto VALUE_OVERWRITENEWFILE_DEFAULT = "true";

static constexpr auto KEY_IGNOREWRITTENFILES = "IgnoreWrittenFilesOnRead";
static constexpr auto VALUE_IGNOREWRITTENFILES_DEFAULT = "true";

static constexpr auto KEY_OPTION_MAXCHARSLINE = "Option_MaxCharsInLine";
static constexpr auto VALUE_OPTION_MAXCHARSLINE_DEFAULT = 40;

static constexpr auto KEY_OPTION_TOUPPERCASE = "Option_ToUpperCase";
static constexpr auto VALUE_OPTION_TOUPPERCASE_DEFAULT = "true";

static constexpr auto KEY_OPTION_UMLAUTS = "Option_ProcessUmlauts";
static constexpr auto VALUE_OPTION_UMLAUTS_DEFAULT = "true";
