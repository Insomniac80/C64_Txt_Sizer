#include "CreateFile.h"

CreateLocalFile::CreateLocalFile(const PathFilename& pathFilename_)
{
	auto btnPress = WinErrBox(std::format("File\n{} \nnot found in\n{} \n\nCreate?\n\nIf No create file by yourself before proceeding!\nCancel to terminate", pathFilename_.filename, pathFilename_.path).c_str()
		, string("File missing").c_str()
		, BtnChoice::YesNoCancel).Show({ BtnThrow::Cancel });

	if (BtnState::No == btnPress)
		return;

	std::ofstream MyFile(pathFilename_.path + "//" + pathFilename_.filename);
	WriteDefaultContent(MyFile, pathFilename_.enumFileName);
	MyFile.close();

	if (pathFilename_.toEditByUser) {
		btnPress = WinErrBox(std::format("File\n{} \nwas created. Please edit it now.\nDo you want this program to continue after editing?.", pathFilename_.filename).c_str()
			, BtnChoice::YesNo).Show();
		system(string("notepad.exe " + pathFilename_.path + "//" + pathFilename_.filename).c_str());
		if (BtnState::No == btnPress)
			exit(0);
	}
}

void CreateLocalFile::WriteDefaultContent(std::ofstream& file_, FileName fileName_) const
{
	switch (fileName_)
	{
	case FileName::ConfigProgram:
		file_ << "// Configuration file for the C64 Txt Sizer app.\n";
		file_ << "// Left of the = is the key the program searches for - do not change.\n";
		file_ << "// Right of the = is the value. Change for your needs, but always keep the data type in mind (don't apply 2 on a bool f.e.).\n";
		file_ << "// For booleans true and false are allowed as well as 0 and 1.\n";
		file_ << "// Never add \"\", not even on strings.\n";
		file_ << "// All values are mandatory, do not delete or comment out one.\n";
		file_ << "// If this file is accidently malformed, delete and the app will create a new one containing all values.\n";
		file_ << "\n";
		file_ << "\n";
		file_ << "// --- From here on the options will have impact on the user interaction when prompted to choose the files. ---\n";
		file_ << "\n";
		file_ << "\n";
		file_ << "// Defines if after choosing files all are listed again, including enter-prompt to continue.[bool]\n";
		file_ << KEY_LISTALLCHOSENFILES;
		file_ << "=";
		file_ << VALUE_LISTALLCHOSENFILES_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "\n";
		file_ << "// --- From here on the options will have impact on the file handling itself. ---\n";
		file_ << "\n";
		file_ << "\n";
		file_ << "// Defines if you will be prompted before a file will be overwritten.[bool]\n";
		file_ << KEY_ASKBEFOREOVERWRITING;
		file_ << "=";
		file_ << VALUE_ASKBEFOREOVERWRITING_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "// If true the changes will be written into the SAME file the data is read from.[bool]\n";
		file_ << "// BEWARE: no backup is made! Enable only if files are _copied_ before processing!\n";
		file_ << KEY_OVERWRITESOURCEFILE;
		file_ << "=";
		file_ << VALUE_OVERWRITESOURCEFILE_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "// If overwriting source file is false, a new file will be created and extended by this.[string]\n";
		file_ << "// F.e. RoomStation.txt -> RoomStation_processed.txt.\n";
		file_ << KEY_APPENDONNEWFILE;
		file_ << "=";
		file_ << VALUE_APPENDONNEWFILE_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "// If true, and a _processed file is already present, it will be overwritten (does _not_ touch the source file).[bool]\n";
		file_ << KEY_OVERWRITENEWFILE;
		file_ << "=";
		file_ << VALUE_OVERWRITENEWFILE_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "// Defines if files which have the suffix (i.e. are written by this app) are not listed for processing.[bool]\n";
		file_ << KEY_IGNOREWRITTENFILES;
		file_ << "=";
		file_ << VALUE_IGNOREWRITTENFILES_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "\n";
		file_ << "// --- From here on the options will have impact on the content of the file itself. ---\n";
		file_ << "\n";
		file_ << "\n";
		file_ << "// Defines how many characters are allowed max in a line.[integer]\n";
		file_ << KEY_OPTION_MAXCHARSLINE;
		file_ << "=";
		file_ << VALUE_OPTION_MAXCHARSLINE_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "// Defines if all characters will be changed to upper case. Does not have impact on uppercase characters.[bool]\n";
		file_ << KEY_OPTION_TOUPPERCASE;
		file_ << "=";
		file_ << VALUE_OPTION_TOUPPERCASE_DEFAULT;
		file_ << "\n";
		file_ << "\n";
		file_ << "// Defines if all umlauts will be changed to base characters (Ä -> AE, Ü -> UE ..).[bool]\n";
		file_ << KEY_OPTION_UMLAUTS;
		file_ << "=";
		file_ << VALUE_OPTION_UMLAUTS_DEFAULT;
		break;
	case FileName::UNSET:
	default:
		WinErrBox("Aborting \nCreateFile::WriteDefaultContent() is missing an enum FileName definition or UNSET!"
			, BtnChoice::Ok).Show({ BtnThrow::Ok });
	}
}