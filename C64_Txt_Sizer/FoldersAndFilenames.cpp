#include "FoldersAndFilenames.h"

FoldersAndFilenames::FoldersAndFilenames(string_view path_)
{
	// temporary folders list. When entry is read, is moved to mFolders
	vector<Entry> folders{ Entry(path_) };
	while (!folders.empty() && ERR_OK == mFileError)
	{
		auto subFolders = ReadFilesAndFolders((*folders.begin()).path().string());
		mFolders.emplace_back(*folders.begin());
		folders.erase(folders.begin());
		if (!subFolders.empty())
			folders.insert(folders.end(), subFolders.begin(), subFolders.end());
	}
}

void FoldersAndFilenames::PrintFiles() const
{
	for (const auto& ele : mFiles)
		cout << ele.path().string() << endl;
}

void FoldersAndFilenames::PrintFolders() const
{
	for (const auto& ele : mFolders)
		cout << ele.path().string() << endl;
}

vector<FoldersAndFilenames::Entry> FoldersAndFilenames::ReadFilesAndFolders(string_view path_)
{
	if (!std::filesystem::is_directory(std::filesystem::path(path_).parent_path()))
	{
		mFileError = ERR_FOLDERNOTEXIST;
		return {};
	}

	vector<Entry> folders{};
	for (const auto& entry : fs::directory_iterator(path_))
	{
		if (entry.is_directory())
			folders.emplace_back(entry);
		else if (entry.is_regular_file())
			mFiles.emplace_back(entry);
	}
	return folders;
}

void FoldersAndFilenames::FileTypePrint(fs::file_status s) const
{
	if (fs::is_regular_file(s)) std::cout << " is a regular file\n";
	if (fs::is_directory(s)) std::cout << " is a directory\n";
	if (fs::is_block_file(s)) std::cout << " is a block device\n";
	if (fs::is_character_file(s)) std::cout << " is a character device\n";
	if (fs::is_fifo(s)) std::cout << " is a named IPC pipe\n";
	if (fs::is_socket(s)) std::cout << " is a named IPC socket\n";
	if (fs::is_symlink(s)) std::cout << " is a symlink\n";
	if (!fs::exists(s)) std::cout << " does not exist\n";
}

// no matter folders or files
vector<string> FoldersAndFilenames::RemovePathFromEntries(
	const vector<Entry>& fullPaths_, 
	string_view pathStartToRemove_,
	FileOrFolder fileOrFolder
) const
{
#ifdef DEBUG
	if (FileOrFolder::Folder == fileOrFolder)
		ForDebug().PrintSeparationLine("FolderCollector");
	else
		ForDebug().PrintSeparationLine("FileCollector");
#endif
	vector<string> foldersWithoutPaths;
	for (const auto& folderPath : fullPaths_)
	{
		if (folderPath.path().string().find(pathStartToRemove_) == std::string::npos)
			WinErrBox("Path and source mismatch.\n Should not happen.\n Debug.\nTerminating."
				, BtnChoice::Ok).Show({ BtnThrow::Ok });

		const auto fileFolder = folderPath.path().string();
		auto rootFolder = string(pathStartToRemove_);

		#ifdef DEBUG_PATH
			if (FileOrFolder::Folder == fileOrFolder) {
				cout << string("Folder \"") + fileFolder + "\" has size of " + std::to_string(fileFolder.size()) << endl;
				cout << string("Folder \"") + rootFolder + "\" has size of " + std::to_string(rootFolder.size()) << endl;
			}
		#endif
		const auto fileFolderSize = fileFolder.size();
		const auto rootFolderSize = rootFolder.size();
		string folderOnly = {};
		if (fileFolderSize > rootFolderSize)    // otherwise root folder, "" already correct.
			folderOnly = { SUBFOLDER_SEPARATOR + folderPath.path().string(), rootFolderSize + 1 };
		#ifdef DEBUG
			if (FileOrFolder::Folder == fileOrFolder)
				cout << "Folder \"" + folderOnly + "\"" << endl;
			else
				cout << "File \"" + folderOnly + "\"" << endl;
		#endif
		foldersWithoutPaths.emplace_back(folderOnly);
	}
	return foldersWithoutPaths;
}

vector<string> FoldersAndFilenames::GetFilesWithoutPaths(string pathStartToRemove_, const vector<string>& onlyAddFilesEndWith_) const
{ 
	if (!pathStartToRemove_.ends_with(SUBFOLDER_SEPARATOR))
		pathStartToRemove_ += SUBFOLDER_SEPARATOR;

	auto allFiles = RemovePathFromEntries(mFiles, pathStartToRemove_, FileOrFolder::File); 

	auto doesntEndWith = [&onlyAddFilesEndWith_](string_view compareEndWith_) {
		for (const auto& allowedEnd : onlyAddFilesEndWith_) {
			if (compareEndWith_.ends_with(allowedEnd))
				return false;
		}
		return true;
	};
	std::erase_if(allFiles, doesntEndWith);
	allFiles.shrink_to_fit();
	return allFiles;
}
