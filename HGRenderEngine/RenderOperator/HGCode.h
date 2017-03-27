#pragma  once


#include "stdafx.h"
#include <string>

#define HGCodeCharBuffMaxLen 512

class HGCode
{
private:
	// 把UTF-8转换成Unicode
	static void one_UTF8_To_Unicode(wchar_t* pOut,char *pText);  
	//UTF-8 转为 GB2312
	static void one_UTF_8To_GB2312(std::string &pOut, char *pText, int pLen);

	//Unicode 转换成UTF-8
	static void one_Unicode_To_UTF8(char* pOut,wchar_t* pText);  
	//把Unicode 转换成 GB2312
	static void one_Unicode_To_GB2312(char* pOut,wchar_t uData);  

	//GB2312 转换成　Unicode
	static void one_Gb2312_To_Unicode(wchar_t* pOut,char *gbBuffer);
	//GB2312 转为 UTF-8
	static void one_GB2312_To_UTF8(std::string& pOut,char *pText, int pLen);



#ifdef _UNICODE
	//////////////////////////////////////////////////////////////////////////
	// MFC unicode 工程
private:
	static char* szResult;
	static wchar_t* wszResult;
public:
	// wchar 转 char
	static const char* wchar_t_Unicode_To_GB2312(wchar_t* str);
	// char 转 wchar
	static const wchar_t* char_Gb2312_To_Unicode(const char* szTestNew);

	// 方便使用
	static const char* convert(CString& str)
	{
		return wchar_t_Unicode_To_GB2312(str.GetBuffer());
	}
	// 方便使用
	static const char* convert(wchar_t* wszTestNew)
	{
		return wchar_t_Unicode_To_GB2312(wszTestNew);
	}
	// 方便使用
	static const wchar_t* convert(const char* szTestNew)
	{
		return char_Gb2312_To_Unicode(szTestNew);
	}
	// 方便使用
	static const wchar_t* convert(std::string& str)
	{
		return char_Gb2312_To_Unicode(str.c_str());
	}
#else
	//////////////////////////////////////////////////////////////////////////
	//	MFC 多字节工程
public:
	//方便使用
	static const char* convert(const char* str)
	{
		return str;
	}
	static void CString_Unicode_To_GB2312(CString& cstr);
	static void CString_GB2312_To_Unicode(CString& cstr);
#endif

};