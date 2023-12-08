#include "TxtFileToStrings.h"

TxtFileToStrings::TxtFileToStrings(string_view pathAndFilename_)
	: mPathAndFilename(pathAndFilename_)
{}

bool TxtFileToStrings::FileExists() const
{
	std::ifstream file(mPathAndFilename);
	return (!file.fail());
}

ErrorCode TxtFileToStrings::ReadFromFile()
{
	vector<wstring> fileContent;
	std::wifstream file(mPathAndFilename);
	if (file.fail())
		return ERR_FILENOTEXIST;
	if (!file.is_open())
		return ERR_FILENOTOPEN;

	SetConsoleCP(1252);
	std::locale::global(std::locale("de_DE.UTF-8"));

	wstring line;
	while (std::getline(file, line))
	{
		if ((!line.starts_with(L"/*")) && (!line.starts_with(L"//")) && !line.empty())
		{
			if (!mOnlyCppFiles || (mOnlyCppFiles && (line.ends_with(L".h") || line.ends_with(L".hpp") || line.ends_with(L".cpp"))))
				fileContent.emplace_back(line);
		}
	}

	if (fileContent.empty())
		return ERR_FILEEMPTY;

	//! Here the wstring is "converted" to single byte string. 
	//! Be aware of the fact that this does _not_ work for all characters - but umlauts are covered.
	//! Reading directly to string will fail btw.
	for (const auto& ele : fileContent)
		mFileContent.emplace_back(ele.begin(), ele.end());

	mFileContent.shrink_to_fit();

	return ERR_OK;
}

void TxtFileToStrings::HandleError(ErrorCode errorCode_) const
{
	switch (errorCode_)
	{
	case ERR_OK:
		return;
	case ERR_FILENOTEXIST :
		WinErrBox("Aborting \nFile does not exist", "Critical error", mPathAndFilename.c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
	case ERR_FILENOTOPEN:
		WinErrBox("Aborting \nFile can not be opened", "Critical error", mPathAndFilename.c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
	case ERR_FILEEMPTY:
		WinErrBox("File is empty. Intended? \nOk to continue. \nCancel to abort.", "", mPathAndFilename.c_str()
			, BtnChoice::OkCancel).Show({ BtnThrow::Cancel });
		break;
	default:
		WinErrBox("Error code not handled", "", std::to_string(errorCode_).c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
	}
}

void TxtFileToStrings::Print() const
{
	for (const auto& ele : mFileContent)
		cout << ele << endl;
}
