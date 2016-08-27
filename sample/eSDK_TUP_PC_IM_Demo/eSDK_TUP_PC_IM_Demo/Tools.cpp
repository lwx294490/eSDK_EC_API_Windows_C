/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#include "StdAfx.h"
#include "Tools.h"
#include <fstream>
CTools::CTools(void)
{
}

CTools::~CTools(void)
{
}

CString CTools::ANSI2UNICODE(std::string& strUtf8) 
{ 
	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, strUtf8.c_str(), -1, NULL, 0);  
	wchar_t *pwText;  
	pwText = new wchar_t[dwNum];  
	MultiByteToWideChar (CP_ACP, 0, strUtf8.c_str(), -1, pwText, dwNum);  
	std::wstring rt;  
	rt = ( wchar_t* )pwText;
	CString cstr = rt.c_str();
	delete [] pwText; 
	pwText = NULL;
	return cstr;
}  

std::wstring CTools::string2wstring(const std::string& str)
{
	//确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode =  new  wchar_t[nLen+1];  
	memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete [] pUnicode; 
	pUnicode = NULL;
	return rt;
}

CString CTools::UTF2UNICODE(const std::string& str)
{
	//确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode =  new  wchar_t[nLen+1];  
	memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	CString cstr = rt.c_str();
	delete [] pUnicode; 
	pUnicode = NULL;
	return cstr;
}
std::string CTools::UNICODE2UTF(const CString& cstr)
{
	char*     pElementText;
	int    iTextLen;
	std::wstring wstr = cstr;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_UTF8,
		0,
		wstr.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_UTF8,
		0,
		wstr.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL );
	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	pElementText = NULL;
	return strText;
}

void CTools::CString2Char(const CString &str,char* ch,unsigned int lenth)
{
	std::string stdstr = UNICODE2UTF(str);
	strncpy_s(ch, lenth * sizeof(char), stdstr.c_str(), _TRUNCATE);
}
void CTools::string2CString(const std::string& str,CString& CStr)
{
	CStr = UTF2UNICODE(str);
}
TUP_INT64 CTools::GetCurUTCTime()
{
	CTime cur = CTime::GetCurrentTime();
	return cur.GetTime()*1000;
}
CString CTools::FormatUTCTime(TUP_INT64& iUTCtime)
{
	CTime cur(iUTCtime/1000);
	CString cstrTime = cur.Format(_T("%Y-%m-%d %H:%M:%S"));
	return cstrTime;
}

CString CTools::getCurrentPath()
{
	TCHAR tcPath[MAX_PATH];
	TCHAR tcFilename[MAX_PATH];
	TCHAR tcDrive[_MAX_DRIVE];
	TCHAR tcDir[_MAX_DIR];
	TCHAR tcFname[_MAX_FNAME];
	TCHAR tcExt[_MAX_EXT];

	GetModuleFileName(NULL, tcFilename, _MAX_PATH);

	_tsplitpath_s(tcFilename, tcDrive, tcDir, tcFname, tcExt);
	_tcscpy_s(tcPath, tcDrive); 
	_tcscat_s(tcPath, tcDir);

	CString strAppPath = tcPath;
	int nPos = strAppPath.ReverseFind (_T('\\'));
	strAppPath = strAppPath.Left (nPos); 
	return strAppPath;
}

void CTools::GetIPPort(const std::string& serverURL,std::string& ip,int& port)
{
	ip.clear();
	std::string instr = serverURL;
	string::size_type pos = instr.find(':');
	if( pos != string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort = instr.substr(pos+1);
		port =  atoi(outPort.c_str());
	}
	else
	{
		ip = "";
		port = 0;
	}


	return;
}
void CTools::GetUserDefineImage(TUP_CHAR* id,TUP_CHAR* data,TUP_UINT32 length,CString& fileiamge)
{
	CString cstrFile = getCurrentPath();
	CString filename;
	filename.Format(_T("\\%s.png"),UTF2UNICODE(id));
	cstrFile.Append(filename);
	std::string temp = UNICODE2UTF(cstrFile);
	std::ofstream fos(string2wstring(temp).c_str(),std::ios::binary);
	fos.write(data, length);
	fos.close();
	fileiamge = cstrFile;

}

std::string CTools::GetLocalIPAddress()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	string ip;
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup( );
	}
	return ip;
}

void CTools::ReplaceToXMLString(std::string& str, std::string strXML, const std::string& strReplace)
{
	size_t beginPos = str.find(strXML);
	std::string tempstr = str;
	size_t len = 0;
	while (beginPos != std::string::npos)
	{
		(void)str.replace(beginPos + len, strXML.size(), strReplace);
		tempstr = str;
		len = beginPos + len + strReplace.size();
		tempstr = tempstr.substr(len);
		beginPos = tempstr.find(strXML);
	}
}

void CTools::ReplaceParagraphTag(std::string& str)
{
	ReplaceToXMLString(str, "<DIV>", "");
	ReplaceToXMLString(str, "</DIV>", "");
	ReplaceToXMLString(str, "<div>", "");
	ReplaceToXMLString(str, "</div>", "");
	ReplaceToXMLString(str, "<P>", "");
	ReplaceToXMLString(str, "</P>", "");
	ReplaceToXMLString(str, "<p>", "");
	ReplaceToXMLString(str, "</p>", "");
}

void CTools::ReplaceSpecialTag(std::string& str)
{
	ReplaceToXMLString(str, "&amp;", "&");
	ReplaceToXMLString(str, "&lt;", "<");
	ReplaceToXMLString(str, "&gt;", ">");
	ReplaceToXMLString(str, "&apos;", "\'");
	ReplaceToXMLString(str, "&quot;", "\"");
	ReplaceToXMLString(str, "&nbsp;", " ");
	ReplaceToXMLString(str, "&amp;nbsp;", " ");
	ReplaceToXMLString(str, "&lt;BR&gt;", "\r\n");
}