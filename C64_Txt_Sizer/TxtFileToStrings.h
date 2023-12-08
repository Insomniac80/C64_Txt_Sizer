#pragma once

#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <cstdint>

#include "ErrorCodes.h"
#include "WinErrBox.hpp"

using std::vector;
using std::string;
using std::string_view;

using std::cout;
using std::endl;

class TxtFileToStrings
{

public:

	explicit TxtFileToStrings(string_view pathAndFilename_); 

	bool FileExists() const;

	// Dumps file content so it can be called for using GetContent()
	// Don´t forget to process ErrorCode before!
	// Handled this way to allow call to FileExists() for optional files.
	// empty lines are skipped
	ErrorCode ReadFromFile();

	// Pass ReadFromFile() - error here to process it (on error get msgbox and
	// if error is critical an exception).
	void HandleError(ErrorCode errorCode_) const;

	// Before calling ReadFromFile() MUST be called! Otherwise vec will be empty
	const vector<string>& GetContent() const {return mFileContent;}

	void Print() const;

	// If true only .h .hpp and .cpp files are copied. Default is false.
	bool OnlyCppFiles() const { return mOnlyCppFiles; }
	// If true only .h .hpp and .cpp files are copied. Default is false.
	void OnlyCppFiles(bool state_) { mOnlyCppFiles = state_; }

private:

	const string mPathAndFilename;

	vector<string> mFileContent{};

	bool mOnlyCppFiles{ false };

};

