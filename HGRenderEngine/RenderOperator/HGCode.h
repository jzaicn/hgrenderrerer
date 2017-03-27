#pragma  once


#include "stdafx.h"
#include <string>

#define HGCodeCharBuffMaxLen 512

class HGCode
{
private:
	// ��UTF-8ת����Unicode
	static void one_UTF8_To_Unicode(wchar_t* pOut,char *pText);  
	//UTF-8 תΪ GB2312
	static void one_UTF_8To_GB2312(std::string &pOut, char *pText, int pLen);

	//Unicode ת����UTF-8
	static void one_Unicode_To_UTF8(char* pOut,wchar_t* pText);  
	//��Unicode ת���� GB2312
	static void one_Unicode_To_GB2312(char* pOut,wchar_t uData);  

	//GB2312 ת���ɡ�Unicode
	static void one_Gb2312_To_Unicode(wchar_t* pOut,char *gbBuffer);
	//GB2312 תΪ UTF-8
	static void one_GB2312_To_UTF8(std::string& pOut,char *pText, int pLen);



#ifdef _UNICODE
	//////////////////////////////////////////////////////////////////////////
	// MFC unicode ����
private:
	static char* szResult;
	static wchar_t* wszResult;
public:
	// wchar ת char
	static const char* wchar_t_Unicode_To_GB2312(wchar_t* str);
	// char ת wchar
	static const wchar_t* char_Gb2312_To_Unicode(const char* szTestNew);

	// ����ʹ��
	static const char* convert(CString& str)
	{
		return wchar_t_Unicode_To_GB2312(str.GetBuffer());
	}
	// ����ʹ��
	static const char* convert(wchar_t* wszTestNew)
	{
		return wchar_t_Unicode_To_GB2312(wszTestNew);
	}
	// ����ʹ��
	static const wchar_t* convert(const char* szTestNew)
	{
		return char_Gb2312_To_Unicode(szTestNew);
	}
	// ����ʹ��
	static const wchar_t* convert(std::string& str)
	{
		return char_Gb2312_To_Unicode(str.c_str());
	}
#else
	//////////////////////////////////////////////////////////////////////////
	//	MFC ���ֽڹ���
public:
	//����ʹ��
	static const char* convert(const char* str)
	{
		return str;
	}
	static void CString_Unicode_To_GB2312(CString& cstr);
	static void CString_GB2312_To_Unicode(CString& cstr);
#endif

};