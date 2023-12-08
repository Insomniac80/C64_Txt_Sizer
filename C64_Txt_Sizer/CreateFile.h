#pragma once

#include "Defines.h"
#include "Structs.h"
#include "WinErrBox.hpp"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <format>

using std::string;

class CreateLocalFile
{

public:

	// to be used if default content has to be written to existing file with WriteDefaultContent;
	CreateLocalFile() = default;

	// path_ without // at the end expected. Writes all, no second call necessary.
	explicit CreateLocalFile(const PathFilename& pathFilename_);

	// only to be used if default constructor is called
	void WriteDefaultContent(std::ofstream& file_, FileName fileName_) const;

};

