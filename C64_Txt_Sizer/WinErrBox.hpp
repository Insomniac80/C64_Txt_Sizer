#pragma once

#include <Windows.h>
#include <winuser.h>
#include <atlstr.h>

#include <string>
#include <sstream>
#include <vector>

#include <iostream>

using std::wstring;
using std::wstringstream;
using std::vector; 

template <typename E>
constexpr typename std::underlying_type_t<E> EnumToNum(E e) noexcept {
	return static_cast<typename std::underlying_type_t<E>>(e);
}

enum class BtnChoice {
	Ok = MB_OK,
	OkCancel = MB_OKCANCEL,
	AbortRetryIgnore = MB_ABORTRETRYIGNORE,
	YesNoCancel = MB_YESNOCANCEL,
	YesNo = MB_YESNO,
	RetryCancel = MB_RETRYCANCEL,
	CancelTryContinue = MB_CANCELTRYCONTINUE,
	Help = MB_HELP
};

enum class BtnState {
	Ok = IDOK,
	Cancel = IDCANCEL,
	Abort = IDABORT,
	Retry = IDRETRY,
	Ignore = IDIGNORE,
	Yes = IDYES,
	No = IDNO,
	Close = IDCLOSE,
	Help = IDHELP,
	Try = IDTRYAGAIN,
	Continue = IDCONTINUE
};

using BtnThrow = BtnState;

class WinErrBox
{

public:

	WinErrBox(const char* message_, BtnChoice btnChoice_);
	WinErrBox(const char* message_, const char* header_, BtnChoice btnChoice_);
	WinErrBox(const char* message_, const char* header_, const char* param_, BtnChoice btnChoice_);
	WinErrBox(const wchar_t* message_, BtnChoice btnChoice_);
	WinErrBox(const wchar_t* message_, const wchar_t* header_, BtnChoice btnChoice_);
	WinErrBox(const wchar_t* message_, const wchar_t* header_, const wchar_t* param_, BtnChoice btnChoice_);

	~WinErrBox();

	BtnState Show() const;
	BtnState Show(const vector<BtnThrow>& throwOns_) const;

private:

	mutable bool mShown{ false };

	const wstring mHeader;
	wstring mMessage;
	const wstring mParam;
	const BtnChoice mBtnChoice;

	wstring BuildMessage(const wstring& message_, const wstring& param_) const;
};

