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

#pragma once
#include <string>
#include <vector>
#include <list>
#include <iosfwd>

#ifdef WIN32
#include <tchar.h>
#include <time.h>
#include <atltime.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Iphlpapi.h"
#endif

#include <string>
#include <vector>
typedef struct  
{
	int m_Pos;    ////�ò���ͼ�Ļ�Ϸ���ʱ��Ҫ�ã�һ��PC��ʹ��/////
	std::string umFileUrl;
	std::string umFileType;
	std::string umFileSize;
	std::string umFileName;
	std::string umFileDuration;
	std::string umTransCode;
	std::string umExtraParam;
}UMINFo;  ////UM��Ϣ�ṹ��///
struct FontInfo
{
	int         m_size;  /////��λ��PX//////
	COLORREF    m_rgb ;  /////������ɫ/////
	CString     face;    //////���������/////
	bool        m_isI;   ////�Ƿ�б��////
	bool        m_isB;   ////�Ƿ�Ӵ�////
	bool        m_isU;   ////�Ƿ��»���////
	FontInfo()
	{
		m_isI = false;
		m_isB = false;
		m_isU = false;
	}
};///////������Ϣ�ṹ��///
typedef struct  
{
	FontInfo m_font;
	CString Content;
	UMINFo  m_uminfo;
}IMINfo; ////������Ϣ�ṹ��///


struct PicPathInfo
{
	int index;      ///////�ؼ���ȡͼƬ��Ϣʱʹ��/////
	int pos;        ///////ͼƬ���ı��е�λ��////////
	std::string picPath;   /////ͼƬ�ı��ص�ַ//////
}; ////ͼƬ���///

struct MsgToSend
{
	std::string txtMsg;
	vector<PicPathInfo> pictures;
	MsgToSend()
	{
		txtMsg="";
	}
};///////������Ϣ�ṹ��////

struct PicInfo
{
	std::string m_picKey;             //////ת����/:D�Ȳ�ѯ///
	std::string m_picStyle;            /////UM��ַת����ѹ�����<IMG style="" src="">��ʽ///
	std::string m_picURARStyle;        /////UM��ַת����δѹ����<IMG style="" src="">��ʽ///
	std::string m_picfullPath;        ////���ص�ַ////
	int picIndex;                     ////�ı��е�λ��///
};///////������Ϣ�ṹ��///

struct TagInfo
{
	CString m_content;             //////�������///
	CString m_Converttype;         /////ƬUM��ַת����ѹ����ĸ�ʽ///
	int TagIndex;                      ////�ı��е�λ��///
};///////������Ϣ�ṹ��///

struct PICUMInfo
{
	CString      UMURL;
	CString      UMID;
	CString      m_strLocalPath;
};///////ͼƬ�ϴ�UM�����Ϣ/////

const int EMOTION_CUSTOM_MAXCOUNT  = 90;   // ���������������///

const int STRING_LENGTH = 100;//���ж����ַ����̶�����
extern "C"
{
	int WINAPI MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
	int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
};
#ifdef UNICODE
#define MessageBoxTimeout MessageBoxTimeoutW
#else
#define MessageBoxTimeout MessageBoxTimeoutA
#endif 

class CTools
{
private:
	CTools(void);
	~CTools(void);
public:
	static CString ANSI2UNICODE(std::string& strUtf8);
	static CString UTF2UNICODE(const std::string& str);
	static std::wstring string2wstring(const std::string& str);
	static std::string UNICODE2UTF(const CString& cstr);
	static void CString2Char(const CString &str,char* ch,unsigned int lenth);
	static void string2CString(const std::string&,CString&);
	static TUP_INT64 GetCurUTCTime();
	static CString FormatUTCTime(TUP_INT64&);
	static CString getCurrentPath();//Modified by w00321336 to fix some unreasonable code at 2015-1-21
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);
	static void GetUserDefineImage(TUP_CHAR* id,TUP_CHAR* data,TUP_UINT32 length,CString& fileiamge);
	static std::string num2str(int);
	static int str2num(const std::string& str);
	static bool GetBestHostip(std::string& ip, const std::string& serverip);
	static void ShowMessageTimeout(LPCTSTR msg,DWORD delay);
	static void ReplaceParagraphTag(std::string& str);
	static void ReplaceSpecialTag(std::string& str);
	static void ReplaceToXMLString(std::string& str, std::string strXML, const std::string& strReplace);

	static std::string MakeMixedIMContent(CString& imgPath);
	static CString GetFileName(const CString & fileFullPath, BOOL bHasExt);
	static ULONGLONG GetFileSize(const CString & filePath);
	////��IMContent�л�ȡ�ı�������&ͼƬ,��������ֵΪtrue��ʾPC����Ϣ�������ʾ�ƶ�����Ϣ//////
	static bool GetIMFromContent(CString &INcontent,IMINfo& m_IMinfo,vector<PicPathInfo>& m_ImageList);
	static void AnalysePCMessage(vector<PicPathInfo>& imglist);                        /////��PC�˵ı��飬ͼƬ��ַ���ɱ��ؾ��Ե�ַ/////
	static void GetEmotionLab(std::map<CString, CString>& m_EmotionLab);
	////////����IM��Ϣ����/////
	static bool GetEmotionKey(CString& m_emotionURL,CString& m_emotionKey);            ////�����ر���ͼƬת�ɳ�ת����/:D�Ȳ�ѯ����ʽ/////
	static void MakeIMStyle(MsgToSend& msgTxtPic,map<int,std::string>& m_imageList);   ////��ͼƬUM��ַת����<IMG style="" src="">��ʽ���
	static void IMPicFormat(MsgToSend& msgTxtPic,vector<PicInfo>& m_picInfo);
	static void ConvertSpecialTag(MsgToSend& msgTxtPic,vector<TagInfo>& m_tagInfo);
	static std::string MakeUncomMessage(FontInfo& m_font,MsgToSend& msgTxtPic);
	static std::string MakeRARMessage(FontInfo& m_font,MsgToSend& msgTxtPic);   ////������ͼ��Ϣ��ͼ�Ļ�ϣ��ı�+���飩
	static std::string MakePicTxtMessage(PICUMInfo& m_UMinfo,FontInfo& m_font,MsgToSend& msgTxtPic);   ////������ͼ��Ϣ��ͼ�Ļ�ϣ��ı�+���飩
	static CSize GetImageSize(const int imgHeight, const int imgWidth);
};



