#include "TextProcessor.h"

TextProcessor::TextProcessor(
	string_view path_, 
	const vector<string>& fileNamesAll_, 
	const vector<uint16_t>& indicesToProcess_, 
	const Configuration& config_
)
{
	cout << endl << endl;
	for (auto idx : indicesToProcess_) {
		if (idx >= fileNamesAll_.size())
			WinErrBox(std::format("Error\n{} \nout of range.\nProgram will exit now.", idx).c_str()
				, BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
		auto fileContentMultiLine = GetFileContent(string(path_) + SUBFOLDER_SEPARATOR + fileNamesAll_.at(idx));
		if (fileContentMultiLine.empty())
			continue;
		AddSpaceAtLineEnd(fileContentMultiLine);
		auto fileContent = MultiLinesToOneLine(fileContentMultiLine);
		NewLineToSpace(fileContent);
		RemoveDoubleSpaces(fileContent);
		if (config_.optProcessUmlauts)
			RemoveUmlauts(fileContent);
		if (config_.optToUpperCase)
			std::transform(fileContent.begin(), fileContent.end(), fileContent.begin(), ::toupper);
		auto processedText = ToMultiLine(fileContent, config_.optMaxCharsInLine);
		RemoveSpaceBeginEnd(processedText);
		CheckForOverlongLines(processedText, fileNamesAll_.at(idx), config_.optMaxCharsInLine);
		AddQuotationMarks(processedText);

		cout << std::format("File {} aligned.", fileNamesAll_.at(idx)) << endl;

		mIdxProcessed.emplace_back(idx);
		mTexts.emplace_back(processedText);
	}
	cout << endl;
}

void TextProcessor::CheckForOverlongLines(const vector<string>& lines_, string_view filename_, uint64_t lineSizeMax_) const
{
	for (const auto& ele : lines_)
	{
		if (ele.size() > lineSizeMax_)
			WinErrBox(std::format("WARNING!\nA word in the text is bigger then the maximum char size:\n{} \nFile:\n{}", ele, filename_.data()).c_str()
				, BtnChoice::Ok).Show({ });
	}
}

void TextProcessor::AddQuotationMarks(vector<string>& lines_) const
{
	for (auto& line : lines_)
	{
		line.insert(0, "\"");
		line.append("\"");
	}
}

void TextProcessor::RemoveSpaceBeginEnd(vector<string>& lines_) const
{
	for (auto& ele : lines_) {
		while (ele.front() == ' ')
			ele.erase(ele.begin());
		while (ele.back() == ' ')
			ele.pop_back();
	}
}

vector<string> TextProcessor::ToMultiLine(string_view text_, uint64_t lineSizeMax_) const
{
	vector<string> linesOfText;
	size_t posBegin{ 0 };
	size_t idx{ text_.find(" ", 0) };
	size_t idxLast{ idx };
	while (idx != string::npos) {
		if (idx - posBegin <= lineSizeMax_) {
			idxLast = idx;
		}
		else {
			linesOfText.emplace_back(text_.substr(posBegin, idxLast - posBegin));
			posBegin = idxLast + 1;
		}
		idx = text_.find(" ", idxLast + 1);
	}
		
	linesOfText.emplace_back(text_.substr(posBegin, text_.size() - posBegin));
	return linesOfText;
}

void TextProcessor::ReplaceInStr(string& text_, string_view toReplace_, string_view replaceBy_) const
{
	int pos = 0;
	while ((pos = text_.find(toReplace_, pos)) != std::string::npos) {
		text_.replace(pos, toReplace_.length(), replaceBy_);
		pos += replaceBy_.length();
	}
}

void TextProcessor::RemoveUmlauts(string& text_) const
{
	ReplaceInStr(text_, "ä", "ae");
	ReplaceInStr(text_, "Ä", "AE");

	ReplaceInStr(text_, "ö", "oe");
	ReplaceInStr(text_, "O", "OE");

	ReplaceInStr(text_, "ü", "ue");
	ReplaceInStr(text_, "Ü", "UE");
}

void TextProcessor::AddSpaceAtLineEnd(vector<string>& lines_) const
{
	for (size_t i = 0; i < lines_.size() - 1; ++i)	// last line needs no space
		lines_.at(i) += " ";
}

string TextProcessor::MultiLinesToOneLine(const vector<string>& lines_) const
{
	string allLines{};
	for (auto& line : lines_)
	{
		allLines += line;
	}
	return allLines;
}

void TextProcessor::RemoveDoubleSpaces(string& line_) const
{
	auto doubleSpace = line_.find("  ");
	while (doubleSpace != std::string::npos)
	{
		line_.erase(doubleSpace, 1);
		doubleSpace = line_.find("  ");
	}
}

void TextProcessor::NewLineToSpace(string& line) const
{
	std::ranges::replace(line, '\n', ' ');
}

vector<string> TextProcessor::GetFileContent(string_view pathFilename_) const
{
	auto content = TxtFileToStrings(pathFilename_);
	content.HandleError(content.ReadFromFile());
	return content.GetContent();
}
