#pragma once

#include "ReadConfig.h"

#include <string>
#include <vector>
#include <tuple>
#include <filesystem>
#include <sstream>

using std::string;
using std::vector;
using std::tuple;

class ToFile
{
public:

	/**
	 * @brief Writes passed content to a file.
	 * @param path_: Path the file will be located _without_ ending \\. F.e. C:\\exampleFolder
	 * @param filename_: Full filename including suffix, but without starting \\. F.e. example.txt.
	 * @param content_: Strings to be written. Each string is one line.
	 * @param config_:Config to be passed. F.e. if prompted before overwriting is read from it.
	*/
	ToFile(string_view path_, string_view filename_, const vector<string>& content_, const Configuration& config_);

private:

	bool FileExists(string_view pathFilename_) const;

	void Write(string_view pathFilename_, const vector<string>& content_) const;

	void CheckPassedParams(string_view path_, string_view filename_, const vector<string>& content_) const;

	tuple<string, string> FilenameToPrefixSuffix(string_view filename_) const;

};

