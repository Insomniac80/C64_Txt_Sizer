#include "ToFile.h"

ToFile::ToFile(string_view path_, string_view filename_, const vector<string>& content_, const Configuration& config_)
{
	CheckPassedParams(path_, filename_, content_);

	string targetfile;
	if (config_.overwriteSourceFile)
	{
		std::ostringstream stream;
		stream << path_ << SUBFOLDER_SEPARATOR << filename_;
		targetfile = stream.str();
		if (config_.askBeforeOverwriting)
		{
			auto btnclick = WinErrBox(std::format("Overwrite\n{} \nwith new content?\n\nWarning: this process is irreversible!\n\nHit cancel to terminate whole process.", targetfile).c_str()
				, string("Overwrite?").c_str()
				, BtnChoice::YesNoCancel).Show({ BtnThrow::Cancel });
			if (BtnState::No == btnclick)
				return;
		}
	}
	else
	{
		auto [filePrefix, fileSuffix] = FilenameToPrefixSuffix(filename_);
		std::ostringstream stream;
		stream << path_ << SUBFOLDER_SEPARATOR << filePrefix << config_.appendToFilename << '.' << fileSuffix;
		targetfile = stream.str();
		if (!config_.overwriteNewFile)
		{
			uint16_t num{1};
			while (FileExists(targetfile)) 
			{
				stream.str("");
				stream.clear();
				stream << path_ << SUBFOLDER_SEPARATOR << filePrefix << config_.appendToFilename << num << '.' << fileSuffix;
				targetfile = stream.str();
				num++;
			}
		}
		else if (FileExists(targetfile) && config_.askBeforeOverwriting)
		{
			auto btnclick = WinErrBox(std::format("Overwrite\n{} \nwith new content?\n\nWarning: this process is irreversible!\n\nHit cancel to terminate whole process.", targetfile).c_str()
				, string("Overwrite?").c_str()
				, BtnChoice::YesNoCancel).Show({ BtnThrow::Cancel });
			if (BtnState::No == btnclick)
				return;
		}
	}
	Write(targetfile, content_);

	cout << std::format("Processed file {} written to {}.", filename_, targetfile) << endl;
}

bool ToFile::FileExists(string_view pathFilename_) const
{
	return std::filesystem::exists(pathFilename_);
}

void ToFile::Write(string_view pathFilename_, const vector<string>& content_) const
{
	std::ofstream MyFile(pathFilename_, std::ofstream::out | std::ofstream::trunc);
	bool first{ true };
	for (const auto& line : content_) {
		if (first) {
			first = false;
			MyFile << line;
		}
		else
			MyFile << endl << line;
	}
	MyFile.close();
}

void ToFile::CheckPassedParams(string_view path_, string_view filename_, const vector<string>& content_) const
{
	if (path_.empty() || filename_.empty() || content_.empty())
		WinErrBox("Error: path, filename or content is empty. Terminating."
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });

	if (path_.back() == '\\')
		WinErrBox(std::format("Error, path\n{} \nis malformed. Ending \\ is not allowed. Terminating.", path_.data()).c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });

	if (*filename_.begin() == '\\')
		WinErrBox(std::format("Error, filename\n{} \nis malformed. Starting \\ is not allowed. Terminating.", filename_.data()).c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
}

tuple<string, string> ToFile::FilenameToPrefixSuffix(string_view filename_) const
{
	const auto pointIdx = filename_.find('.');
	if (pointIdx == string::npos)
		WinErrBox(std::format("Error, filename\n{} \nis malformed. Point not found. Terminating.", filename_.data()).c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });

	const auto prefix = string(filename_.substr(0, pointIdx));
	const auto suffix = string(filename_.substr(pointIdx + 1, filename_.size() - pointIdx));

	if (suffix.compare("txt") != 0)
		WinErrBox(std::format("Error, suffix\n{} \nis no txt file suffix. Okto continue, cancel to abort.", suffix.data()).c_str()
			, BtnChoice::Ok).Show({ BtnThrow::Cancel });

	return std::make_tuple(prefix, suffix);
}
