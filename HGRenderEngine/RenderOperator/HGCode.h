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

private:
	static char* szResult;
	static wchar_t* wszResult;

public:
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
	// wchar ת char
	static const char* wchar_t_Unicode_To_GB2312(wchar_t* str)
	{
		if (szResult)
		{
			delete szResult;
			szResult = NULL;
		}
		int nChar = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);    // ���ؽ���Ѱ���'\0'��Ҫռ�õ��ڴ�
		nChar = nChar * sizeof(char);
		//char* szResult = new char[nChar];
		szResult = new char[nChar];
		ZeroMemory(szResult, nChar);
		int i = WideCharToMultiByte(CP_ACP, 0, str, -1, szResult, nChar, NULL, NULL);
		int nszResultLen = lstrlenA(szResult);            
		int nszResultSize = sizeof(szResult);            

#if 0	// DEMO
		wchar_t wszTest[] = L"ziwuge";
		wchar_t wszTestNew[] = L"ziwuge����԰";
		int nwszTestLen = lstrlenW(wszTest);            // 6
		int nwszTestNewLen = lstrlenW(wszTestNew);        // 9
		int nwszTestSize = sizeof(wszTest);                // 14
		int nwszTestNewSize = sizeof(wszTestNew);        //    20
		int nChar = WideCharToMultiByte(CP_ACP, 0, wszTestNew, -1, NULL, 0, NULL, NULL);    // 13, ���ؽ���Ѱ���'\0'��Ҫռ�õ��ڴ�
		nChar = nChar * sizeof(char);                    // 13, ��ʵ��һ���ɲ���Ҫ,�������ǰ�����
		char* szResult = new char[nChar];
		ZeroMemory(szResult, nChar);
		int i = WideCharToMultiByte(CP_ACP, 0, wszTestNew, -1, szResult, nChar, NULL, NULL);    // 13
		int nszResultLen = lstrlenA(szResult);            // 12
		int nszResultSize = sizeof(szResult);            // 4
#endif // DEMO

		return szResult;
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
	// char ת wchar
	static const wchar_t* char_Gb2312_To_Unicode(const char* szTestNew)
	{
		if (wszResult)
		{
			delete wszResult;
			wszResult = nullptr;
		}

		int nszTestNewLen = lstrlenA(szTestNew);        
		int nszTestNewSize = sizeof(szTestNew);           
		int nWChar = MultiByteToWideChar(CP_ACP, 0, szTestNew, -1, NULL, 0);        // ���ؽ���Ѱ���'\0'��Ҫռ�õ��ڴ�
		nWChar = nWChar * sizeof(wchar_t);               
		wszResult = new wchar_t[nWChar];
		ZeroMemory(wszResult, nWChar);
		int j = MultiByteToWideChar(CP_ACP, 0, szTestNew, -1, wszResult, nWChar);    
		int nwszResultLen = lstrlenW(wszResult);        
		int nwszResultSize = sizeof(wszResult);           
		return wszResult;

#if 0	//DEMO
		char szTest[] = "ziwuge";
		char szTestNew[] = "ziwuge����԰";
		int nszTestLen = lstrlenA(szTest);                // 6
		int nszTestNewLen = lstrlenA(szTestNew);        // 12
		int nszTestSize = sizeof(szTest);                // 7
		int nszTestNewSize = sizeof(szTestNew);            // 13
		int nWChar = MultiByteToWideChar(CP_ACP, 0, szTestNew, -1, NULL, 0);        // 10, ���ؽ���Ѱ���'\0'��Ҫռ�õ��ڴ�
		nWChar = nWChar * sizeof(wchar_t);                // 20
		wchar_t* wszResult = new wchar_t[nWChar];
		ZeroMemory(wszResult, nWChar);
		int j = MultiByteToWideChar(CP_ACP, 0, szTestNew, -1, wszResult, nWChar);    // 10
		int nwszResultLen = lstrlenW(wszResult);        // 9
		int nwszResultSize = sizeof(wszResult);            // 4
		return 0;
#endif	//DEMO
	}
};