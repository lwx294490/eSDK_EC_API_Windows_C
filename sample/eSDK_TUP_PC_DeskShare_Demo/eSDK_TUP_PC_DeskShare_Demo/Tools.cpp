#include "StdAfx.h"
#include "Tools.h"
CTools::CTools(void)
{
}

CTools::~CTools(void)
{
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
	delete  pUnicode; 
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
	return strText;
}

void CTools::CString2Char(const CString &str,char* ch,unsigned int lenth)
{
	std::string stdstr = UNICODE2UTF(str);
	//strncpy_s(ch,lenth,stdstr.c_str(),stdstr.size());
	strncpy(ch, stdstr.c_str(), lenth);
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


//std::string CTools::GetLocalIPAddress()
//{
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	char name[255];
//	string ip;
//	PHOSTENT hostinfo;
//	wVersionRequested = MAKEWORD( 2, 0 );
//	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
//	{
//		if( gethostname ( name, sizeof(name)) == 0)
//		{
//			if((hostinfo = gethostbyname(name)) != NULL)
//			{
//				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
//			}
//		}
//		WSACleanup( );
//	}
//	return ip;
//}


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
	strTable = NULL;
	return ret;
}