#include "stdafx.h"
#include "HGCode.h"

#include <string>
#include <locale>
#include <codecvt>

//////////////////////////////////////////////////////////////////////////
// MFC UNICODE 字符集
#ifdef _UNICODE
wchar_t* HGCode::wszResult = nullptr;
char* HGCode::szResult = nullptr;
const char* HGCode::wchar_t_Unicode_To_GB2312(wchar_t* str)
{
	if (szResult)
	{
		delete szResult;
		szResult = NULL;
	}
	int nChar = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);    // 返回结果已包含'\0'所要占用的内存
	nChar = nChar * sizeof(char);
	//char* szResult = new char[nChar];
	szResult = new char[nChar];
	ZeroMemory(szResult, nChar);
	int i = WideCharToMultiByte(CP_ACP, 0, str, -1, szResult, nChar, NULL, NULL);
	int nszResultLen = lstrlenA(szResult);            
	int nszResultSize = sizeof(szResult);           

	return szResult;
}

const wchar_t* HGCode::char_Gb2312_To_Unicode(const char* szTestNew)
{
	if (wszResult)
	{
		delete wszResult;
		wszResult = nullptr;
	}

	int nszTestNewLen = lstrlenA(szTestNew);        
	int nszTestNewSize = sizeof(szTestNew);           
	int nWChar = MultiByteToWideChar(CP_ACP, 0, szTestNew, -1, NULL, 0);        // 返回结果已包含'\0'所要占用的内存
	nWChar = nWChar * sizeof(wchar_t);               
	wszResult = new wchar_t[nWChar];
	ZeroMemory(wszResult, nWChar);
	int j = MultiByteToWideChar(CP_ACP, 0, szTestNew, -1, wszResult, nWChar);    
	int nwszResultLen = lstrlenW(wszResult);        
	int nwszResultSize = sizeof(wszResult);           
	return wszResult;

}
#else

void HGCode::CString_Unicode_To_GB2312(CString& cstr)
{
	std::string str;
	one_UTF_8To_GB2312(str,cstr.GetBuffer(),cstr.GetLength());
	cstr = str.c_str();
}


void HGCode::CString_GB2312_To_Unicode(CString& cstr)
{
	std::string str;
	one_GB2312_To_UTF8(str,cstr.GetBuffer(),cstr.GetLength());
	cstr = str.c_str();
}

#endif


void HGCode::one_UTF8_To_Unicode(wchar_t* pOut,char *pText)
{
	char* uchar = (char *)pOut;

	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

	return;
}

void HGCode::one_Unicode_To_UTF8(char* pOut,wchar_t* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));

	return;
}

void HGCode::one_Unicode_To_GB2312(char* pOut,wchar_t uData)
{
	int a = WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
	return;
}    

void HGCode::one_Gb2312_To_Unicode(wchar_t* pOut,char *gbBuffer)
{
	int a = ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return ;
}

void HGCode::one_GB2312_To_UTF8(std::string& pOut,char *pText, int pLen)
{
	char buf[4];
	int nLength = pLen* 3;
	char* rst = new char[nLength];

	memset(buf,0,4);
	memset(rst,0,nLength);

	int i = 0;
	int j = 0;     
	while(i < pLen)
	{
		//如果是英文直接复制就能
		if( *(pText + i) >= 0)
		{
			rst[j++] = pText[i++];
		}
		else
		{
			wchar_t pbuffer;
			one_Gb2312_To_Unicode(&pbuffer,pText+i);

			one_Unicode_To_UTF8(buf,&pbuffer);

			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];    

			j += 3;
			i += 2;
		}
	}
	rst[j] = '\0';

	//返回结果
	pOut = rst;             
	delete []rst;  

	return;
}


void HGCode::one_UTF_8To_GB2312(std::string &pOut, char *pText, int pLen)
{
	char * newBuf = new char[pLen];
	char Ctemp[4];
	memset(Ctemp,0,4);

	int i =0;
	int j = 0;

	while(i < pLen)
	{         
		WCHAR Wtemp;
		one_UTF8_To_Unicode(&Wtemp,pText + i);

		one_Unicode_To_GB2312(Ctemp,Wtemp);

		newBuf[j] = Ctemp[0];
		newBuf[j + 1] = Ctemp[1];

		i += 3;    
		j += 2; 
	}
	newBuf[j] = '\0';

	pOut = newBuf;
	delete []newBuf;

	return;
} 

//std::wstring HGCode::UTF8_To_ws( const std::string& src )
//{
//	if(src.empty()) return L"";
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
//	std::wstring temp;
//	try
//	{
//		temp = conv.from_bytes( src );
//	}		
//	catch (const std::range_error& e)
//	{
//		temp =  conv.from_bytes(src.substr(0, conv.converted()));
//	}
//	return move(temp);
//}
//
//
//
//std::string HGCode::UTF8_To_s( const std::string& src )
//{
//	return CString(UTF8_To_ws(src).c_str()).GetBuffer();
//}