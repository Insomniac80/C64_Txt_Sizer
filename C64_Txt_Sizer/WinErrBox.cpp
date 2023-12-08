#include "WinErrBox.hpp"

WinErrBox::WinErrBox(const char* message_, BtnChoice btnChoice_)
	: WinErrBox(CA2CT(message_), btnChoice_)
{
}

WinErrBox::WinErrBox(const char* message_, const char* header_, BtnChoice btnChoice_)
	: WinErrBox(CA2CT(message_), CA2CT(header_), btnChoice_)
{
}

WinErrBox::WinErrBox(const char* message_, const char* header_, const char* param_, BtnChoice btnChoice_)
	: WinErrBox(CA2CT(message_), CA2CT(header_), CA2CT(param_), btnChoice_)
{
}

WinErrBox::WinErrBox(const wchar_t* message_, BtnChoice btnChoice)
	: WinErrBox(message_, L"Something went wrong", btnChoice)
{
}

WinErrBox::WinErrBox(const wchar_t* message_, const wchar_t* header_, BtnChoice btnChoice_)
	: WinErrBox(message_, header_, L"", btnChoice_)
{
}

WinErrBox::WinErrBox(const wchar_t* message_, const wchar_t* header_, const wchar_t* param_, BtnChoice btnChoice_)
	: mHeader(header_)
	, mMessage(message_)
	, mParam(param_)
	, mBtnChoice(btnChoice_)
{
}

WinErrBox::~WinErrBox()
{
	if (!mShown)
	{
		try {
			mMessage.insert(0, L"MESSAGE SENT BY DESTRUCTOR! \n FIX THIS! \n");
		}
		catch (const std::exception&)
		{
			WinErrBox("Caught in constructor!"
				, BtnChoice::Ok).Show();			
		}
	}
}

BtnState WinErrBox::Show() const
{
	return Show({});
}

BtnState WinErrBox::Show(const vector<BtnThrow>& throwOns_) const
{
	mShown = true;

	const auto msgboxID = MessageBox(
		nullptr,
		BuildMessage(mMessage.c_str(), mParam.c_str()).c_str(),
		mHeader.c_str(),
		EnumToNum(mBtnChoice)
	);

	if (std::ranges::find(throwOns_, static_cast<BtnThrow>(msgboxID)) != throwOns_.end())
		throw std::exception();

	return static_cast<BtnState>(msgboxID);
}

wstring WinErrBox::BuildMessage(const wstring& message_, const wstring& param_) const
{
	if (param_.empty())
		return message_;
	else
	{
		wstringstream msg;
		msg << message_;
		msg << L"\nthrown by:\n";
		msg << param_;
		std::wcout << msg.str().c_str() << std::endl;
		return msg.str().c_str();
	}
}