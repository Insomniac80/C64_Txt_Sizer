#include "Interaction.h"

Interaction::Interaction(const vector<string>& txtFiles_, const Configuration& config_)
{
    if (txtFiles_.empty())
    {
        cout << "\nNo text files could be found in the folder.\nSubfolders are not supported.\nProgram terminates now.\nPress any key.";
        cin.get();
        exit(0);
    }

    PrintIntroConfig(config_);
    PrintFileList(txtFiles_);
    mIndicesRead = InputNumbersToIndices(ReadIndices(txtFiles_.size()), txtFiles_.size());
    CheckElements(txtFiles_.size());
    if (config_.uiListFilesOnEnd)
        ConfirmProceeding(txtFiles_);
}

vector<uint16_t> Interaction::InputNumbersToIndices(const vector<uint16_t>& indices_, size_t maxSize_) const
{
    vector<uint16_t> processed;
    if (indices_.size() == 1 && indices_.at(0) == 0)
    {
        processed.insert(processed.begin(), maxSize_, 0);
        std::iota(std::begin(processed), std::end(processed), 0);
    }
    else
    {
        for (auto& ele : indices_)
            processed.emplace_back(ele - 1);
    }
    return processed;
}

vector<uint16_t> Interaction::ReadIndices(size_t maxSize_) const
{
    cout << "Your choice: " << endl;
    string rawInput;
    vector<uint16_t> numbers;
    while (getline(cin, rawInput))
    {
        if (rawInput.empty())
            break;
        if (std::find_if(rawInput.begin(), rawInput.end(), [](unsigned char char_) { return (isdigit(char_) == 0); }) != rawInput.end()) {
            cout << "Please only enter numbers. Discarded." << endl;
            continue;
        }

        const auto idx = std::stoi(rawInput);
        if (idx == 0) {
            if (!numbers.empty()) {
                cout << "Numbers besides 0 detected. If adding 0, no other numbers are of use (as all files will be processed anyway)." << endl;
                numbers.clear();
            }
            numbers.push_back(static_cast<uint16_t>(idx));
            break;
        }
        else if (idx < 0 || idx > static_cast<int>(maxSize_))
            cout << "Number is out of range. Please check number in front of filename and enter accordingly. Discarded." << endl;
        else {
            if (std::find(numbers.begin(), numbers.end(), idx) != numbers.end())
                cout << "Number was already added. Discarding." << endl;
            else {
                numbers.push_back(static_cast<uint16_t>(idx));
                cout << "Enter another number or press enter to continue." << endl;
            }
        }
    }

    numbers.shrink_to_fit();

    return numbers;
}

void Interaction::CheckElements(size_t) const
{
    string rawInput;

    if (mIndicesRead.empty()) {
        cout << "No files chosen. Program will terminate after enter is pressed." << endl;
        while (getline(cin, rawInput))
        {
            exit(0);
        }
    }

    //if (maxSize_ == mIndicesRead.size()) {
    //    cout << "Hint: if all shall be processed, you also can just add the 0." << endl;
    //    mIndicesRead.clear();
    //    mIndicesRead.emplace_back(0);
    //}
}

void Interaction::ConfirmProceeding(const vector<string>& txtFiles_) const
{
    string rawInput;

    cout << endl;
    cout << "The files you have chosen are:" << endl;
    for (auto ele : mIndicesRead)
        cout << txtFiles_.at(ele) << endl;
    cout << "Press enter to continue or close the window to abort. (For skipping this prompt see configuration.)" << endl;
    while (getline(cin, rawInput))
    {
        if (rawInput.empty())
            break;
        cout << "Press enter to continue or close the window to abort." << endl;
    }
}

void Interaction::PrintFileList(const vector<string>& txtFiles_) const
{
    cout << "Please choose files to be processed." << endl;
    cout << "Enter 0 to choose all files at once." << endl;
    cout << "Multiple files can be chosen (press enter after every file number)." << endl;
    cout << "Press enter without a number when finished." << endl;
    cout << "To abort close the window. No changes will be made." << endl;
    cout << endl;
    cout << "Files in folder:" << endl;
    uint16_t idx{ 1 };
    for (const auto& ele : txtFiles_) {
        cout << std::to_string(idx) << ". " << ele << endl;
        idx++;
    }
    cout << endl;
}

string Interaction::GetBoolAsText(bool toStr_) const
{
    if (toStr_)
        return "true";
    else
        return "false";
}

void Interaction::PrintIntroConfig(const Configuration& config_) const
{
    cout << "Welcome to the C64 Text Normalizer" << endl;
    cout << "Config file was read from program folder and applied." << endl;
    cout << "Unused parameters are not listed here. Check .ini for all options." << endl;
    cout << endl;
    cout << "Config reads:" << endl;
    cout << KEY_LISTALLCHOSENFILES << " is " << GetBoolAsText(config_.uiListFilesOnEnd) << endl;
    cout << "   means that after adding all files they will be listed and program is waiting for confirmation." << endl;
    cout << KEY_ASKBEFOREOVERWRITING << " is " << GetBoolAsText(config_.askBeforeOverwriting) << endl;
    if (config_.overwriteSourceFile) {
        cout << "SOURCE FILES WILL BE OVERWRITTEN! NO BACKUP WILL BE MADE!" << endl;
        cout << KEY_OVERWRITESOURCEFILE << " is " << GetBoolAsText(config_.overwriteSourceFile) << endl;
        cout << "SOURCE FILES WILL BE OVERWRITTEN! NO BACKUP WILL BE MADE!" << endl;
    }
    else {
        cout << KEY_APPENDONNEWFILE << " is " << config_.appendToFilename << endl;
        cout << "   means source file will not be touched, instead new file is created, ending with above string." << endl;
        cout << KEY_IGNOREWRITTENFILES << " is " << config_.ignoreWrittenFiles << endl;
        cout << "   means files with the suffix (see option above) are not listed here to be processed." << endl;
        cout << KEY_OVERWRITENEWFILE << " is " << GetBoolAsText(config_.overwriteNewFile) << endl;
        if (config_.overwriteNewFile)
            cout << "   if the new file is already present, it will be overwritten. Source is not touched." << endl;
    }
    cout << KEY_OPTION_MAXCHARSLINE << " is " << std::to_string(config_.optMaxCharsInLine) << endl;
    cout << KEY_OPTION_TOUPPERCASE << " is " << GetBoolAsText(config_.optToUpperCase) << endl;
    cout << KEY_OPTION_UMLAUTS << " is " << GetBoolAsText(config_.optProcessUmlauts) << endl;
    cout << endl;
}