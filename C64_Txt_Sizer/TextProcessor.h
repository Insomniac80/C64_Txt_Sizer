#pragma once

#include "ReadConfig.h"
#include "TxtFileToStrings.h"

#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using std::string;
using std::vector;
using std::tuple;

class TextProcessor
{

public:

	TextProcessor(
		string_view path_, 
		const vector<string>& fileNamesAll_, 
		const vector<uint16_t>& indicesToProcess_, 
		const Configuration& config_
	);

	tuple<vector<vector<string>>, vector<uint16_t>> GetTextsAndIndices() { return std::make_tuple(mTexts, mIdxProcessed); }

private:

	// f.e. empty files are dropped here
	vector<uint16_t> mIdxProcessed;

	vector<vector<string>> mTexts;

	vector<string> GetFileContent(string_view pathFilename_) const;

	void NewLineToSpace(string& line) const;

	void RemoveDoubleSpaces(string& line) const;

	string MultiLinesToOneLine(const vector<string>& lines_) const;

	void RemoveUmlauts(string& text_) const;

	void AddSpaceAtLineEnd(vector<string>& lines_) const;

	void RemoveSpaceBeginEnd(vector<string>& lines_) const;

	vector<string> ToMultiLine(string_view text_, uint64_t lineSize_) const;

	void ReplaceInStr(string& text_, string_view toReplace_, string_view replaceBy_) const;

	void CheckForOverlongLines(const vector<string>& lines_, string_view filename_, uint64_t lineSizeMax_) const;

	void AddQuotationMarks(vector<string>& lines_) const;

};

