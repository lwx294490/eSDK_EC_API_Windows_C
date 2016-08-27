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
const int MAX_IMAGE_HEIGHT = 50;// 自定义图片高度
const int MAX_IMAGE_WIDTH = 55;// 自定义图片宽度

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
	delete[]  pwText; 
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
	delete[] pUnicode; 
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
	string::size_type pos1 = instr.find(';');
	if( pos != string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort("");
		if ( string::npos == pos1)
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

std::string CTools::num2str(int i)
{
	char str[STRING_LENGTH]= {0};
	sprintf_s(str,STRING_LENGTH-1,"%d",i);
	return std::string(str);
}

int CTools::str2num(const std::string& str)
{	
	return atoi(str.c_str());
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
	strTable = NULL;
	return ret;
}

void CTools::ShowMessageTimeout(LPCTSTR msg,DWORD delay)
{
	MessageBoxTimeout(NULL,msg,_T("Call Notify"),MB_OK,GetSystemDefaultLangID(),delay);
}

//************************************************************************
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
//************************************************************************
//************************************************************************
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

//************************************************************************
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

std::string CTools::MakeMixedIMContent(CString& imgPath)
{
	std::string cont_;

	if(imgPath.IsEmpty())
	{
		return cont_;
	}

	//起始标识
	cont_ = cont_ + "/:um_begin{";

	//文件路径
	CString strImagePath = imgPath;
	(void)strImagePath.Replace(L'/', L'\\');
	(void)strImagePath.Replace(_T("%20"), _T(" "));
	cont_ = cont_ + CTools::UNICODE2UTF(strImagePath);

	//文件类型
	cont_ = cont_ + "|Img";

	//文件大小
	ULONGLONG uTotal = CTools::GetFileSize(strImagePath);
	uTotal = uTotal/1024;
	CString filesize;
	filesize.Format(_T("|%d"),  uTotal);
	cont_ = cont_ + CTools::UNICODE2UTF(filesize);

	//文件名称
	CString filePathTmp = imgPath;
	int pos = filePathTmp.ReverseFind('\\');
	if(-1 != pos)
	{
		CString fileName = filePathTmp.Right(((filePathTmp.GetLength() - pos) -1));
		cont_ = cont_ + "|";
		cont_ = cont_ + CTools::UNICODE2UTF(fileName);
	}

	//播放时长，Img填0
	cont_ = cont_ + "|0";

	//附加参数  图片大小width;height  云盘提取码code  
	CImage image;
	image.Load(strImagePath);
	char strWidth[16];
	(void)::sprintf_s(strWidth, 16, "%d", image.GetWidth());
	char strHeight[16];
	(void)::sprintf_s(strHeight, 16, "%d", image.GetHeight());
	cont_ = cont_ + "|" + strWidth;
	cont_ = cont_ + ";" + strHeight;
	cont_ = cont_ + ";[OfflineTransmissionCode][NULL]";

	//结尾标识
	cont_ = cont_ + "}/:um_end";
	return cont_;
}
CString CTools::GetFileName(const CString & fileFullPath, BOOL bHasExt)
{
	CString returnFileNameStr = _T("");
	if (fileFullPath.IsEmpty())
	{
		return returnFileNameStr;
	}

	returnFileNameStr = fileFullPath;
	int pos = returnFileNameStr.ReverseFind('\\');
	if (pos > 0)
	{
		returnFileNameStr = returnFileNameStr.Right((returnFileNameStr.GetLength() - pos) - 1);
	}

	//不带扩展名
	if (!bHasExt)
	{
		int extPos = returnFileNameStr.ReverseFind('.');
		if (extPos > 0)
		{
			returnFileNameStr = returnFileNameStr.Left(pos);
		}
	}

	return returnFileNameStr;
}

ULONGLONG CTools::GetFileSize(const CString & filePath)
{
	ULONGLONG fileSize = 0;

	CFileStatus fs;
	if (CFile::GetStatus(filePath, fs))
	{
		fileSize = fs.m_size;
	}

	return fileSize;
}
bool CTools::GetIMFromContent(CString &INcontent,IMINfo& m_IMinfo,vector<PicPathInfo>& m_ImageList)
{
	////1.判断消息是否来自移动端////
	bool m_IsPC = true;;
	if (17 == INcontent.MakeReverse().Find(_T(">lmth/<")))
	{
		m_IsPC = false;
	}
	INcontent.MakeReverse();
	////2.清空输出参数/////
	CString Oconteont("") ;
	m_ImageList.clear();
	m_IMinfo.Content = _T("");
	m_IMinfo.m_font.face = _T("");
	m_IMinfo.m_font.m_size = 0;
	m_IMinfo.m_font.m_rgb = RGB(0,0,0);
	int Beginpos = 0;
	int EndPos = 0;
	///3.解析UM信息//eSpace发送消息中只可能包含一个UM消息体/////
	CString m_strFileName("");  /////获取文件名/////
	Beginpos = INcontent.Find(_T("<imgname>"));
	EndPos = INcontent.Find(_T("</imgname>"));
	m_strFileName = INcontent.Mid(Beginpos + 9,EndPos - Beginpos -9); ////得到文件名
	Beginpos = INcontent.Find(_T("<content>"));
	INcontent = INcontent.MakeReverse();
	EndPos = INcontent.GetLength() - INcontent.Find(_T(">tnetnoc/<"));
	INcontent = INcontent.MakeReverse();
	Oconteont = INcontent.Mid(Beginpos + 9,EndPos - Beginpos - 19);
	bool m_isUMavalable = false;   ////是否含有UM信息/////
	map<int,CString> imglist;      ////放置UM信息////
	if (m_IsPC)
	{
		m_isUMavalable = (-1!= Oconteont.Find(m_strFileName))&&m_strFileName.GetLength();
		/////PC端截取方式需要严格些/////
		if (m_isUMavalable)
		{
			Beginpos = INcontent.Find(_T("<imgdata __type__=\"url\">"));
			EndPos = INcontent.Find(_T("</imgdata>"));
			CString iMURL = INcontent.Mid(Beginpos + 24,EndPos - Beginpos -24);
			Beginpos = Oconteont.Find(iMURL);
			EndPos = Oconteont.Find(_T("}"),Beginpos + iMURL.GetLength());
			Oconteont = Oconteont.Mid(Beginpos,EndPos - Beginpos);
			int  t = 0;
			while (-1 != Oconteont.Find(_T("|")))
			{
				////////////分割UM信息///
				EndPos = Oconteont.Find(_T("|"));
				imglist[t++] = Oconteont.Left(EndPos);
				Oconteont = Oconteont.Mid(EndPos + 1,Oconteont.GetLength() - EndPos -1);
			}
			imglist[t] = Oconteont;
		}
		else
		{
			imglist.clear();
		}
	}
	else
	{
		/////移动端的UM信息主要从/:um_begin  。。。 /:um_end中截取/////
		m_isUMavalable = (-1!= Oconteont.Find(_T("/:um_begin")))&&(Oconteont.Find(_T("/:um_end")));
		if (m_isUMavalable)
		{
			////有UM信息
			Beginpos = Oconteont.Find(_T("{"));
			EndPos = Oconteont.Find(_T("}"));
			Oconteont = Oconteont.Mid(Beginpos + 1,EndPos -Beginpos -1);
			int  t = 0;
			while (-1 != Oconteont.Find(_T("|")))
			{
				////////////分割UM信息//////
				EndPos = Oconteont.Find(_T("|"));
				imglist[t++] = Oconteont.Left(EndPos);
				Oconteont = Oconteont.Mid(EndPos + 1,Oconteont.GetLength() - EndPos -1);
			}
			imglist[t] = Oconteont;
		}
		else
		{
			imglist.clear();
		}

	}
	/////将UM信息填充到m_IMinfo.m_uminfo中/////
	if ( imglist.size())
	{
		////输出UM信息////
		m_IMinfo.m_uminfo.m_Pos = 0;    ////图片位置暂初始化为0，后续排查本地图标的时候，予以标注/////
		m_IMinfo.m_uminfo.umFileUrl = CTools::UNICODE2UTF(imglist[0]);
		m_IMinfo.m_uminfo.umFileType = CTools::UNICODE2UTF(imglist[1]);
		m_IMinfo.m_uminfo.umFileSize = CTools::UNICODE2UTF(imglist[2]);
		m_IMinfo.m_uminfo.umFileName = CTools::UNICODE2UTF(imglist[3]);
		m_IMinfo.m_uminfo.umFileDuration = CTools::UNICODE2UTF(imglist[4]);
		CString m_tmpUMCode = imglist[5];
		////提取第二个;后面的数据/////
		if (!m_tmpUMCode.IsEmpty() && _T("0") != m_tmpUMCode && _T(";;") != m_tmpUMCode)
		{
			Beginpos = m_tmpUMCode.ReverseFind(';');
			////提取第二个;后面的内容/////
			if (Beginpos >= 1 && Beginpos < m_tmpUMCode.GetLength() -1)
			{
				m_IMinfo.m_uminfo.umTransCode = CTools::UNICODE2UTF(m_tmpUMCode.Mid(Beginpos +1,m_tmpUMCode.GetLength() - Beginpos -1));
			}
			else
			{
				m_IMinfo.m_uminfo.umExtraParam ="";
			}
		}
		else
		{
			////UM信息需要全部作废/////
			m_IMinfo.m_uminfo.umFileUrl.clear();
			m_IMinfo.m_uminfo.umFileType.clear();
			m_IMinfo.m_uminfo.umFileSize.clear();
			m_IMinfo.m_uminfo.umFileName.clear();
			m_IMinfo.m_uminfo.umFileDuration.clear();
			m_IMinfo.m_uminfo.umTransCode.clear();
			m_IMinfo.m_uminfo.umExtraParam.clear();
		}
		/////清空UM信息/////
		imglist.clear();
	}

	///4. 解析消息////
	if (m_IsPC)
	{
		////PC侧消息解析////
		Beginpos = INcontent.Find(_T("<FONT"));
		EndPos = INcontent.Find(_T("</FONT>"));
		Oconteont = INcontent.Mid(Beginpos + 6,EndPos - Beginpos -6);
		EndPos = Oconteont.Find(_T(">"));
		CString m_strFont = Oconteont.Left(EndPos + 1);   ///// 带上“>”//////
		/////提取文字信息/////
		////1.提取SIZE////
		Beginpos = m_strFont.Find(_T(":"));
		EndPos = m_strFont.Find(_T("px"));
		m_IMinfo.m_font.m_size = CTools::str2num(CTools::UNICODE2UTF(m_strFont.Mid(Beginpos + 1,EndPos - Beginpos -1)));
		///2. 提取字体///////
		Beginpos = m_strFont.Find(_T("face"));
		if ( -1 != Beginpos)
		{
			/////存在face参数/////
			EndPos = m_strFont.Find(_T("color"));
			if (-1 != EndPos)
			{
				////存在color参数////
				int rr = strtol(CTools::UNICODE2UTF(m_strFont.Mid(EndPos + 7,2)).c_str(),NULL,16);
				int gg = strtol(CTools::UNICODE2UTF(m_strFont.Mid(EndPos + 9,2)).c_str(),NULL,16);
				int bb = strtol(CTools::UNICODE2UTF(m_strFont.Mid(EndPos + 11,2)).c_str(),NULL,16);
				m_IMinfo.m_font.m_rgb = RGB(rr,gg,bb);
				m_IMinfo.m_font.face = m_strFont.Mid(Beginpos + 6,EndPos - Beginpos -8);

			}
			else
			{
				//////存在face但是不存在color参数////
				m_IMinfo.m_font.face = Oconteont.Mid(Beginpos + 6,EndPos - Beginpos -7);
				m_IMinfo.m_font.m_rgb = RGB(0,0,0);
			}
		}
		else
		{
			////Face 参数都不存在/////
			m_IMinfo.m_font.m_rgb = RGB(0,0,0);
			m_IMinfo.m_font.face = _T("");
		}
		EndPos = m_strFont.Find(_T(">"));
		/////2. 检查是否存在<B></B>的信息
		Oconteont = Oconteont.Mid(EndPos + 1,Oconteont.GetLength() - EndPos -1);
		Beginpos = Oconteont.Find(_T("<I>"));
		if (-1 != Beginpos)
		{
			////存在斜体情况////
			EndPos = Oconteont.Find(_T("</I>"));
			Oconteont = Oconteont.Mid(Beginpos + 3,EndPos -Beginpos -3);
			m_IMinfo.m_font.m_isI = true;
		}
		Beginpos = Oconteont.Find(_T("<B>"));
		if (-1 != Beginpos)
		{
			////存在加粗情况////
			EndPos = Oconteont.Find(_T("</B>"));
			Oconteont = Oconteont.Mid(Beginpos + 3,EndPos -Beginpos -3);
			m_IMinfo.m_font.m_isB = true;
		}
		Beginpos = Oconteont.Find(_T("<U>"));
		if (-1 != Beginpos)
		{
			////存在下划线情况////
			EndPos = Oconteont.Find(_T("</U>"));
			Oconteont = Oconteont.Mid(Beginpos + 3,EndPos -Beginpos -3);
			m_IMinfo.m_font.m_isU = true;
		}
		// 转义字符二次替换
		Oconteont.Replace(_T("&amp;"), _T("&"));
		Oconteont.Replace(_T("&lt;"), _T("<"));
		Oconteont.Replace(_T("&gt;"), _T(">"));
		Oconteont.Replace(_T("&apos;"),_T("\'"));
		Oconteont.Replace(_T("&quot;"),_T("\""));
		Oconteont.Replace(_T("&nbsp;"),_T(" "));
		Oconteont.Replace(_T("&lt;BR&gt;"),_T("\r\n"));
		Oconteont.Replace(_T("<BR>"),_T("\r\n"));

		while (-1 != Oconteont.Find(_T("<IMG")))
		{
			////剔除IM内容和本地表情/////
			Beginpos = Oconteont.Find(_T("<IMG"));

			EndPos = Oconteont.Find(_T(">"));
			CString Tmp;  ////用来存放图片路径/////
			if (Beginpos < EndPos)
			{
				Tmp = Oconteont.Mid(Beginpos + 4,EndPos - Beginpos - 4);
			}
			else
			{
				m_IMinfo.Content.Append(Oconteont.Left(Beginpos));
				Oconteont = Oconteont.Mid(Beginpos,Oconteont.GetLength() - Beginpos);
				continue;
			}
			if ( -1 != Tmp.Find(_T("UC.InternalImg//emotion")))
			{
				///取字符/////
				m_IMinfo.Content.Append( Oconteont.Left(Beginpos));
				////查找表情并存储于vector中/////
				PicPathInfo m_pictureInfo;
				m_pictureInfo.pos = m_IMinfo.Content.GetLength();
				m_pictureInfo.picPath = CTools::UNICODE2UTF(Tmp);
				m_ImageList.push_back(m_pictureInfo);
				Oconteont = Oconteont.Mid(EndPos +1);///去掉最后的“<”
			}
			else if(-1 != Tmp.Find(CTools::UTF2UNICODE(m_IMinfo.m_uminfo.umFileName)))
			{
				///取字符/////
				m_IMinfo.Content.Append( Oconteont.Left(Beginpos));
				///截图信息不再内容中保存，直接剔除/////
				m_IMinfo.m_uminfo.m_Pos = m_IMinfo.Content.GetLength();
				Oconteont = Oconteont.Right(Oconteont.GetLength() - EndPos -1);
			}
			else
			{
				///将整个<IMG ...>中字符放入内容中;
				m_IMinfo.Content.Append(Oconteont.Left(EndPos + 1));
				Oconteont = Oconteont.Mid(EndPos + 1,Oconteont.GetLength() - EndPos - 1);
			}
		}
		m_IMinfo.Content.Append(Oconteont);
	}
	else
	{
		/////移动端消息解析/////
		Beginpos = INcontent.Find(_T("<content>"));
		INcontent = INcontent.MakeReverse();
		EndPos = INcontent.GetLength() - INcontent.Find(_T(">tnetnoc/<"));
		INcontent = INcontent.MakeReverse();
		Oconteont = INcontent.Mid(Beginpos + 9,EndPos - Beginpos - 19);
		/////仅处理非截图信息，截图信息上面已经处理了////
		if (-1 == Oconteont.Find(_T("um_begin")))
		{
			////初始化Emotion/////
			std::map<CString, CString> m_EmotionLab;
			CTools::GetEmotionLab(m_EmotionLab);
			Beginpos = Oconteont.Find(_T("CDATA"));
			if (-1 != Beginpos)
			{
				////有时候移动端消息带有CDATA这个无用字符////
				Oconteont = Oconteont.Mid(Beginpos + 6,Oconteont.GetLength() - Beginpos -9);
			}
			////文字，表情分离////
			while (-1 != Oconteont.Find(_T("/")))
			{
				Beginpos = Oconteont.Find(_T("/"));
				m_IMinfo.Content.Append(Oconteont.Left(Beginpos -1));
				CString tmp = Oconteont.Mid(Beginpos , 3);
				if ( m_EmotionLab[tmp].IsEmpty())
				{
					//////查询不到，表示该字符不是本地表情/////
					m_IMinfo.Content.Append(_T("/"));
					Oconteont = Oconteont.Mid(Beginpos + 1,Oconteont.GetLength() - Beginpos -1);
				}
				else
				{
					PicPathInfo m_pictureInfo;
					m_pictureInfo.pos = m_IMinfo.Content.GetLength();
					m_pictureInfo.picPath = CTools::UNICODE2UTF(m_EmotionLab[tmp]);
					m_ImageList.push_back(m_pictureInfo);
					Oconteont = Oconteont.Mid(Beginpos + 3 ,Oconteont.GetLength() - Beginpos -3);
				}
			}
			m_IMinfo.Content.Append(Oconteont);
		}
	}
	return m_IsPC;
}

void CTools::AnalysePCMessage(vector<PicPathInfo>& imglist)
{
	///////申请临时变量，存储有效信息//////
	vector<PicPathInfo> m_tmpImglist;
	////////获取emotion路径///////
	CString m_EmotionPath = CTools::getCurrentPath() + _T("\\Emotion\\");
	vector<PicPathInfo>::iterator itBegin = imglist.begin();
	for (;itBegin != imglist.end();itBegin++)
	{
		///将Emotion真实路径计算出来////
		CString tPath = CTools::UTF2UNICODE(itBegin->picPath);
		int m_BeginPos = tPath.Find(_T("emotion"));
		int m_sendPoints = tPath.Find(_T("gif"));
		if ((-1 != m_BeginPos) &&(-1 != m_sendPoints))
		{
			tPath = tPath.Mid(m_BeginPos + 8,tPath.GetLength()-m_BeginPos -9);
			itBegin->picPath = CTools::UNICODE2UTF(m_EmotionPath + tPath);
			/*m_tmpImglist[itBegin->] = itBegin->second;*/
			PicPathInfo m_picInfo;
			m_picInfo.index = 0;
			m_picInfo.picPath = itBegin->picPath;
			m_picInfo.pos = itBegin->pos;
			m_tmpImglist.push_back(m_picInfo);
		}
	}
	//////将正确的emotion信息转存储到imglist中用于输出//////
	imglist.clear();
	vector<PicPathInfo>::iterator itTmpFirst = m_tmpImglist.begin();
	for (;itTmpFirst != m_tmpImglist.end();itTmpFirst++)
	{
		////存储有效内容//////
		PicPathInfo m_picInfo;
		m_picInfo.index = 0;
		m_picInfo.picPath = itTmpFirst->picPath;
		m_picInfo.pos = itTmpFirst->pos;
		imglist.push_back(m_picInfo);
	}
}

void CTools::GetEmotionLab(std::map<CString, CString>& m_EmotionLab)
{
	m_EmotionLab.clear();
	// 读取表情配置文件(Emotion.ini),存储到map容器
	TCHAR emotionPath[_MAX_PATH];
	memset(emotionPath, 0, _MAX_PATH);
	GetCurrentDirectory(_MAX_PATH, emotionPath);
	CString strEmotionPath(emotionPath);
	strEmotionPath += _T("\\Emotion\\Emotion.ini");
	CString m_strDefaultEmotionPath(emotionPath);
	m_strDefaultEmotionPath += _T("\\Emotion\\");
	for (int i = 0; i <= EMOTION_CUSTOM_MAXCOUNT; ++i)
	{
		CString strTemp(_T(""));
		strTemp.Format(_T("%d"), i + 1);
		TCHAR emotionKey[MAX_PATH] = {0};
		GetPrivateProfileString((LPCTSTR)strTemp, _T("character"), _T(""), emotionKey, MAX_PATH, strEmotionPath);
		TCHAR emotionValue[MAX_PATH] = {0};
		GetPrivateProfileString((LPCTSTR)strTemp, _T("file"), _T(""), emotionValue, MAX_PATH, strEmotionPath);
		CString m_stemoPath(emotionPath);
		m_stemoPath.Append(_T("\\Emotion\\"));
		m_EmotionLab.insert(make_pair<CString, CString>(CString(emotionKey),m_stemoPath + CString(emotionValue)));
	}
}

bool CTools::GetEmotionKey(CString& m_emotionURL,CString& m_emotionKey)
{
	std::map<CString, CString> m_EmotionLab;
	CTools::GetEmotionLab(m_EmotionLab);
	std::map<CString, CString>::iterator itBegin = m_EmotionLab.begin();
	for (;itBegin != m_EmotionLab.end();itBegin++)
	{
		/////查找替换/////
		if (itBegin->second == m_emotionURL)
		{
			m_emotionKey = itBegin->first;
			return true;
		}
	}
	return false;
}
void CTools::MakeIMStyle(MsgToSend& msgTxtPic,map<int,std::string>& m_imageList)
{
	m_imageList.clear();
	vector<PicPathInfo>::iterator itBegin = msgTxtPic.pictures.begin();
	for (;itBegin != msgTxtPic.pictures.end();itBegin++)
	{
		std::string m_emotion = itBegin->picPath;
		CImage Img;
		Img.Load(CTools::UTF2UNICODE(m_emotion));
		int m_ImageH = Img.GetHeight();
		int m_ImageW = Img.GetWidth();
		int m_BeginPos = m_emotion.find("Emotion");
		if (std::string::npos != m_BeginPos)
		{
			////表情类图片处理/////
			std::string m_emotionNUm = m_emotion.substr(m_BeginPos + 8,m_emotion.length() - m_BeginPos -12);
			CString m_str(_T(""));
			m_str.Format(_T("<IMG style=\"WIDTH: %dpx; HEIGHT: %dpx\" src=\"file:///UC.InternalImg//emotion/%d.gif\">"),m_ImageW,m_ImageH,CTools::str2num(m_emotionNUm));
			m_imageList[itBegin->pos] = CTools::UNICODE2UTF(m_str);
		}
	}
}


void CTools::IMPicFormat(MsgToSend& msgTxtPic,vector<PicInfo>& m_picInfo)
{
	////清空记录数据/////
	m_picInfo.clear();
	////图片检索/////
	vector<PicPathInfo>::iterator itBegin = msgTxtPic.pictures.begin();
	for (;itBegin != msgTxtPic.pictures.end();itBegin++)
	{
		PicInfo m_tmpPicInfo;
		std::string m_emotion = itBegin->picPath;
		CImage Img;
		Img.Load(CTools::UTF2UNICODE(m_emotion));
		int m_ImageH = Img.GetHeight();
		int m_ImageW = Img.GetWidth();
		int m_BeginPos = m_emotion.find("Emotion");
		if (std::string::npos != m_BeginPos)
		{
			////表情类图片处理/////
			std::string m_emotionNUm = m_emotion.substr(m_BeginPos + 8,m_emotion.length() - m_BeginPos -12);
			CString m_str(_T(""));
			m_str.Format(_T("&lt;IMG style=&quot;WIDTH: %dpx; HEIGHT: %dpx&quot; border=0 hspace=0 src=&quot;file:///UC.InternalImg//emotion/%d.gif&quot;&gt;"),m_ImageW,m_ImageH,CTools::str2num(m_emotionNUm));
			CString m_strUnRAR(_T(""));
			m_strUnRAR.Format(_T("<IMG style=\"WIDTH: %dpx; HEIGHT: %dpx\" src=\"file:///UC.InternalImg//emotion/%d.gif\">"),m_ImageW,m_ImageH,CTools::str2num(m_emotionNUm));
			m_tmpPicInfo.m_picStyle =  CTools::UNICODE2UTF(m_str);
			m_tmpPicInfo.m_picURARStyle = CTools::UNICODE2UTF(m_strUnRAR);
			m_tmpPicInfo.picIndex = itBegin->pos;
			m_tmpPicInfo.m_picfullPath = itBegin->picPath;
			CString emotiomKey(_T(""));
			if (GetEmotionKey(CTools::UTF2UNICODE(itBegin->picPath),emotiomKey))
			{
				m_tmpPicInfo.m_picKey = CTools::UNICODE2UTF(emotiomKey);
			}
			else
			{
				m_tmpPicInfo.m_picKey = "";
			}
		}
		else
		{
			/////截图信息处理/////
			CString m_picName = CTools::UTF2UNICODE(m_emotion);
			m_picName = CTools::GetFileName(m_picName,TRUE);
			CString m_str(_T(""));
			m_str.Format(_T("<IMG style=\"BORDER-BOTTOM: #cccccc 1px solid; BORDER-LEFT: #cccccc 1px solid; WIDTH: %dpx; HEIGHT: %dpx; BORDER-TOP: #cccccc 1px solid; BORDER-RIGHT: #cccccc 1px solid\" "),m_ImageW,m_ImageH);
			m_str = m_str + __T("id='") + m_picName + _T("\"\' ") + _T("onmouseup=ShowImageMenu(this) ondblclick=ShowImage(this) src=\"file:///UC.ExternalImg//temp/") + m_picName + _T("\">");
			m_tmpPicInfo.m_picStyle = ("");
			m_tmpPicInfo.m_picURARStyle = CTools::UNICODE2UTF(m_str);
			m_tmpPicInfo.picIndex = itBegin->pos;
			m_tmpPicInfo.m_picfullPath = itBegin->picPath;
		}
		m_picInfo.push_back(m_tmpPicInfo);
		Img.Destroy();
	}
}

void CTools::ConvertSpecialTag(MsgToSend& msgTxtPic,vector<TagInfo>& m_tagInfo)
{
	/////检查特殊符号并转义掉/////
	CString m_strConent = CTools::UTF2UNICODE(msgTxtPic.txtMsg);
	for (int i = 0;i < m_strConent.GetLength();i++)
	{
		CString myStr;
		TagInfo m_tmpInfo;
		myStr = m_strConent.GetAt(i);
		if (_T("&") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&amp;");
			m_tmpInfo.TagIndex = i;
		}else if (_T("<") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&lt;");
			m_tmpInfo.TagIndex = i;
		}else if (_T(">") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&gt;");
			m_tmpInfo.TagIndex = i;
		}else if (_T("\'") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&apos;");
			m_tmpInfo.TagIndex = i;
		}else if (_T("\"") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&quot;");
			m_tmpInfo.TagIndex = i;
		}else if (_T(" ") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&nbsp;");
			m_tmpInfo.TagIndex = i;
		}else if (_T("\r\n") == myStr)
		{
			m_tmpInfo.m_content = myStr;
			m_tmpInfo.m_Converttype = _T("&lt;BR&gt;");
			m_tmpInfo.TagIndex = i;
		}
		else
			continue;
		m_tagInfo.push_back(m_tmpInfo);
	}
}

std::string CTools::MakeUncomMessage(FontInfo& m_font,MsgToSend& msgTxtPic)
{
	CString m_frontStyle;
	m_frontStyle.Format(_T("&lt;imbody&gt;\n    &lt;imagelist/&gt;\n    &lt;html&gt;&lt;![CDATA[&lt;FONT style=&apos;font-size:%dpx&apos;face=&apos;%s&apos; color=&apos;%2x%2x%2x&apos;&gt;"),m_font.m_size,m_font.face.GetBuffer(),GetRValue(m_font.m_rgb),GetGValue(m_font.m_rgb),GetBValue(m_font.m_rgb));
	vector<PicInfo> m_picInfo;   ///将图片格式化/////
	CTools::IMPicFormat(msgTxtPic,m_picInfo);
	vector<TagInfo> m_tagInfo;
	CTools::ConvertSpecialTag(msgTxtPic,m_tagInfo);
	////1. 组装html信息/////
	map<int ,CString> m_ForHtml;
	map<int ,CString> m_ForContent;
	vector<TagInfo>::iterator itTagBegin = m_tagInfo.begin();
	for (;itTagBegin != m_tagInfo.end();itTagBegin++)
	{
		m_ForHtml[itTagBegin->TagIndex] = itTagBegin->m_Converttype;
		m_ForContent[itTagBegin->TagIndex] = itTagBegin->m_Converttype;
	}
	vector<PicInfo>::iterator itPicBegin = m_picInfo.begin();
	for (;itPicBegin != m_picInfo.end();itPicBegin++)
	{
		m_ForHtml[itPicBegin->picIndex] = CTools::UTF2UNICODE(itPicBegin->m_picStyle);
		m_ForContent[itPicBegin->picIndex] = CTools::UTF2UNICODE(itPicBegin->m_picKey);
	}
	CString m_html = CTools::UTF2UNICODE(msgTxtPic.txtMsg);
	CString m_content = m_html; 
	bool m_IsConv = false;   ////标记是否存在转义字符/////
	for (int i = m_html.GetLength();i >= 0;i--)
	{
		CString m_strtmp = m_ForHtml[i];
		////1.处理HTML
		if (!m_strtmp.IsEmpty())
		{
			////图片还是特殊标记////
			if (m_strtmp.GetLength()> 10 )
			{
				/////表情图片////
				m_html = m_html.Left(i) + m_strtmp + m_html.Right(m_html.GetLength() - i);
			}
			else
			{
				/////特殊转义符号////
				m_html = m_html.Left(i) + m_strtmp + m_html.Right(m_html.GetLength() - i -1);

			}
		}
		////2.处理Content////
		m_strtmp = m_ForContent[i];
		if (!m_strtmp.IsEmpty())
		{
			if ( -1 != m_strtmp.Find(_T("/")))
			{
				////表情图片////
				m_content = m_content.Left(i) + m_strtmp+ m_content.Right(m_content.GetLength() - i);
			}
			else
			{
				///特殊转义符号////
				m_IsConv = true;
				m_content = m_content.Left(i) + m_strtmp + m_content.Right(m_content.GetLength() - i -1);
			}
		}

	}
	if (m_IsConv)    ////增加存在转义字符标记/////
	{
		m_content = _T("&lt;![CDATA[") + m_content + _T("]]&gt;");
	}
	////组装消息////
	CString m_Message2Send;
	m_Message2Send = _T("<r><n>d3BjMDM=</n><g>0</g><c>") + m_frontStyle + m_html +_T("&lt;/FONT&gt;]]&gt;&lt;/html&gt;\n    &lt;content&gt;") + m_content +  _T("&lt;/content&gt;\n&lt;/imbody&gt;") + _T("</c></r>");
	return CTools::UNICODE2UTF(m_Message2Send);
}
std::string CTools::MakeRARMessage(FontInfo& m_font,MsgToSend& msgTxtPic)
{
	CString m_frontStyle;
	m_frontStyle.Format(_T("<imbody><imagelist/><html><![CDATA[<FONT style='font-size:%dpx' face='%s' color='%x%x%x'>"),m_font.m_size,m_font.face.GetBuffer(),GetRValue(m_font.m_rgb),GetGValue(m_font.m_rgb),GetBValue(m_font.m_rgb));
	vector<PicInfo> m_picInfo;   ///将图片格式化/////
	CTools::IMPicFormat(msgTxtPic,m_picInfo);

	////1. 组装html信息/////
	map<int ,CString> m_ForHtml;
	map<int ,CString> m_ForContent;
	vector<PicInfo>::iterator itPicBegin = m_picInfo.begin();
	for (;itPicBegin != m_picInfo.end();itPicBegin++)
	{
		m_ForHtml[itPicBegin->picIndex] = CTools::UTF2UNICODE(itPicBegin->m_picURARStyle);
		m_ForContent[itPicBegin->picIndex] = CTools::UTF2UNICODE(itPicBegin->m_picKey);
	}
	CString m_html = CTools::UTF2UNICODE(msgTxtPic.txtMsg);
	CString m_content = m_html; 
	for (int i = m_html.GetLength();i >= 0;i--)
	{
		CString m_strtmp = m_ForHtml[i];
		////1.处理HTML
		if (!m_strtmp.IsEmpty())
		{
			/////表情图片////
			m_html = m_html.Left(i) + m_strtmp + m_html.Right(m_html.GetLength() - i);

		}
		////2.处理Content////
		m_strtmp = m_ForContent[i];
		if (!m_strtmp.IsEmpty())
		{

			////表情图片////
			m_content = m_content.Left(i) + m_strtmp + m_strtmp.Right(m_content.GetLength() - i);
		}
	}
	////组装消息////
	CString m_Message2Send;
	m_Message2Send = m_frontStyle + m_html +_T("</FONT>]]></html><content>") + m_content +  _T("</content></imbody>");
	return CTools::UNICODE2UTF(m_Message2Send);
}

std::string CTools::MakePicTxtMessage(PICUMInfo& m_UMinfo,FontInfo& m_font,MsgToSend& msgTxtPic)
{
	CString m_Content2Send(_T(""));
	m_Content2Send = _T("<imbody>\n    <imagelist>\n        <img>\n            <imgname>") + CTools::GetFileName(m_UMinfo.m_strLocalPath, TRUE) + _T("</imgname>\n            <imgdata __type__=\"url\">") + m_UMinfo.UMURL + _T("</imgdata>\n        </img>\n    </imagelist>\n    <html>");

	CString m_frontStyle;
	m_frontStyle.Format(_T("<![CDATA[<FONT style='font-size:%dpx' face='%s' color='%2x%2x%2x'>"),m_font.m_size,m_font.face.GetBuffer(),GetRValue(m_font.m_rgb),GetGValue(m_font.m_rgb),GetBValue(m_font.m_rgb));
	m_Content2Send = m_Content2Send + m_frontStyle;

	////处理本地表情等信息/////
	vector<PicInfo> m_picInfo;   ///将图片格式化/////
	CTools::IMPicFormat(msgTxtPic,m_picInfo);
	std::string _content = MakeMixedIMContent(m_UMinfo.m_strLocalPath);
	CString m_strContent = CTools::UTF2UNICODE(_content);
	m_strContent.Replace(m_UMinfo.m_strLocalPath,m_UMinfo.UMURL);
	_content = CTools::UNICODE2UTF(m_strContent);

	////1. 组装html信息/////
	map<int ,CString> m_ForHtml;
	map<int ,CString> m_ForContent;
	vector<PicInfo>::iterator itPicBegin = m_picInfo.begin();
	for (;itPicBegin != m_picInfo.end();itPicBegin++)
	{
		/*CString m_strtmpURL = itPicBegin->m_picURARStyle*/
		m_ForHtml[itPicBegin->picIndex] = CTools::UTF2UNICODE(itPicBegin->m_picURARStyle);
		////判断是不是截图信息/////
		if(!itPicBegin->m_picStyle.empty())
		{
			m_ForContent[itPicBegin->picIndex] = CTools::UTF2UNICODE(itPicBegin->m_picKey);
		}
		else
		{
			m_ForContent[itPicBegin->picIndex] = CTools::UTF2UNICODE(_content);


		}
	}
	CString m_html = CTools::UTF2UNICODE(msgTxtPic.txtMsg);
	CString m_content = m_html; 
	for (int i = m_html.GetLength();i >= 0;i--)
	{
		CString m_strtmp = m_ForHtml[i];
		////1.处理HTML
		if (!m_strtmp.IsEmpty())
		{
			/////表情图片////
			m_html = m_html.Left(i) + m_strtmp + m_html.Right(m_html.GetLength() - i);

		}
		////2.处理Content////
		m_strtmp = m_ForContent[i];
		if (!m_strtmp.IsEmpty())
		{

			////表情图片////
			m_content = m_content.Left(i) + m_strtmp + m_content.Right(m_content.GetLength() - i -1);
		}
	}
	////组装消息////
	m_Content2Send = m_Content2Send + m_html +_T("</FONT>]]></html>\n    <content>") + m_content +  _T("</content>\n</imbody>");
	return CTools::UNICODE2UTF(m_Content2Send);
}

CSize CTools::GetImageSize(const int imgHeight, const int imgWidth)
{
	CSize finalSize(imgWidth, imgHeight);
	BOOL bResult = FALSE;

	double perVal = 1.0;

	// 计算图片长宽与最大长宽的比
	int iHeight = (imgHeight / MAX_IMAGE_HEIGHT);
	int iWidth = (imgWidth / MAX_IMAGE_WIDTH);

	// 如果长或者宽超过最大值，则等比缩放
	if (iHeight > 0 || iWidth > 0)
	{
		double perHeight = (imgHeight * 1.0) / MAX_IMAGE_HEIGHT;
		double perWidth = (imgWidth * 1.0) / MAX_IMAGE_WIDTH;

		int perce = 100;
		perVal = (iHeight > iWidth) ? perHeight : perWidth;// 以大比例的为准
		bResult = TRUE;

		finalSize.cx = 100;// 宽度是默认窗口的100%
		if (perHeight > 1)
		{
			int newWidth = MAX_IMAGE_HEIGHT * imgWidth / imgHeight;
			perce = newWidth * 100 / MAX_IMAGE_WIDTH;
		}

		finalSize.cx = (perce > 100) ? 100 : perce;
		finalSize.cy = (int)(finalSize.cy / perVal);
		return finalSize;
	}
	finalSize.cx = (int)(finalSize.cx / perVal);
	finalSize.cy = (int)(finalSize.cy / perVal);

	return finalSize;
}