#include "Structs.h"
#include "WinErrBox.hpp"
#include "TxtFileToStrings.h"
#include "ToKeyValue.h"
#include "Defines.h"
#include "CreateFile.h"
#include "ForDebug.h"
#include "ReadConfig.h"
#include "FoldersAndFilenames.h"
#include "Interaction.h"
#include "TextProcessor.h"
#include "ToFile.h"

#include <string>
#include <vector>
#include <iostream> 
#include <ctype.h>

using std::string;
using std::vector;
using std::cin;

string GetPathProgram(int argc, char* argv[])
{
    if (argc < 1) {
        WinErrBox("Path to app not found.\nProgram will exit now."
            , BtnChoice::Ok).Show();
        exit(0);
    }

    // first argument is always path and filename of program
    return { argv[0], 0, string(argv[0]).find_last_of("\\") };
}

PathFilename GetPathFilenameConfig(string_view path_)
{
    PathFilename pathFilenameConfig;
    pathFilenameConfig.path = path_;
    pathFilenameConfig.filename = CONFIG_NAME;
    pathFilenameConfig.enumFileName = FileName::ConfigProgram;
    return pathFilenameConfig;
}

vector<string> GetTxtFilesOfFolder(string_view programPath_)
{
    auto foldersAndFilenames = FoldersAndFilenames(programPath_); 
    if (!foldersAndFilenames.Success())
    {
        WinErrBox(std::format("Error\n{} \nhas occurred when reading folder content.\nProgram will exit now.", foldersAndFilenames.GetFileError()).c_str()
            , BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
    }
    return foldersAndFilenames.GetFilesWithoutPaths(string(programPath_), { "txt" });
}

vector<string> RemoveFilesWithSuffix(vector<string> allFiles_, const Configuration& config_)
{
    if (config_.ignoreWrittenFiles)
    {
        auto suffixPresent = [&config_](string_view scanForSuffix_) {
            return (scanForSuffix_.find(config_.appendToFilename) != std::string::npos);
        };
        std::erase_if(allFiles_, suffixPresent);
    }
    return allFiles_;
}

void PrintSuccess()
{
    cout << "\nProgram has finished expected. Press enter to close this window." << endl;
    string rawInput;
    while (getline(cin, rawInput))
    {
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    try
    {
        const auto programPath = GetPathProgram(argc, argv);

        const Configuration config(ReadConfig(GetPathFilenameConfig(programPath)));

        const auto fileListComplete = RemoveFilesWithSuffix(GetTxtFilesOfFolder(programPath), config);

        auto interaction = Interaction(fileListComplete, config);

        auto [texts, indices] = TextProcessor(programPath, fileListComplete, interaction.GetIndicesFromUser(), config).GetTextsAndIndices();

        // check texts indices for same size
        for (size_t i{ 0 }; i < indices.size(); ++i) {
            ToFile(programPath, fileListComplete.at(indices.at(i)), texts.at(i), config);
        }

        PrintSuccess();
    }
    catch (const std::exception& exc) 
    {
        WinErrBox(std::format("Error\n{} \nhas occurred.\nProgram will exit now.", exc.what()).c_str()
            , BtnChoice::Ok).Show();
        return EXIT_FAILURE;
    }
}