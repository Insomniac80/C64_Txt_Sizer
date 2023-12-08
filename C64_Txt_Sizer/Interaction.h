#pragma once

#include "ReadConfig.h"

#include <string>
#include <vector>
#include <iostream> 
#include <ctype.h>
#include <numeric>

using std::string;
using std::vector;
using std::cin;

class Interaction
{
public:

	Interaction(const vector<string>& txtFiles_, const Configuration& config_);

	vector<uint16_t> GetIndicesFromUser() const { return mIndicesRead; }

private:

	void PrintFileList(const vector<string>& txtFiles_) const;

	string GetBoolAsText(bool toStr_) const;

	void PrintIntroConfig(const Configuration& config_) const;

	void ConfirmProceeding(const vector<string>& txtFiles_) const;

	void CheckElements(size_t maxSize_) const;

	vector<uint16_t> ReadIndices(size_t maxSize_) const;

	// input begins with 1, so -1 to directly access names in other vec. Or with 0 all indices have to be added
	vector<uint16_t> InputNumbersToIndices(const vector<uint16_t>& indices, size_t maxSize_) const;

	vector<uint16_t> mIndicesRead;

};

