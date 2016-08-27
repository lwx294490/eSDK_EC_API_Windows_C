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

#include <TlHelp32.h>
#include <fstream>
#include <string>

//************************************************************************
CTools::CTools(void)
{
}
//************************************************************************
CTools::~CTools(void)
{
}
//************************************************************************
CString CTools::ANSI2UNICODE(std::string& strUtf8) 
{ 
	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, strUtf8.c_str(), -1, NULL, 0);  
	wchar_t *pwText;  
	pwText = new wchar_t[dwNum];  
	MultiByteToWideChar (CP_ACP, 0, strUtf8.c_str(), -1, pwText, dwNum);  
	std::wstring rt;  
	rt = ( wchar_t* )pwText;
	CString cstr = rt.c_str();
	delete  pwText; 
	return cstr;
}  
//************************************************************************
void CTools::CString2Char(const CString &str,char* ch,unsigned int lenth)
{
	std::string stdstr = UNICODE2UTF(str);
	strncpy_s(ch, lenth * sizeof(char), stdstr.c_str(), _TRUNCATE);
}
//************************************************************************
void CTools::string2CString(const std::string& str,CString& CStr)
{
	CStr = UTF2UNICODE(str);
}
//************************************************************************
std::wstring CTools::string2wstring(const std::string& str)
{
	//确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode =  new  wchar_t[nLen+1];  
	memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode; 
	return rt;
}
//************************************************************************
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
	return strText;
}
//************************************************************************
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
	delete  pUnicode; 
	return cstr;
}
//************************************************************************
void CTools::OpenURL( const CString &strURI )
{
	// 获得默认浏览器文件的名称
	TCHAR szBrowserName[256];
	DWORD dwCount = 256;
	ZeroMemory(szBrowserName, 256);

	// 打开链接时强制用ie浏览器
	HKEY hKey = NULL;
	long lReturn = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\IEXPLORE.EXE"), 0 , KEY_QUERY_VALUE , &hKey);

	if (0L == lReturn)
	{
		RegQueryValueEx(hKey, _T(""), 0, &dwCount, (BYTE*)szBrowserName, &dwCount);
		RegCloseKey(hKey);
	}

	if ( szBrowserName[0] == '\0' )
	{
		::ShellExecute(NULL, _T("open"),  strURI, NULL, NULL, SW_MAXIMIZE);
		return;
	}

	//做一个转换，因为注册表中写的浏览器全路径名带参数
	CString strFileName = szBrowserName;

	// 全部转成小写
	strFileName = strFileName.MakeLower();

	// 查找.exe的位置
	int iIndex = strFileName.Find(_T(".exe"));
	if (iIndex > 0)
	{
		//真正的浏览器的全路径名
		strFileName = strFileName.Left( iIndex+4 );

		//判断左侧是否带引号
		if( strFileName.GetAt( 0 ) == '\"' )
		{
			strFileName = strFileName.Mid( 1 , strFileName.GetLength()-1 );
		}	
	}

	::ShellExecute( NULL, _T("open"), strFileName , strURI,  NULL, SW_SHOWNORMAL);
}

bool CTools::GetBestHostip(std::string& ip, const std::string& serverip)
{
	DWORD destAddr = inet_addr(serverip.c_str());

	MIB_IPFORWARDROW bestRoute;
	memset(&bestRoute, 0, sizeof(bestRoute));
	if (NO_ERROR != GetBestRoute((DWORD)destAddr, 0, &bestRoute))
	{
		return false;
	}

	MIB_IPADDRTABLE buf;
	PMIB_IPADDRTABLE pIPAddrTable = (MIB_IPADDRTABLE*)&buf;
	if ( !pIPAddrTable )
	{
		return false;
	}

	// Make an initial call to GetIpAddrTable to get the
	// necessary size into the dwSize variable
	DWORD dwSize = 0;
	if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
	{
		if ( !pIPAddrTable )
		{
			return false;
		}
	}

	char* strTable = new char[dwSize];
	pIPAddrTable = (MIB_IPADDRTABLE*)strTable;

	// Make a second call to GetIpAddrTable to get the
	// actual data we want
	DWORD dwRetVal;
	if ( (dwRetVal = GetIpAddrTable( pIPAddrTable, &dwSize, 0 )) != NO_ERROR ) 
	{ 
		return false;
	}

	bool ret = false;
	for (DWORD i=0; i<pIPAddrTable->dwNumEntries; ++i)
	{
		const MIB_IPADDRROW& entry = pIPAddrTable->table[i];
		char * ipaddr1 = NULL;
		const unsigned IPLENGTH = 20;//ip 字符串长度
		char addr1[IPLENGTH]={0};
		in_addr inaddr1;
		inaddr1.s_addr=entry.dwAddr;
		ipaddr1 = inet_ntoa(inaddr1);
		strcpy_s(addr1,IPLENGTH,ipaddr1); 
		if (entry.dwIndex == bestRoute.dwForwardIfIndex)
		{
			bool found = false;
			if (entry.dwMask <= 0 || entry.dwMask  >= (unsigned long)255*255*255*255)
			{
				//////子网掩码不存在默认此种情况下是拨号方式//////
				found = true;
			} 
			else
			{
				if (0 == bestRoute.dwForwardNextHop)
					found = (entry.dwAddr&bestRoute.dwForwardMask) == (bestRoute.dwForwardDest&bestRoute.dwForwardMask);
				else
					found = (entry.dwAddr&entry.dwMask) == (bestRoute.dwForwardNextHop&entry.dwMask);
			}
			if (found)
			{
				char * ipaddr = NULL;
				const unsigned IPLENGTH = 20;//ip 字符串长度
				char addr[IPLENGTH]={0};
				in_addr inaddr;
				inaddr.s_addr=entry.dwAddr;
				ipaddr = inet_ntoa(inaddr);
				strcpy_s(addr,IPLENGTH,ipaddr);  
				if (strcmp(addr,"0.0.0.0") !=0  && strcmp(addr,"127.0.0.1") !=0)
				{
					ip = addr;
					ret = true;
				}
			}
		}
	}

	delete[] strTable;
	return ret;
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
	std::string::size_type pos = instr.find(':');
	std::string::size_type pos1 = instr.find(';');
	if( pos != std::string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort("");
		if ( std::string::npos == pos1)
		{
			//UC服务器地址172.22.8.61:8011
			outPort = instr.substr(pos+1);
		} 
		else
		{
			//SIP服务器地址，返回值有3个，必然有;为界/////
			outPort = instr.substr(pos+1, pos1-pos-1);
		}
		port =  atoi(outPort.c_str());
	}
	else
	{
		ip = "";
		port = 0;
	}

	return;
}