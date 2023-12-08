#pragma once

#ifdef DEBUG

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class ForDebug
{

public:

    // Do not move in cpp as VS debug define will fail

    ForDebug() = default;

    void PrintSeparationLine(const char* name_ = nullptr)
    {
        cout << "\n- - - - - - - - - - - - ";
        if (name_)
            cout << name_;
        cout << " - - - - - - - - - - - -" << endl;
    }

    void PrintVecOfStrings(const vector<string>& toPrint_)
    {
        for (const auto& entry : toPrint_)
            cout << entry << endl;
    }

    void PrintVecOfStringsWithHeader(const char* header_, const vector<string>& toPrint_)
    {
        PrintSeparationLine(header_);
        PrintVecOfStrings(toPrint_);
    }

};

#endif
