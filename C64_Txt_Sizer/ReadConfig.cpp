#include "ReadConfig.h"

ReadConfig::ReadConfig(const PathFilename& pathFilename_)
    : mConfig(ToKeyValue{ ReadFromFile(pathFilename_ )})
{}

bool ReadConfig::GetValueAsBool(const char* key_) const
{
    auto value = GetValueAsString(key_);
    if (value.compare("true") == 0)
        return true;
    if (value.compare("false") == 0)
        return false;

    // read new instead of copy paste convert code
    auto asInt = GetValueAsInt(key_);

    if (asInt < 0 || asInt > 1)
        ReadFailedExit(key_, FailureReason::OutOfRange);

    return static_cast<bool>(asInt);
}

int64_t ReadConfig::GetValueAsInt(const char* key_) const
{
    auto value = GetValueAsString(key_);

    try {
        return stoi(value);
    }
    catch (const std::exception& exc)
    {   // will trigger if to string fails
        ReadFailedExit(key_, FailureReason::ToNumberFailed);
        return {};
    }
}

uint64_t ReadConfig::GetValueAsUint(const char* key_) const
{
    const auto asInt(GetValueAsInt(key_));
    if (asInt < 0)
        ReadFailedExit(key_, FailureReason::OutOfRange);

    return static_cast<uint64_t>(asInt);
}

string ReadConfig::GetValueAsString(const char* key_) const
{
    auto [success, value] = mConfig.GetAsStringNoSpaces(key_);
    if (!success)
        ReadFailedExit(key_, FailureReason::KeyNotFound);

    return value;
}

vector<string> ReadConfig::ReadFromFile(const PathFilename& pathFilename_) const
{
    if (!pathFilename_.IsValid())
        WinErrBox("PathFilename_ has unset parameter. Aborting."
            , BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });

    TxtFileToStrings fileDump(pathFilename_.path + "\\" + pathFilename_.filename);
    if (!fileDump.FileExists())
        CreateLocalFile lf(pathFilename_);

    if (fileDump.FileExists()) {
        auto err = fileDump.ReadFromFile();
        if (!((ERR_FILEEMPTY == err) && !pathFilename_.toEditByUser))
            fileDump.HandleError(err);
    }

    #ifdef DEBUG
        ForDebug().PrintSeparationLine(pathFilename_.filename);
        fileDump.Print();
    #endif

    return fileDump.GetContent();
}

void ReadConfig::ReadFailedExit(const char* keyFailed_, FailureReason failureReason_) const
{
    WinErrBox(GetFailureString(keyFailed_, failureReason_).c_str()
        , BtnChoice::Ok).Show({ BtnThrow::Ok, BtnThrow::Cancel });
}

string ReadConfig::GetFailureString(const char* keyFailed_, FailureReason failureReason_) const
{
    switch (failureReason_) {
        case FailureReason::KeyNotFound:
            return string(string("Key ") + keyFailed_ + " not found in config.\nDelete config for rewrite.\nAborting.");
        case FailureReason::OutOfRange:
            return string(string("Key ") + keyFailed_ + " is out of range.\nDelete config for rewrite.\nAborting.");
        case FailureReason::ToNumberFailed:
            return string(string("Key ") + keyFailed_ + " could not be converted to number.\nRemove all characters from value and try again,\nor delete config for rewrite.\nAborting.");
        default:
            return string(string("Key ") + keyFailed_ + " failed for undocumented reason.\nAborting.");
    }
}
