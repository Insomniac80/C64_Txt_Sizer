#pragma once

#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <cstdint>
#include <filesystem>

#include "ErrorCodes.h"
#include "WinErrBox.hpp"
#include "ForDebug.h"
#include "Defines.h"

using std::vector;
using std::string;
using std::string_view; 

namespace fs = std::filesystem;

using std::cout;
using std::endl;

class FoldersAndFilenames
{
public:

	using Entry = std::filesystem::directory_entry;

	enum class FileOrFolder : bool {
		File,
		Folder
	};

	explicit FoldersAndFilenames(string_view path_);

	bool Success() const { return (mFileError == ERR_OK /*|| mFileError == ERR_FILEEMPTY*/); }

	ErrorCode GetFileError() const { return mFileError; }

	const vector<Entry>& GetFiles() const { return mFiles; }
	const vector<Entry>& GetFolders() const { return mFolders; }

	vector<string> GetFilesWithoutPaths(string_view pathStartToRemove_) const { return RemovePathFromEntries(mFiles, pathStartToRemove_, FileOrFolder::File); }
	vector<string> GetFoldersWithoutPaths(string_view pathStartToRemove_) const { return RemovePathFromEntries(mFolders, pathStartToRemove_, FileOrFolder::Folder); }

	vector<string> GetFilesWithoutPaths(string pathStartToRemove_, const vector<string>& onlyAddFilesEndWith_) const;

	// only to be used if subparameters must be specified. Otherwise use GetXyWithoutPaths()
	vector<string> RemovePathFromEntries(
		const vector<Entry>& fullPaths_,
		string_view pathStartToRemove_,
		FileOrFolder fileOrFolder
	) const;

	void PrintFiles() const;

	void PrintFolders() const;

private:

	ErrorCode mFileError{ ERR_OK };

	vector<Entry> mFiles{};
	vector<Entry> mFolders{};

	vector<Entry> ReadFilesAndFolders(string_view path_);

	void FileTypePrint(fs::file_status s) const;

};

