/* 
Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "stdafx.h"
#include "IMMSGDemo.h"
#include "IMMSGDemoDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include "NotifyCallBack.h"

#include <afxole.h>
#include <RichOle.h>
#include <utility>
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CAPTURE_TIME = 10001;	 // 间隔时间30秒
const int HEARTBEAT_TIME = 30000;	 // 间隔时间30秒
const int HEART_BEAT_TIMEID = 1000;	 // 心跳定时器ID
#define IM_CONT_EXTIMG_SYMBOL           _T("file:///UC.ExternalImg//temp/")
static const TUP_UINT64 def_max_offline_size = 3 * 1024u * 1024u * 1024u;

template<typename T>
void NEW_NULL_MEMORY_TPL(T*& t,UINT len)
{
	if(len > 1)
	{
		t = new T[len];
		memset( t, 0, sizeof(T) * len );
	}
}


UINT ThreadFun(LPVOID pParam){  //线程要调用的函数

	if (NULL == pParam)
	{
		return 0;
	}
	Sleep(3000);
	CIMMSGDemoDlg* instance = (CIMMSGDemoDlg*)pParam;
	return 0;

}

//************************************************************************
// BOOL CIMMSGDemoDlg::m_bIsOfflineMsg = FALSE;
//************************************************************************
CIMMSGDemoDlg::CIMMSGDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIMMSGDemoDlg::IDD, pParent)
	, m_bLoginFlag(FALSE)
	, m_strEmotionPath("")
	, m_strDefaultEmotionPath("")
	, m_bLogOff(FALSE)
	, m_downloadImagePath(_T(""))
	, m_cstrOppositeAccount(_T(""))
	, m_UtcStamp(0)
	,m_ImagePosition(0)
	,m_strScrathURI("")      //////截图URL////
    ,m_strContent("")      //////生成消息结构体中Content内容/////
    ,m_strHTML("")        ///////组装生成消息结构体的HTML字段内容/////
{
	memset(&m_LoginInfo, 0, sizeof(OFFLINE_LOGININFO));
	memset(&m_UserInfo, 0, sizeof(OFFLINE_USERINFO));
	memset(OriginAccount, 0, IM_D_MAX_ACCOUNT_LENGTH);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CIMMSGDemoDlg::~CIMMSGDemoDlg()
{	
	SAFE_DELETEARRY(m_UserInfo.pcDeviceType);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceName);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceOS);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceSN);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceVersion);
	SAFE_DELETEARRY(m_LoginInfo.pcLocalIP);
}
//************************************************************************
void CIMMSGDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_ipAddress);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_PSD, m_editPSD);
	DDX_Control(pDX, IDC_EDIT_OPPSITE_ACCOUNT, m_editOppsiteAccount);
	DDX_Control(pDX, IDC_BUTTON_SEND_MSG, m_btnSendMSG);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_stcInputStatic);
	DDX_Control(pDX, IDC_BUTTON_SCREENCATCH, m_btnScreenCatch);
	DDX_Control(pDX, IDC_BUTTON_EMOTION, m_btnEmotion);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_BUTTON_LOGOFF, m_btnLogoff);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_EDIT_SEND_MSG, m_editSendMSG);
	DDX_Control(pDX, IDC_BUTTON_SEND_CATCH, m_btnSendScreenCatch);
	DDX_Control(pDX, IDC_BUTTON1, m_sendPic);
	DDX_Control(pDX, IDC_RICHEDIT21, m_editRecvMSG);
}
//************************************************************************
BEGIN_MESSAGE_MAP(CIMMSGDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CIMMSGDemoDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOFF, &CIMMSGDemoDlg::OnBnClickedButtonLogoff)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CIMMSGDemoDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND_MSG, &CIMMSGDemoDlg::OnBnClickedButtonSendMsg)
	ON_WM_TIMER()
	ON_MESSAGE(WM_RECV_IM, &CIMMSGDemoDlg::OnRecvIM)
	ON_MESSAGE(WM_RECV_OFFLINE_IM, &CIMMSGDemoDlg::OnRecvOfflineIM)
	ON_MESSAGE(WM_INPUT_STATUS, &CIMMSGDemoDlg::OnInputStatus)
	ON_MESSAGE(WM_USER_KICKOUT, &CIMMSGDemoDlg::OnKickOutUser)
	ON_MESSAGE(WM_SHOW_DOWNLOADIMAGE, &CIMMSGDemoDlg::OnShowDownloadImage)
	ON_MESSAGE(WM_SEND_IMAGEINFO, &CIMMSGDemoDlg::OnSendImageInfo)
	ON_EN_KILLFOCUS(IDC_EDIT_SEND_MSG, &CIMMSGDemoDlg::OnKillfocusEditMsg)
	ON_EN_SETFOCUS(IDC_EDIT_SEND_MSG, &CIMMSGDemoDlg::OnSetfocusEditMsg)
	ON_BN_CLICKED(IDC_BUTTON_SCREENCATCH, &CIMMSGDemoDlg::OnBnClickedButtonScreencatch)
	ON_BN_CLICKED(IDC_BUTTON_EMOTION, &CIMMSGDemoDlg::OnBnClickedButtonEmotion)
	ON_EN_KILLFOCUS(IDC_EDIT_OPPSITE_ACCOUNT, &CIMMSGDemoDlg::OnEnKillfocusEditOppsiteAccount)
	ON_BN_CLICKED(IDC_BUTTON_SEND_CATCH, &CIMMSGDemoDlg::OnBnClickedButtonSendCatch)
	ON_BN_CLICKED(IDC_BUTTON1, &CIMMSGDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CIMMSGDemoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()
//************************************************************************
// CIMMSGDemoDlg message handlers
//************************************************************************
void CIMMSGDemoDlg::ComMsgFormat(CString& cotent, CString& sendContent)
{
	sendContent = _T("<r><g>1</g><c>");
	CString cstrTemp = _T("<imbody><imagelist/><html><![CDATA[<FONT style='font-size:14px'>");
	cstrTemp += cotent;
	cstrTemp.Replace(_T("\r\n"), _T("<BR>"));
	cstrTemp += _T("</FONT>]]></html><content>");
	cstrTemp += cotent;
	cstrTemp += _T("</content></imbody>");

	std::string strTmpContent = CTools::UNICODE2UTF(cstrTemp);
	int nLength = strTmpContent.length();
	// 压缩
	TUP_UCHAR *ack = NULL;
	tup_im_gzlib_comp(strTmpContent.c_str(), &ack, (TUP_INT*)&nLength);

	// 编码n
	nLength = strTmpContent.length();
	TUP_CHAR *pEncode = new TUP_CHAR[sizeof(TUP_CHAR) * (nLength + 1)];
	memcpy(pEncode,strTmpContent.c_str(),nLength);
	pEncode[nLength] = '\0';
	tup_im_base64_encode(ack, pEncode, (TUP_UINT*)&nLength);
	std::string strTemp(pEncode);
	cstrTemp = CTools::UTF2UNICODE(strTemp);
	sendContent += cstrTemp;
	sendContent += _T("</c></r>");
	SAFE_DELETEARRY(pEncode);
	tup_im_release_tup_mem(ack);
	ack = NULL;
}
void CIMMSGDemoDlg::ComCodeMsg(std::string& m_strSource, std::string& m_strTarget)
{
	CString tmpMsg = CTools::UTF2UNICODE(m_strSource);
	tmpMsg.Replace(_T("\r\n"), _T("<BR>"));
	std::string strTmpContent = CTools::UNICODE2UTF(tmpMsg);
	int nLength = strTmpContent.length();
	// 压缩
	TUP_UCHAR *ack = NULL;
	TUP_INT nMsgLength = strTmpContent.length();
	tup_im_gzlib_comp(strTmpContent.c_str(), &ack, &nMsgLength);

	// 编码n
	TUP_UINT nLen = (TUP_UINT)(nMsgLength);
	TUP_CHAR *pEncode = new TUP_CHAR[sizeof(TUP_CHAR) * (nLength + 1)];
	memcpy(pEncode, strTmpContent.c_str(), nLength);
	pEncode[nLength] = '\0';
	tup_im_base64_encode(ack, pEncode, &nLen);
	m_strTarget = pEncode;
	SAFE_DELETEARRY(pEncode);
	tup_im_release_tup_mem(ack);
	ack = NULL;
	m_strTarget = "<r><g>1</g><c>" + m_strTarget + "</c></r>";
}
//************************************************************************
void CIMMSGDemoDlg::DisableLoginRelativeControls()
{
	m_editAccount.EnableWindow(FALSE);
	m_editPSD.EnableWindow(FALSE);
	m_ipAddress.EnableWindow(FALSE);
	m_editPort.EnableWindow(FALSE);
	m_btnLogin.EnableWindow(FALSE);
	m_btnLogoff.EnableWindow(TRUE);
	m_btnSendMSG.EnableWindow(TRUE);
	m_btnScreenCatch.EnableWindow(TRUE);
//	m_sendPic.EnableWindow(TRUE);
	m_btnEmotion.EnableWindow(TRUE);
	m_editOppsiteAccount.EnableWindow(TRUE);
}
//************************************************************************
void CIMMSGDemoDlg::EnableLoginRelativeControls()
{
	m_editAccount.EnableWindow(TRUE);
	m_editPSD.EnableWindow(TRUE);
	m_ipAddress.EnableWindow(TRUE);
	m_editPort.EnableWindow(TRUE);
	m_btnLogin.EnableWindow(TRUE);
	m_btnLogoff.EnableWindow(FALSE);
	m_btnSendMSG.EnableWindow(FALSE);
	m_btnScreenCatch.EnableWindow(FALSE);
	m_sendPic.EnableWindow(FALSE);
	m_btnEmotion.EnableWindow(FALSE);
	m_editOppsiteAccount.EnableWindow(FALSE);
	m_btnSendScreenCatch.EnableWindow(FALSE);
}
//*************************************************************
BOOL CIMMSGDemoDlg::GetDeviceInfo (std::string& sys, std::string& ver, std::string& sn)
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	OSVERSIONINFOEX os;
	CString strSystemVersion;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{

		switch(os.dwMajorVersion)//判断主版本号
		{
		case 4:
			switch(os.dwMinorVersion)//判断次版本号
			{
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
				{
					strSystemVersion=_T("Microsoft Windows NT 4.0");
				}
				else if (os.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
				{
					strSystemVersion=_T("Microsoft Windows 95");
				}
				break;
			case 10:
				strSystemVersion=_T("Microsoft Windows 98");
				break;
			case 90:
				strSystemVersion=_T("Microsoft Windows Me");
				break;
			default:
				break;
			}
			break;

		case 5:
			switch(os.dwMinorVersion)
			{
			case 0:
				strSystemVersion=_T("Microsoft Windows 2000");
				break;
			case 1:
				strSystemVersion=_T("Microsoft Windows XP");
				break;
			case 2:
				if(os.wProductType==VER_NT_WORKSTATION && 
					info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
				{
					strSystemVersion=_T("Microsoft Windows XP Professional x64 Edition");
				}
				else
				{
					strSystemVersion=_T("Microsoft Windows Server 2003");
				}
				break;
			default:
				break;
			}
			break;

		case 6:
			switch(os.dwMinorVersion)
			{
			case 0:
				if(os.wProductType==VER_NT_WORKSTATION)
				{
					strSystemVersion=_T("Microsoft Windows Vista");
				}
				else
				{
					strSystemVersion=_T("Microsoft Windows Server 2008");
				}
				break;
			case 1:
				if(os.wProductType==VER_NT_WORKSTATION)
				{
					strSystemVersion=_T("Microsoft Windows 7");
				}
				else
				{
					strSystemVersion=_T("Microsoft Windows Server 2008 R2");
				}
				break;
			case 2:
				strSystemVersion=_T("Microsoft Windows 8");
				break;
			default:
				break;
			}
			break;
		default:
			strSystemVersion=_T("UnKown System");
		}

		sys = "PC";
		//ver = ctk::to_utf8str(strSystemVersion.GetString()).get();
		ver = CTools::UNICODE2UTF(strSystemVersion);
		sn = "1.2.3.17";
		return TRUE;
	}
	else
	{
		return FALSE;         
	}
}
//************************************************************************
void CIMMSGDemoDlg::InsertAccountTime(TUP_CHAR account[], TUP_INT64 utcStamp) const
{
	HRESULT hresult = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;

	CString strShowMSG("<br/>");
	strShowMSG += CTools::UTF2UNICODE(account);
	strShowMSG += _T(" ");
	strShowMSG += CTools::FormatUTCTime(utcStamp);
	strShowMSG += CString("<br/>");

	CComBSTR bstrInfo( strShowMSG );
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1); 
	if (sfArray == NULL ) 
		return;
	hresult = SafeArrayAccessData(sfArray,(LPVOID*) & param);
	param->vt = VT_BSTR;
	param->bstrVal = (BSTR)bstrInfo;
	hresult = SafeArrayUnaccessData(sfArray);
	hresult = m_pDocument->write(sfArray);
	if (sfArray != NULL) {
		SafeArrayDestroy(sfArray);
	}
}
//************************************************************************
void CIMMSGDemoDlg::InsertHTMLText(const CString& sendContext) const
{
	if (sendContext.IsEmpty()) return;
	HRESULT hresult = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;

	CComBSTR bstrInfo( sendContext );
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1); 
	if (sfArray == NULL ) 
		return;
	hresult = SafeArrayAccessData(sfArray,(LPVOID*) & param);
	param->vt = VT_BSTR;
	param->bstrVal = (BSTR)bstrInfo;
	hresult = SafeArrayUnaccessData(sfArray);
	hresult = m_pDocument->write(sfArray);
	if (sfArray != NULL) {
		SafeArrayDestroy(sfArray);
	}

	// 设置光标位置
	CEdit *pSendMSG = (CEdit*)GetDlgItem(IDC_EDIT_SEND_MSG);
	pSendMSG->SetFocus();
}

//************************************************************************
void CIMMSGDemoDlg::InsertImage(CString imagePath, UINT width, UINT height, BOOL isImage, const CString& imageid,BOOL bIsPerc) const
{
	m_pDocument->clear();
	CString strHtml;
	strHtml.Format(_T("<img src=%s WIDTH=%dpx HEIGHT=%dpx />"), imagePath.GetString(), width, height);

	HRESULT hresult = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;
	CComBSTR bstrInfo(strHtml);
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1); 
	if (sfArray == NULL ) 
		return;
	hresult = SafeArrayAccessData(sfArray,(LPVOID*) & param);
	param->vt = VT_BSTR;
	param->bstrVal = (BSTR)bstrInfo;
	hresult = SafeArrayUnaccessData(sfArray);
	hresult = m_pDocument->write(sfArray);
	if (sfArray != NULL) {
		SafeArrayDestroy(sfArray);
	}
}
//************************************************************************
void CIMMSGDemoDlg::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	if (m_bLoginFlag)
	{
		// 取消底层模块中未处理的消息处理
		TUP_RESULT tRet = tup_im_setcancelsendingmessage();
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_setcancelsendingmessage failed."));
		}

		// 注销UC服务器的登录
		tRet = tup_im_logout();
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_logout failed."));
		}

		// 关闭上报消息，用户退出登录时调用
		tRet = tup_im_setdispatchmessage(TUP_FALSE);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
		}
	}
	SAFE_DELETEARRY(m_UserInfo.pcDeviceType);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceName);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceOS);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceSN);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceVersion);
	SAFE_DELETEARRY(m_LoginInfo.pcLocalIP);
	::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);// 发送关闭主窗口消息
}
//************************************************************************
void CIMMSGDemoDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	// 获取IP数据
	BYTE field0, field1, field2, field3;
	m_ipAddress.GetAddress(field0, field1, field2, field3);
	char IP[100];
	memset(IP, 0, 100);
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);

	// 获取服务器IP和端口
	CString cstrPort;
	m_editPort.GetWindowText(cstrPort);
	if (cstrPort.IsEmpty())
	{
		AfxMessageBox(_T("port is empty!"));
		return;
	}
	std::string strPort = CTools::UNICODE2UTF(cstrPort);
	int iPort = atoi(strPort.c_str());

	// 设置服务器IP和端口
	TUP_RESULT tRet = tup_im_setserveraddress(IP, iPort);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setserveraddress failed."));
		return;
	}

	// 设置IM回调消息上报函数地址
	tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_register_callback failed."));
		return;
	}

	// 使能消息分发，否则消息不会上报
	tRet = tup_im_setdispatchmessage(TUP_TRUE);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
		return;
	}

	// 获取控件上的登录账号和密码
	CString account;
	CString cstrPSD;
	m_editPSD.GetWindowText(cstrPSD);
	m_editAccount.GetWindowText(account);
	if (account.IsEmpty() || cstrPSD.IsEmpty())
	{
		AfxMessageBox(_T("Account or password is empty!"));
		return;
	}

	IM_S_LOGIN_ARG arg;
	CTools::CString2Char(account, arg.account, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(cstrPSD, arg.password, IM_D_MAX_PASSWORD_LENGTH);

	// 版本号固定
	CString cstrVersion = _T("v1.1.11.103");
	CTools::CString2Char(cstrVersion, arg.version, IM_D_MAX_VERSION_LENGTH);
	arg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;

	// 登录UC服务器
	IM_S_LOGIN_ACK ack;
	tRet = tup_im_login(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		switch (ack.reason)
		{
			// 消息超时
		case IM_E_LOGING_RESULT_TIMEOUT:
			{
				AfxMessageBox(_T("Message timeout!"));
			}
			break;
			// 程序内部错误
		case IM_E_LOGING_RESULT_INTERNAL_ERROR:
			{
				AfxMessageBox(_T("Internal error!"));
			}
			break;
			// 密码错误
		case IM_E_LOGING_RESULT_PASSWORD_ERROR:
			{
				if (0 == ack.retryTimes)
				{
					AfxMessageBox(_T("Password error five times, account is locked!"));
				}
				else
				{
					CString cstrErrorTip;
					cstrErrorTip.Format(_T("Password error, number of attempts remaining: %d"), ack.retryTimes);
					AfxMessageBox(cstrErrorTip);
				}
			}
			break;
			// 账号不存在
		case IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST:
			{
				AfxMessageBox(_T("Account does not exist!"));
			}
			break;
			// 用户已存在
		case IM_E_LOGING_RESULT_ALREADY_LOGIN:
			{
				AfxMessageBox(_T("User already exist!"));
			}
			break;
			// 帐号已锁定
		case IM_E_LOGING_RESULT_ACCOUNT_LOCKED:
			{
				AfxMessageBox(_T("Account has been locked!"));
			}
			break;
			// 需要下载新版本才允许登录
		case IM_E_LOGING_RESULT_NEED_NEW_VERSION:
			{
				AfxMessageBox(_T("Need to download the new version of this to allow login!"));
			}
			break;
			// 用户未激活
		case IM_E_LOGING_RESULT_NOT_ACTIVE:
			{
				AfxMessageBox(_T("User is not activated!"));
			}
			break;
			// 用户账号被暂停
		case IM_E_LOGING_RESULT_ACCOUNT_SUSPEND:
			{
				AfxMessageBox(_T("User account was suspended!"));
			}
			break;
			// 用户账号过期
		case IM_E_LOGING_RESULT_ACCOUNT_EXPIRE:
			{
				AfxMessageBox(_T("User account expired!"));
			}
			break;
			// 消息解密失败
		case IM_E_LOGING_RESULT_DECRYPT_FAILED:
			{
				AfxMessageBox(_T("Message decryption failed!"));
			}
			break;
			// 证书下载失败
		case IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED:
			{
				AfxMessageBox(_T("Certificate download failed!"));
			}
			break;
			// 证书校验失败
		case IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED:
			{
				AfxMessageBox(_T("Certificate validation failed!"));
			}
			break;
			// 域名解析错误
		case IM_E_LOGING_RESULT_DNS_ERROR:
			{
				AfxMessageBox(_T("Domain name resolution error!"));
			}
			break;
		default:break;
		}
		return;
	}
	else
	{
		// UC服务器登录成功
		IM_S_GETSERVICEPROFILEARG serviceArg;
		memset(&serviceArg,0,sizeof(IM_S_GETSERVICEPROFILEARG));
		serviceArg.isSyncAll  = TUP_TRUE;
		serviceArg.needIcon = TUP_TRUE;
		serviceArg.isVpnAccess = TUP_FALSE;
		std::string LocalIPAddr;
		if (!CTools::GetBestHostip(LocalIPAddr,IP))
		{
			return;
		}
		strncpy_s(serviceArg.localIP,IM_D_IP_LENGTH*sizeof(TUP_CHAR),LocalIPAddr.c_str(),_TRUNCATE);
		strncpy_s(serviceArg.timestamp,IM_D_MAX_TIMESTAMP_LENGTH*sizeof(TUP_CHAR),"19000000000000",_TRUNCATE);

		IM_S_SERVICEPROFILEACK serviceAck;
		memset(&serviceAck,0,sizeof(IM_S_SERVICEPROFILEACK));
		tRet = tup_im_getserviceprofile(&serviceArg,&serviceAck);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_im_getserviceprofile failed.");
			return ;
		}
		TUP_CHAR* umServerHttpsList = new TUP_CHAR[UMSERVERLENT+1];
		memset(umServerHttpsList,0,128+1);
		memcpy(umServerHttpsList,serviceAck.umServerHttpsList->data,UMSERVERLENT);

		TUP_CHAR* umServerHttpList = new TUP_CHAR[UMSERVERLENT+1];
		memset(umServerHttpList,0,UMSERVERLENT);
		memcpy(umServerHttpList,serviceAck.umServerHttpList->data,UMSERVERLENT);
       TUP_ULONG loginRes = 0L;
		SetOffLineLoginInfo(m_LoginInfo,umServerHttpsList,umServerHttpList);
		SetOffLineUserInfo(m_UserInfo);	
		tRet = tup_offlinefile_login(&m_LoginInfo, &m_UserInfo, &loginRes);
		if (tRet != TUP_SUCCESS)
		{
			AfxMessageBox(_T("tup_offlinefile_login failed!"));
			return;
		}		

		// 		m_bLogOff = FALSE;// 注销按钮为未按下状态
		m_bLoginFlag = TRUE;// 登录成功
		m_editAccount.GetWindowText(m_cstrLoginAccount);
		g_Account = CTools::UNICODE2UTF(account);
		DisableLoginRelativeControls();// 禁用登录相关控件

		IM_S_GETUSERINFOARG argSend;
		CTools::CString2Char(m_cstrLoginAccount, argSend.account, IM_D_MAX_ACCOUNT_LENGTH);
		// 精确查找发送方用户的信息
		TUP_RESULT tRet = tup_im_getuserinfo(&argSend, &m_sendUserInfo);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("The account does not exist!"));
			return;
		}

		m_SendImArg.chatType = IM_E_IM_CHAT_TYPE_SINGLE;
		m_SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
		memcpy(m_SendImArg.origin, m_sendUserInfo.account, IM_D_MAX_ACCOUNT_LENGTH);
		m_SendImArg.regionID = 0;

		// 设置心跳定时器
		SetTimer(HEART_BEAT_TIMEID, HEARTBEAT_TIME, NULL);

		//////释放tup_im_getserviceprofile结构体指针/////
		tup_im_release_tup_list(serviceAck.funcIDList);
		tup_im_release_tup_list(serviceAck.configList);
		tup_im_release_tup_list(serviceAck.panelList);
		tup_im_release_tup_list(serviceAck.serverList);
		tup_im_release_tup_list(serviceAck.componentList);
		tup_im_release_tup_list(serviceAck.componentParamList);
		tup_im_release_tup_list(serviceAck.dataConfAddrList);
		tup_im_release_tup_list(serviceAck.umServerHttpList);
		tup_im_release_tup_list(serviceAck.umServerHttpsList);
	}
}
//************************************************************************
void CIMMSGDemoDlg::OnBnClickedButtonLogoff()
{
	// TODO: Add your control notification handler code here
	if (m_bLoginFlag)
	{
		// 按下注销按钮，只退出服务器，不退出对话框
		m_bLogOff = TRUE;

		// 取消底层模块中未处理的消息处理
		TUP_RESULT tRet = tup_im_setcancelsendingmessage();
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_setcancelsendingmessage failed."));
		}

		// 注销UC服务器的登录
		tRet = tup_im_logout();
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_logout failed."));
		}	

		KillTimer(HEART_BEAT_TIMEID);// 删除定时器
		// 启用登录相关控件
		EnableLoginRelativeControls();

		// 设置焦点
		m_btnLogin.SetFocus();
		m_editSendMSG.SetWindowText(_T(""));
		m_stcInputStatic.SetWindowText(_T(""));
		m_editOppsiteAccount.SetWindowText(_T(""));

		// 关闭上报消息，用户退出登录时调用
		if (m_bLoginFlag)
		{
			TUP_RESULT tRet = tup_im_setdispatchmessage(TUP_FALSE);
			if(tRet == TUP_FAIL)
			{
				AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
			}
		}
		if (!m_bLogOff)
		{
			// 按下的是注销按钮，则不发送关闭消息
			::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
		}
		m_bLogOff = FALSE;// 重置为FALSE
	}

	/////释放资源//////
	SAFE_DELETEARRY(m_UserInfo.pcDeviceType);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceName);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceOS);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceSN);
	SAFE_DELETEARRY(m_UserInfo.pcDeviceVersion);
	SAFE_DELETEARRY(m_LoginInfo.pcLocalIP);

}
//************************************************************************
void CIMMSGDemoDlg::OnBnClickedButtonSendMsg()
{
	// TODO: Add your control notification handler code here
	// 获取接收方账户
	CString		recvAccount;
	m_editOppsiteAccount.GetWindowText(recvAccount);

	IM_S_GETUSERINFOARG argRecv;
	IM_S_USERINFO userInfoRecv;
	CTools::CString2Char(recvAccount, argRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(recvAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);

	// 启用IM输入状态服务
	TUP_RESULT tRet = tup_im_notifyiminputting(&m_statusArg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("Username error,please re-enter!"));
		return;
	}

	//精确查找接收方用户的信息
	tRet = tup_im_getuserinfo(&argRecv, &userInfoRecv);
	if (TUP_FAIL == tRet)
	{
		AfxMessageBox(_T("Username error,please re-enter!"));
		return;
	}
	////精确匹配账户
	if(0 != strcmp(userInfoRecv.account,CTools::UNICODE2UTF(recvAccount).c_str()))
	{
		AfxMessageBox(_T("No Such User"));
		return;
	}

	// 判断消息内容是否为空，为空则返回重新输入
	CString sendMSG;
	m_editSendMSG.GetWindowText(sendMSG);
	// msgShow用来更新聊天内容，sendMSG用来生成发送格式
	CString msgShow = sendMSG;
	CString strSend(_T(""));
	if (sendMSG.IsEmpty())
	{
		AfxMessageBox(_T("Message is empty,please re-enter!"));
		m_editSendMSG.SetFocus();
		return;
	}
	else
	{
		// eSpace发送消息长度如果超出500会进行压缩，而UC没有压缩功能
		// 所以UC消息内容长度控制在500以下，超出500直接返回并进行提示
		int nLength = CTools::UNICODE2UTF(sendMSG).length();
		/* 对标签进行两次转义替换
		sendMsg.Replace(_T("<"), _T("&lt;"));
		sendMsg.Replace(_T(">"), _T("&gt;"));
		sendMsg.Replace(_T("&"), _T("&amp;"));
		效果等同于下面
		*/
		sendMSG.Replace(_T("<"), _T("&amp;lt;"));
		sendMSG.Replace(_T(">"), _T("&amp;gt;"));
		if (nLength <= 500)
		{
			// 未压缩的消息格式
			UnCompMsgFormat(sendMSG, strSend);
		}
		else if (nLength <= 1000)
		{
			// 压缩的消息格式
			ComMsgFormat(sendMSG, strSend);
		}
		else
		{
			AfxMessageBox(_T("Message is too long, please re-enter!"));
			m_editSendMSG.SetWindowText(_T(""));
			m_editSendMSG.SetFocus();
			return;
		}
	}

	// 设置发送消息请求参数
	m_SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
	memcpy(m_SendImArg.target, userInfoRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(strSend, m_SendImArg.content, IM_D_MAX_MESSAGE_LENGTH);
	m_SendImArg.utcStamp = CTools::GetCurUTCTime();

	// 判断信息是否发送给自己
	if (strcmp(m_SendImArg.target, m_SendImArg.origin) == 0)
	{
		AfxMessageBox(_T("The sender and receiver can't be the same!"));
		return;
	}
	// 发送即时消息
	tRet = tup_im_sendim(&m_SendImArg);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_sendim failed."));
		return;
	}
	else
	{
		UpdataChatContent(m_SendImArg.origin, m_SendImArg.utcStamp, msgShow);
		m_editSendMSG.SetWindowText(_T(""));
	}
}
//************************************************************************
BOOL CIMMSGDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//InitUIAndEmotionConfig();
	//::AfxBeginThread(ThreadFun, this); 


	// 初始化登录对话框
	m_ipAddress.SetAddress(172,22,9,42);
	m_editPort.SetWindowTextW(TEXT("8011"));
	m_editAccount.SetWindowTextW(TEXT("chenensheng01"));
	m_editPSD.SetWindowTextW(TEXT("huawei.123"));

	// 限制编辑框输入长度
	m_editAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_editPSD.LimitText(IM_D_MAX_PASSWORD_LENGTH);
	m_editPort.LimitText(10);
	m_editOppsiteAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);

	// 设置焦点在登录按钮上
	m_btnLogin.SetFocus();

	return FALSE;  // return TRUE  unless you set the focus to a control
}
//************************************************************************
LRESULT CIMMSGDemoDlg::OnInputStatus(WPARAM wParam, LPARAM lParam)
{
	IM_S_SENDIMINPUT_NOTIFY *notify  = (IM_S_SENDIMINPUT_NOTIFY *)wParam;
	if(NULL == notify)
	{
		return -1L;
	}

	std::string   showInfo = "";
	switch (notify->status)
	{
	case IM_E_IM_CHAT_STATUS_CHATTING:
		{
			showInfo  = notify->account;
			showInfo += "正在输入";
			/////将字符转换成Unicode字符集，否则界面乱码//////
			m_stcInputStatic.SetWindowText(CTools::UTF2UNICODE(showInfo.c_str()));
		}
		break;
	case IM_E_IM_CHAT_STATUS_STOPPED:
		{
			m_stcInputStatic.SetWindowText(CTools::UTF2UNICODE(showInfo.c_str()));
		}
		break;
	default:break;
	}

	return 0L;
}
//************************************************************************
LRESULT CIMMSGDemoDlg::OnKickOutUser(WPARAM wParam, LPARAM lParam)
{
	// 取消底层模块中未处理的消息处理
	m_editOppsiteAccount.SetWindowText(_T(""));

	TUP_RESULT tRet = tup_im_setcancelsendingmessage();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
		return -1L;
	}

	// 注销UC服务器登录
	tRet = tup_im_logout();
	m_bLogOff = TRUE;// 若不置为TRUE，则被踢下线时会退出对话框
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_logout failed!"));
		return -1L;
	}

	// 删除定时器
	KillTimer(HEART_BEAT_TIMEID);

	// 启动登录相关控件
	EnableLoginRelativeControls();

	// 关闭上报消息，用户退出登录时调用
	if (m_bLoginFlag)
	{
		TUP_RESULT tRet = tup_im_setdispatchmessage(TUP_FALSE);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
		}
	}
	if (!m_bLogOff)
	{
		// 按下的是注销按钮，则不发送关闭消息
		::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
	}
	m_bLogOff = FALSE;// 重置为FALSE

	// 提示用户已被强制下线
	AfxMessageBox(_T("You have been forced offline, please login again!"));

	return 0L;
}
//************************************************************************
void CIMMSGDemoDlg::OnKillfocusEditMsg()
{
	// TODO: Add your control notification handler code here
	// 获取接收方账户
	CString		recvAccount;
	m_editOppsiteAccount.GetWindowText(recvAccount);
	if (recvAccount.IsEmpty()) return;

	// 设置接收方输入状态信息
	CTools::CString2Char(recvAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);
	m_statusArg.type = IM_E_IM_CHAT_STATUS_STOPPED;

	// 启用IM输入状态服务
	TUP_RESULT tRet = tup_im_notifyiminputting(&m_statusArg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_notifyiminputting failed!"));
	}
}
//************************************************************************
LRESULT CIMMSGDemoDlg::OnRecvIM(WPARAM wParam,LPARAM)
{
	IM_S_CODECHAT_NOTIFY *notify  = (IM_S_CODECHAT_NOTIFY *)wParam;
	if(NULL == notify) return -1L;

	// 根据消息类型不同设置已读消息
	IM_S_SETMESSAGEREAD_ARG *arg = new IM_S_SETMESSAGEREAD_ARG;
	IM_S_MESSAGEINFO *argMsgInfo = new IM_S_MESSAGEINFO;

	if (NULL == argMsgInfo) return -1L;
	// 单聊、临时单聊
 	if ((IM_E_IM_CHAT_TYPE_SINGLE == notify->chatInfo.chatType)
		|| (IM_E_IM_CHAT_TYPE_TEMP == notify->chatInfo.chatType))
	{
		argMsgInfo->msgType = IM_E_IM_HISTORYMESSAGEMSG_TYPE_SINGLECHAT;
		memcpy(argMsgInfo->sender, notify->chatInfo.origin, strlen(notify->chatInfo.origin) + 1);
	}
	// 固定群聊、临时群聊、多人会话讨论组
	else if ((IM_E_IM_CHAT_TYPE_FIXEDGROUP == notify->chatInfo.chatType)
		|| (IM_E_IM_CHAT_TYPE_TEMPGROUP == notify->chatInfo.chatType)
		|| (IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP == notify->chatInfo.chatType))
	{
		argMsgInfo->msgType = IM_E_IM_HISTORYMESSAGEMSG_TYPE_GROUPCHAT;
		memcpy(argMsgInfo->sender, notify->chatInfo.groupID, strlen(notify->chatInfo.groupID) + 1);
	}
	// 短信消息和系统广告目前暂不处理
// 	else if()
// 	{
// 
// 	}
	argMsgInfo->msgId = notify->chatInfo.serverChatID;
	TUP_S_LIST *pData = new TUP_S_LIST;
	pData->data = (TUP_VOID *)argMsgInfo;
	pData->next = NULL;
	arg->messageinfo = pData;
	TUP_RESULT tRet = tup_im_setmessageread(arg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setmessageread failed!"));
	}
	SAFE_DELETE(pData);
	SAFE_DELETE(argMsgInfo);
	SAFE_DELETE(arg);

	// 显示发送方账户
	CString m_RecName;
	m_editOppsiteAccount.GetWindowText(m_RecName);
	if (strcmp(CTools::UNICODE2UTF(m_RecName).c_str(),notify->chatInfo.origin) != 0 && m_RecName.GetLength())
	{
		////认为不同的对话/////
		m_editRecvMSG.SetWindowText(_T(""));
	}

	m_editOppsiteAccount.SetWindowText(CString(notify->chatInfo.origin));
	m_UtcStamp = notify->chatInfo.utcStamp;
	strncpy_s(OriginAccount, IM_D_MAX_ACCOUNT_LENGTH * sizeof(TUP_CHAR), notify->chatInfo.origin, _TRUNCATE);

	m_cstrOppositeAccount = CTools::UTF2UNICODE(std::string(notify->chatInfo.origin));

	// 解析收到的eSpace纯文本消息
	string strMSG(notify->chatInfo.content);

	// 处理从eSpace或UC传过来的消息内容（判断是否压缩，是否进行相应解压等操作）
	ProcessCotentFromeSpaceOrUC(strMSG);

	// 将字符串转换为宽字符
	wstring comment = CTools::string2wstring(strMSG);
	CString strComment(comment.c_str());
	
	switch (notify->chatInfo.mediaType)
	{
	case  tagIM_E_IM_CHATMEDIA_TYPE_TEXT:    /*< 纯文本 */
		{
			//////解析IM消息////
			IMINfo m_Iminfo;
			vector<PicPathInfo> m_Imagelist;;
			if(CTools::GetIMFromContent(strComment,m_Iminfo,m_Imagelist))
			{
				/////处理PC端发来的消息/////
				CTools::AnalysePCMessage(m_Imagelist);
			}
			////显示消息//////
			UpdataChatContent(notify->chatInfo.origin,notify->chatInfo.utcStamp,m_Iminfo.Content);
			InsertEmotion(m_Imagelist,m_Iminfo.Content.GetLength());
		}
		break;
	case tagIM_E_IM_CHATMEDIA_TYPE_AUDIO:	 /**< 富媒体 语音 */
		{
			/////暂时不处理语音类消息/////
		}
		break;
	case tagIM_E_IM_CHATMEDIA_TYPE_VIDEO:  /**< 富媒体 视频 */
		{
			/////暂时不处理视频类消息//////

		}break;
	case tagIM_E_IM_CHATMEDIA_TYPE_IMAGE:  /**< 富媒体 图片 */
		{
			//////解析IM消息////
			IMINfo m_Iminfo;
			vector<PicPathInfo> m_Imagelist;
			if(CTools::GetIMFromContent(strComment,m_Iminfo,m_Imagelist))
			{
				/////处理PC端发来的消息/////
				CTools::AnalysePCMessage(m_Imagelist);
			}
			////显示消息//////
			UpdataChatContent(notify->chatInfo.origin,notify->chatInfo.utcStamp,m_Iminfo.Content);
			InsertEmotion(m_Imagelist,m_Iminfo.Content.GetLength());
			////下面显示富媒体消息中的图片//////
			m_ImagePosition = m_Iminfo.Content.GetLength() - m_Iminfo.m_uminfo.m_Pos +1;
			m_downloadImagePath = DownloadImageFromServerce(m_Iminfo.m_uminfo);
			Sleep(300);  ////延时，给予下载图片时间
		}
		break;
	default:
		break;
	} 
	SAFE_DELETE(notify);
	return 0L;
}
//************************************************************************
LRESULT CIMMSGDemoDlg::OnRecvOfflineIM(WPARAM wParam, LPARAM lParam)
{
	/////离线消息需要反向输出，否则会造成消息消息倒序排列///////
	IM_S_CHATLIST_NOTIFY *pOfflineMsg = (IM_S_CHATLIST_NOTIFY*)wParam;
	if(NULL == pOfflineMsg) return -1L;
	TUP_S_LIST *pList = pOfflineMsg->chatList;
	std::vector<IM_S_CODECHAT_NOTIFY> m_OFFLINEMsg;
	while (pList)
	{
		IM_S_CODECHAT_NOTIFY notify ;
		memcpy(&notify,(IM_S_CODECHAT_NOTIFY*)pList->data, sizeof(IM_S_CODECHAT_NOTIFY));
		if (pList->data)
		{
			m_OFFLINEMsg.push_back(notify);
		}
		pList = pList->next;
	}

	int m_size = m_OFFLINEMsg.size();
	for (int i = m_size ;i > 0; i--)
	{
		IM_S_CODECHAT_NOTIFY* m_MsgNOTIFY = new IM_S_CODECHAT_NOTIFY;
		IM_S_CODECHAT_NOTIFY m_Msg = m_OFFLINEMsg[i -1];
		memcpy(m_MsgNOTIFY,&m_Msg, sizeof(IM_S_CODECHAT_NOTIFY));
		::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_RECV_IM, (WPARAM)m_MsgNOTIFY, 0);
		if (tagIM_E_IM_CHATMEDIA_TYPE_TEXT != m_Msg.chatInfo.mediaType)
		{
			Sleep(300); ////延时，等待图片类消息下载/////
		}
	}
	tup_im_release_tup_list(pOfflineMsg->chatList);
	SAFE_DELETE(pOfflineMsg);
	return 0L;
}
//************************************************************************

void CIMMSGDemoDlg::OnSetfocusEditMsg()
{
	// TODO: Add your control notification handler code here
	// 获取接收方账户
	CString		recvAccount;
	m_editOppsiteAccount.GetWindowText(recvAccount);

	// 设置接收方输入状态信息
	CTools::CString2Char(recvAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);
	m_statusArg.type = IM_E_IM_CHAT_STATUS_CHATTING;

	// 启用IM输入状态服务
	TUP_RESULT tRet = tup_im_notifyiminputting(&m_statusArg);
}
//************************************************************************
void CIMMSGDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	// 定时向服务器发送心跳消息
	if (HEART_BEAT_TIMEID == nIDEvent)
	{
		// 启用心跳服务
		TUP_RESULT tRet = tup_im_sendheartbeat();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_sendheartbeat failed."));
		}
	}

	if (CAPTURE_TIME == nIDEvent)
	{
		if (!CTools::IsProcessExistsFromName(_T("CatchScreen.exe")))
		{
			// 将剪切板上的数据保存到本地
			if (IsClipboardFormatAvailable(CF_BITMAP))
			{
				if (OpenClipboard())
				{
					TCHAR path[MAX_PATH];
					SHGetSpecialFolderPath(0, path, CSIDL_APPDATA, 0);
					s_ImagePath = path;
					s_ImagePath += _T("\\");
					//使用当前时间命名
					CString dateStr = _T("");
					CTime curTime = CTime::GetCurrentTime();
					dateStr.Format(_T("%.4d%.2d%.2d%.2d%.2d%.2d"), curTime.GetYear(),curTime.GetMonth(),curTime.GetDay(),curTime.GetHour(),curTime.GetMinute(),curTime.GetSecond());
					s_ImagePath += dateStr;
					s_ImagePath += _T(".png");

					// 保存图片
					CImage image;
					BOOL bRet = FALSE;
					HBITMAP hBitmap = static_cast<HBITMAP>(::GetClipboardData(CF_BITMAP));
					if (hBitmap)
					{
						BITMAP bitmap;
						memset(&bitmap, 0, sizeof(BITMAP));
						int nResult = GetObject(hBitmap, sizeof(BITMAP), &bitmap);
						if (bitmap.bmType == 0 && nResult)
						{
							image.Attach(hBitmap);
							image.Save(s_ImagePath, Gdiplus::ImageFormatPNG);
							CSize imageSize = CTools::GetImageSize (image.GetHeight(), image.GetWidth());
							ResizeImage(imageSize.cx, imageSize.cy);// 调整图片大小
							m_SendImArg.utcStamp = CTools::GetCurUTCTime();
							// 					InsertAccountTime(m_SendImArg.origin, m_SendImArg.utcStamp);
							// 					InsertImage(s_ImagePath, imageSize.cx, imageSize.cy, TRUE, CTools::GetFileName(s_ImagePath, FALSE), TRUE);

							int tempIndex=m_editSendMSG.picIndex++;

							m_editSendMSG.InsertImage(s_ImagePath,tempIndex);

							PicPathInfo pic;
							pic.index= tempIndex;
							pic.picPath=CTools::UNICODE2UTF(s_ImagePath);
							m_editSendMSG.msgTxtPic.pictures.push_back(pic);

						}
					}
					DeleteObject(hBitmap);
					CloseClipboard();
				}
			}

			 KillTimer(CAPTURE_TIME);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
//************************************************************************
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//************************************************************************
void CIMMSGDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//************************************************************************
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
//************************************************************************
HCURSOR CIMMSGDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//************************************************************************
void CIMMSGDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}
//************************************************************************
void CIMMSGDemoDlg::OnBnClickedButtonScreencatch()
{
	// TODO: Add your control notification handler code here
	CString strAccount;
	GetDlgItem(IDC_EDIT_OPPSITE_ACCOUNT)->GetWindowText(strAccount);
	if (strAccount.IsEmpty())
	{
		AfxMessageBox(_T("The receiver account is empty, please enter the account first!"));
		GetDlgItem(IDC_EDIT_OPPSITE_ACCOUNT)->SetFocus();
		return;
	}
	OpenClipboard();
	EmptyClipboard();
	CloseClipboard();
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	BOOL bExists = CTools::IsProcessExistsFromName(_T("CatchScreen.exe"));
	if (!bExists)
	{
		// 启动截图程序
		if (::CreateProcess(_T("CatchScreen.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			::CloseHandle(pi.hProcess);
			::CloseHandle(pi.hThread);
			SetTimer(CAPTURE_TIME,100,NULL);
		}
		else
		{
			AfxMessageBox(_T("Start the screenshot failed!"));
			return;
		}
	}

	GetDlgItem(IDC_BUTTON_SEND_CATCH)->EnableWindow(TRUE);
	

	
}
//************************************************************************
void CIMMSGDemoDlg::OnBnClickedButtonEmotion()
{
	// TODO: Add your control notification handler code here
	// 判断接收方是否为空
	CString strAccount;
	m_editOppsiteAccount.GetWindowText(strAccount);
	if (strAccount.IsEmpty())
	{
		AfxMessageBox(_T("The recipient account is empty, please enter the account number!"));
		m_editOppsiteAccount.SetFocus();
		return;
	}
	// 打开默认图标对话框
	CString strName(_T(""));
	CString strPath(_T(""));
	TCHAR szFilters[] = _T("GIF Files (*.gif)|*.gif||");
	CString strFilePath = CTools::getCurrentPath();
	strFilePath += _T("\\Emotion");
	CFileDialog fileDlg(TRUE, _T("gif"),NULL, OFN_ALLOWMULTISELECT|OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR, szFilters, NULL);
	fileDlg.m_ofn.lpstrInitialDir = strFilePath.GetBuffer();
	if (IDOK == fileDlg.DoModal())
	{
		int tempIndex=m_editSendMSG.picIndex++;

		strPath = fileDlg.GetPathName();
		m_editSendMSG.InsertImage(strPath,tempIndex);

		PicPathInfo pic;
		pic.index= tempIndex;
		pic.picPath=CTools::UNICODE2UTF(strPath);
		m_editSendMSG.msgTxtPic.pictures.push_back(pic);

		strName = fileDlg.GetFileName();
	}
	else
	{
		return;
	}



//	CImage image;
//	std::string strTemp = CTools::UNICODE2UTF(strPath);
//	std::wstring strTemp2 = CTools::string2wstring(strTemp);
//	image.Load(strTemp2.c_str());
//	CSize imageSize = CTools::GetImageSize(image.GetHeight(), image.GetWidth());
//	m_SendImArg.utcStamp = CTools::GetCurUTCTime();
//// 	InsertAccountTime(m_SendImArg.origin, m_SendImArg.utcStamp);
//// 	InsertImage(strPath, imageSize.cx, imageSize.cy, TRUE, CTools::GetFileName(strPath, FALSE), TRUE);
//	m_pDocument->clear();
//	CString strHtmlCont;
//	strHtmlCont.Format(_T("<img src=%s WIDTH=%dpx HEIGHT=%dpx />"), strPath, imageSize.cx, imageSize.cy);
//	UpdataChatContent(m_SendImArg.origin, m_SendImArg.utcStamp, strHtmlCont);
//	
//	// 发送消息
//	IM_S_GETUSERINFOARG argRecv;
//	IM_S_USERINFO userInfoRecv;
//	CTools::CString2Char(strAccount, argRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
//	CTools::CString2Char(strAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);
//
//	// 启用IM输入状态服务
//	TUP_RESULT tRet = tup_im_notifyiminputting(&m_statusArg);
//	if (TUP_SUCCESS != tRet)
//	{
//		AfxMessageBox(_T("tup_im_notifyiminputting failed!"));
//		return;
//	}
//
//	//精确查找接收方用户的信息
//	tRet = tup_im_getuserinfo(&argRecv, &userInfoRecv);
//	if (TUP_FAIL == tRet)
//	{
//		AfxMessageBox(_T("tup_im_getuserinfo failed！"));
//		return;
//	}
//	////精确匹配账户
//	if(0 != strcmp(userInfoRecv.account,CTools::UNICODE2UTF(strAccount).c_str()))
//	{
//		AfxMessageBox(_T("No Such User"));
//		return;
//	}
//
//	CString strSend(_T("<r><n>546L6aOeMDI=</n><g>0</g><c>&lt;imbody&gt;&lt;imagelist/&gt;&lt;html&gt;&lt;![CDATA[&lt;FONT style=&apos;font-size:14px&apos; face=&apos;Segoe UI&apos;&gt;&lt;IMG style=&quot;WIDTH: 26px; HEIGHT: 26px&quot; border=0 hspace=0 src=&quot;file:///UC.InternalImg//emotion/"));
//	strSend += strName;
//	strSend += CString(_T("&quot;&gt;&lt;/FONT&gt;]]&gt;&lt;/html&gt;&lt;content&gt;"));
//	for (map<CString, CString>::iterator item = m_EmotionReplace.begin(); item != m_EmotionReplace.end(); ++item)
//	{
//		if (strName == (item->second))
//		{
//			strName = item->first;
//			strSend += strName;
//			strSend += CString(_T("&lt;/content&gt;&lt;/imbody&gt;</c></r>"));
//			// 设置发送消息请求参数
//			m_SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
//			m_SendImArg.chatType = IM_E_IM_CHAT_TYPE_SINGLE;
//			m_SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
//			memcpy(m_SendImArg.target, userInfoRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
//			memcpy(m_SendImArg.origin, m_sendUserInfo.account, IM_D_MAX_ACCOUNT_LENGTH);
//			CTools::CString2Char(strSend, m_SendImArg.content, IM_D_MAX_MESSAGE_LENGTH);
//			m_SendImArg.utcStamp = CTools::GetCurUTCTime();
//			m_SendImArg.regionID = 0;
//			if (strcmp(m_SendImArg.target, m_SendImArg.origin) == 0)
//			{
//				AfxMessageBox(_T("The sender and receiver can't be the same!"));
//				return;
//			}
//			// 发送即时消息
//			TUP_RESULT tRet = tup_im_sendim(&m_SendImArg);
//			if(TUP_SUCCESS != tRet)
//			{
//				AfxMessageBox(_T("tup_im_sendim failed."));
//				return;
//			}
//		}
//	}
}
//************************************************************************

//************************************************************************
BOOL CIMMSGDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYDOWN == pMsg->message)
	{
		HWND hwndFocus = ::GetFocus();
		HWND hwndLogin = GetDlgItem(IDC_BUTTON_LOGIN)->GetSafeHwnd();
		HWND hwndEditSend = GetDlgItem(IDC_EDIT_SEND_MSG)->GetSafeHwnd();
		HWND hwndBtnSend = GetDlgItem(IDC_BUTTON_SEND_MSG)->GetSafeHwnd();
		HWND hwndLogout = GetDlgItem(IDC_BUTTON_LOGOFF)->GetSafeHwnd();
		HWND hwndExit = GetDlgItem(IDC_BUTTON_EXIT)->GetSafeHwnd();
		HWND hwndOppsiteAccount = GetDlgItem(IDC_EDIT_OPPSITE_ACCOUNT)->GetSafeHwnd();
		WPARAM nVirtKey = pMsg->wParam;

		if (VK_RETURN == nVirtKey)
		{
			// 焦点在登录按钮上
			if (hwndFocus == hwndLogin)
			{
				OnBnClickedButtonLogin();
				return TRUE;
			}

			// 焦点在消息编辑框或发送按钮上
			if (hwndFocus == hwndBtnSend)
			{
				OnBnClickedButtonSendMsg();
				return TRUE;
			}

			// 焦点在注销按钮
			if (hwndFocus == hwndLogout)
			{
				OnBnClickedButtonLogoff();
				return TRUE;
			}

			// 焦点在退出按钮
			if (hwndFocus == hwndExit)
			{
				OnBnClickedButtonExit();
				return TRUE;
			}

			// 焦点在接收方账户，则将焦点设置到下一控件
			if (hwndFocus == hwndOppsiteAccount)
			{
				m_editSendMSG.SetFocus();
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
//************************************************************************
void CIMMSGDemoDlg::SetOffLineLoginInfo(OFFLINE_LOGININFO& loginInfo,TUP_CHAR* umServerHttpsList,TUP_CHAR* umServerHttpList)
{
	// 初始化loginInfo参数字段
	loginInfo.enTlsMode = EN_TLS_VERIFY_NONE;
	loginInfo.stTlsPara.pcCaCertPath = HTTP_NULL;
	loginInfo.stTlsPara.pcClientCertPath = HTTP_NULL;
	loginInfo.stTlsPara.pcClientCertType = HTTP_NULL;
	loginInfo.stTlsPara.pcClientKeyPath = HTTP_NULL;
	loginInfo.stTlsPara.pcClientKeyType = HTTP_NULL;
	loginInfo.stTlsPara.pcClientPrivKeyPw = HTTP_NULL;
	loginInfo.stTlsPara.enVerifyServerMode = EN_VERIFY_SERVER_PEER;
	NEW_NULL_MEMORY_TPL(loginInfo.pcLocalIP, 20);

	// 获取IP数据
	BYTE field0, field1, field2, field3;
	m_ipAddress.GetAddress(field0, field1, field2, field3);
	char IP[100];
	memset(IP, 0, 100);
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);
	std::string localIP(IP);
	(void)memcpy_s(loginInfo.pcLocalIP, 20, localIP.c_str(), static_cast<UINT>(localIP.size()));

	loginInfo.timeout = 0;
	loginInfo.tryConnectTimeout = 0;
	loginInfo.enServerMode = OFFLINE_TRANSFER_UM;   /////目前仅支持UM服务器模式，云盘模式为华为内部私有，有核心资产校验
	loginInfo.bEncryTrans = TUP_FALSE;//云盘为TRUE
	OFFLINE_SERVERINFO stHttpsSer1;
	memset(&stHttpsSer1, 0, sizeof(OFFLINE_SERVERINFO));
	OFFLINE_SERVERINFO stHttpsSer2;
	memset(&stHttpsSer2, 0, sizeof(OFFLINE_SERVERINFO));

	//////开放给ISV时，只支持UM服务器这种模式  c00327158 Start//////
	if (OFFLINE_TRANSFER_UM == loginInfo.enServerMode)
	{
		unsigned int iSize = strlen(umServerHttpsList);
		stHttpsSer1.pcUrl = (TUP_CHAR*)malloc(iSize+1);
		memset(stHttpsSer1.pcUrl,0,iSize+1);
		memcpy(stHttpsSer1.pcUrl,umServerHttpsList,iSize);
	}
	//////开放给ISV时，只支持UM服务器这种模式  c00327158 End//////

	OFFLINE_SERVERINFO stHttpSer1;
	memset(&stHttpSer1, 0, sizeof(OFFLINE_SERVERINFO));
	OFFLINE_SERVERINFO stHttpSer2;
	memset(&stHttpSer2, 0, sizeof(OFFLINE_SERVERINFO));
	//////开放给ISV时，只支持UM服务器这种模式  c00327158 Start//////
	if (OFFLINE_TRANSFER_UM == loginInfo.enServerMode)
	{
		unsigned int iSize = strlen(umServerHttpList);
		stHttpSer1.pcUrl = (TUP_CHAR*)malloc(iSize+1);
		memset(stHttpSer1.pcUrl,0,iSize+1);
		memcpy(stHttpSer1.pcUrl,umServerHttpList,iSize);
	}
	//////开放给ISV时，只支持UM服务器这种模式  c00327158 End//////

	OFFLINE_SERVERLIST stLstHttpsSer;
	memset(&stLstHttpsSer, 0, sizeof(OFFLINE_SERVERLIST));
	stLstHttpsSer.ulCnt = 2;
	stLstHttpsSer.stServerUrl[0] = stHttpsSer1;
	stLstHttpsSer.stServerUrl[1] = stHttpsSer2;
	loginInfo.stHttpsSerList = stLstHttpsSer;

	OFFLINE_SERVERLIST stLstHttpSer;
	memset(&stLstHttpSer, 0, sizeof(OFFLINE_SERVERLIST));
	stLstHttpSer.ulCnt = 2;
	stLstHttpSer.stServerUrl[0] = stHttpSer1;
	stLstHttpSer.stServerUrl[1] = stHttpSer2;
	loginInfo.stHttpSerList = stLstHttpSer;

	loginInfo.ulMaxFileSize = 30 * 1024u * 1024u;// 30M(文件大小)
	//探测服务器刷新时间
	loginInfo.lServerExpiredAt = 1000 * 60;// 1分钟
	loginInfo.bPartTrans = TUP_FALSE;// 不支持分片传输
}
//************************************************************************
void CIMMSGDemoDlg::SetOffLineUserInfo(OFFLINE_USERINFO& userInfo)
{
	// 初始化userInfo参数字段
	CString account;
	CString cstrPSD;
	m_editPSD.GetWindowText(cstrPSD);
	m_editAccount.GetWindowText(account);
	userInfo.pcLoginName = (TUP_CHAR*)malloc(IM_D_MAX_ACCOUNT_LENGTH);
	userInfo.pcPassword = (TUP_CHAR*)malloc(IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(account, userInfo.pcLoginName, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(cstrPSD, userInfo.pcPassword, IM_D_MAX_ACCOUNT_LENGTH);
	NEW_NULL_MEMORY_TPL(userInfo.pcDeviceType, 512);
	(void)memcpy_s(userInfo.pcDeviceType, 512, "PC", 7);
	NEW_NULL_MEMORY_TPL(userInfo.pcDeviceName, 512);
	TCHAR  szBuff[256] = {0};
	DWORD  dwSize = 256;
	if (::GetComputerName(szBuff ,&dwSize))
	{
		CString strTempp(szBuff);
		std::string name = CTools::UNICODE2UTF(strTempp);
		(void)memcpy_s(userInfo.pcDeviceName, 512, name.c_str(), static_cast<UINT>(name.size()));
	}
	std::string sysinfo, sysversion, syssn;
	GetDeviceInfo(sysinfo, sysversion, syssn);
	unsigned int oslength = sysinfo.length() + 1;
	NEW_NULL_MEMORY_TPL(userInfo.pcDeviceOS, oslength);
	unsigned int snlength = syssn.length() + 1;
	NEW_NULL_MEMORY_TPL(userInfo.pcDeviceSN, snlength);
	unsigned int verlength = sysversion.length() + 1;
	NEW_NULL_MEMORY_TPL(userInfo.pcDeviceVersion, verlength);
	(void)memcpy_s(userInfo.pcDeviceOS, oslength, sysinfo.c_str(), sysinfo.length());
	(void)memcpy_s(userInfo.pcDeviceSN, snlength, syssn.c_str(), syssn.length());
	(void)memcpy_s(userInfo.pcDeviceVersion, verlength, sysversion.c_str() ,sysversion.length());

}
//************************************************************************
//  BOOL CIMMSGDemoDlg::s_bIsFinishDownload = FALSE;
//************************************************************************
BOOL CIMMSGDemoDlg::s_bIsUpload = TRUE;
//************************************************************************
CString CIMMSGDemoDlg::s_ImagePath = _T("");
//************************************************************************
void CIMMSGDemoDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}
//************************************************************************
void CIMMSGDemoDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}
//************************************************************************
LRESULT CIMMSGDemoDlg::OnSendImageInfo(WPARAM wParam, LPARAM lParam)
{
	////上传图片成功后，将图文信息发送接收方/////
	OFFLINE_RSPFILEINFO *pstFileRsp = (OFFLINE_RSPFILEINFO *)wParam;
	FontInfo m_font;
	m_font.m_size = 14,m_font.face = _T("Segoe UI"),m_font.m_rgb = RGB(0,0,0);
	PICUMInfo m_picUMinfo;
	m_picUMinfo.m_strLocalPath = s_ImagePath;
	m_picUMinfo.UMID = pstFileRsp->pcFileId;
	m_picUMinfo.UMURL = pstFileRsp->pcUrl;
	m_picUMinfo.UMAccessCode = pstFileRsp->pcPlainAccessCode;
	std::string m_Message = CTools::MakePicTxtMessage(m_picUMinfo,m_font,m_editSendMSG.msgTxtPic);
	ComCodeMsg(m_Message,m_Message);

	// 获取接收方账户
	CString	recvAccount;
	m_editOppsiteAccount.GetWindowText(recvAccount);
	if (recvAccount.IsEmpty()) 
	{
		AfxMessageBox(_T("Please enter the recipient account first!"));
		return -1L;
	}
	IM_S_GETUSERINFOARG argRecv;
	IM_S_USERINFO userInfoRecv;
	CTools::CString2Char(recvAccount, argRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(recvAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);

	//精确查找接收方用户的信息
	TUP_RESULT tRet = tup_im_getuserinfo(&argRecv, &userInfoRecv);
	if (TUP_FAIL == tRet)
	{
		AfxMessageBox(_T("tup_im_getuserinfo failed!"));
		return -1L;
	}
	////精确匹配账户
	if(0 != strcmp(userInfoRecv.account,CTools::UNICODE2UTF(recvAccount).c_str()))
	{
		AfxMessageBox(_T("No Such User"));
		return -1L;
	}

	// 设置发送消息请求参数
	m_SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
	m_SendImArg.mediaType = tagIM_E_IM_CHATMEDIA_TYPE_IMAGE;
	memcpy(m_SendImArg.target, userInfoRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
	strncpy_s(m_SendImArg.content, IM_D_MAX_MESSAGE_LENGTH*sizeof(char),m_Message.c_str(),_TRUNCATE);
	m_SendImArg.utcStamp = CTools::GetCurUTCTime();

	// 判断信息是否发送给自己
	if (strcmp(m_SendImArg.target, m_SendImArg.origin) == 0)
	{
		AfxMessageBox(_T("The sender and receiver can't be the same!"));
		return -1L;
	}
	// 发送即时消息
	tRet = tup_im_sendim(&m_SendImArg);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_sendim failed."));
		return -1L;
	}
	else
	{
		UpdataChatContent(m_SendImArg.origin, m_SendImArg.utcStamp, CTools::UTF2UNICODE(m_editSendMSG.msgTxtPic.txtMsg));
		InsertEmotion(m_editSendMSG.msgTxtPic.pictures,CTools::UTF2UNICODE(m_editSendMSG.msgTxtPic.txtMsg).GetLength());
	}
	/////清空发送窗口
	m_editSendMSG.msgTxtPic.txtMsg="";
	if (m_editSendMSG.msgTxtPic.pictures.size())
	{
		m_editSendMSG.msgTxtPic.pictures.clear();
	}
	m_editSendMSG.picIndex=0;
	m_editSendMSG.SetSel(0, -1);
	m_editSendMSG.Clear();
	return 0L;
}
//************************************************************************
LRESULT CIMMSGDemoDlg::OnShowDownloadImage(WPARAM wParam, LPARAM lParam)
{
	CImage image;
	image.Load(m_downloadImagePath.GetBuffer(0));
	CSize imageSize = CTools::GetImageSize (image.GetHeight(), image.GetWidth());
	ResizeImage(imageSize.cx, imageSize.cy);// 调整图片大小
	/////获取当前光标的位置/////
	m_editRecvMSG.SetSel(-1,-1);
	long nStartChar = 0;
	long nEndChar = 0;
	m_editRecvMSG.GetSel(nStartChar,nEndChar);
	m_editRecvMSG.SetSel(nStartChar - m_ImagePosition ,nStartChar - m_ImagePosition);
	m_editRecvMSG.InsertImage(m_downloadImagePath,0);
	return 0;
}
//************************************************************************
//************************************************************************
void CIMMSGDemoDlg::ProcessCotentFromeSpaceOrUC(std::string& cotent)
{
	size_t pos1 = cotent.find("<g>");
	size_t pos2 = cotent.find("</g>");
	std::string compValue = cotent.substr(pos1 + 3, pos2 - pos1 - 3);
	if (compValue == "1")
	{
		pos1 = cotent.find("<c>");
		pos2 = cotent.find("</c>");
		cotent = cotent.substr(pos1 + 3, pos2 - pos1 - 3);

		// 解码
		TUP_UINT nLength = cotent.length() + 1;
		TUP_UCHAR *pDecodeMsg = new TUP_UCHAR[nLength];
		tup_im_base64_decode(cotent.c_str(), pDecodeMsg,&nLength);

		// 解压缩
		TUP_CHAR *unCompSzbuffer = NULL;
		tup_im_gzlib_uncomp((TUP_CHAR*)pDecodeMsg, &unCompSzbuffer, (TUP_INT*)&nLength);
		cotent = unCompSzbuffer;

		SAFE_DELETEARRY(pDecodeMsg);
		tup_im_release_tup_mem(unCompSzbuffer);
		unCompSzbuffer = NULL;


	}
	else
	{
		CTools::ReplaceSpecialTag(cotent);
		CTools::ReplaceParagraphTag(cotent);
	}
}
//************************************************************************
void CIMMSGDemoDlg::ProgressCallBack(OFFLINEHANDLE fileHandle, TUP_UINT64 ulTotal, TUP_UINT64 ulNow, void *userInfo)
{
	TRACE2("ulTotal = %d, ulNow = %d", ulTotal, ulNow);
}
//************************************************************************
void CIMMSGDemoDlg::ResizeImage(LONG& lWidth, LONG& lHeight)
{
	RECT rcShowImg = {0, 0, 0, 0};
	int iShowImgWidth = (rcShowImg.right - rcShowImg.left) - 35;
	// 调整大小
	if (lWidth > iShowImgWidth && 0 != lWidth)
	{
		double tmpHeight = (((iShowImgWidth * (double)lHeight)/(double)lWidth) *1.0);
		lWidth = iShowImgWidth;
		lHeight = (int)tmpHeight;
	}
}
//************************************************************************
void CIMMSGDemoDlg::Splitstring(const std::string& srcString, const std::string& spiltchar, std::vector<std::string>& list_)
{
	std::string substring = srcString;
	std::string::size_type findpos; 

	while((findpos = substring.find_first_of(spiltchar)) != std::string::npos)
	{
		list_.push_back(substring.substr(0, findpos));
		substring = substring.substr(findpos+1);
	}
	list_.push_back(substring);
}
//************************************************************************
int CIMMSGDemoDlg::UMMsgTransResultCallback(OFFLINEHANDLE fileHandle, TUP_ULONG enCode, OFFLINE_RSPFILEINFO *pstFileRsp, void *userInfo)
{
	if (NULL == pstFileRsp) return 0;
	// 获得响应码
	HTTPULong ulStatus = pstFileRsp->ulStatusCode;

	std::string fileSessid = num2str<OFFLINEHANDLE>(fileHandle);
	UMDownLoadInfo downloadInfo;
	if (pstFileRsp->enCallbackType == OFFLINE_CALLBACK_DOWNLOAD)
	{
		fileSessid = downloadInfo.sessid;
	}

	if (0 == enCode)// 上传成功
	{
		if (ulStatus == 200 || ulStatus == 0)
		{
			if (s_bIsUpload)
			{
				// 上传图片
				//生成发给移动终端的content,UM格式
				::SendMessage(theApp.m_pMainWnd->m_hWnd, WM_SEND_IMAGEINFO, (WPARAM)pstFileRsp, 0);
			}
			else
			{
				// 下载图片
// 				s_bIsFinishDownload = TRUE;
				::SendMessage(theApp.m_pMainWnd->m_hWnd, WM_SHOW_DOWNLOADIMAGE, 0, 0);
			}
		}
	}
	return 0;
}
//************************************************************************
void CIMMSGDemoDlg::UnCompMsgFormat(CString& content, CString& sendContent)
{
	sendContent = _T("<r><g>0</g><c>");
	content.Replace(_T(" "), _T("&nbsp;"));
	content.Replace(_T("\r\n"), _T("&lt;BR&gt;"));
	content.Replace(_T("<BR>"), _T("&amp;lt;BR&amp;gt;"));
	CString strTemp(_T("&lt;imbody&gt;&lt;imagelist/&gt;&lt;html&gt;&lt;![CDATA[&lt;FONT style=&apos;font-size:14px&apos; face=&apos;Segoe UI&apos;&gt;"));
	strTemp += content;
	strTemp += _T("&lt;/FONT&gt;]]&gt;&lt;/html&gt;&lt;content&gt;");
	strTemp += content;
	strTemp += _T("&lt;/content&gt;&lt;/imbody&gt;");

	sendContent += strTemp;
	sendContent += _T("</c></r>");
	//sendContent.Replace(_T("&amp;"), _T("&"));
}

void CIMMSGDemoDlg::UNComCodeMsg(std::string& m_strSource, std::string& m_strTarget)
{
	CString content = CTools::UTF2UNICODE(m_strSource);
// 	content.Replace(_T(" "), _T("&nbsp;"));
// 	content.Replace(_T("\r\n"), _T("&lt;BR&gt;"));
// 	content.Replace(_T("<BR>"), _T("&amp;lt;BR&amp;gt;"));
// 	content.Replace(_T("<"), _T("&lt;"));
// 	content.Replace(_T(">"), _T("&gt;"));
// 	content.Replace(_T("\'"), _T("&apos;"));
// 	content.Replace(_T("\""), _T("&quot;"));
// 	content.Replace(_T(" "), _T("&nbsp;"));
// 	content.Replace(_T(" "), _T("&nbsp;"));
	m_strTarget = "<r><n>d3BjMDM=</n><g>0</g><c>" + CTools::UNICODE2UTF(content) + "</c></r>";
}
//************************************************************************
int CIMMSGDemoDlg::UpdataChatContent(TUP_CHAR account[], TUP_INT64 utcStamp, const CString& chatContent)
{

	CHARFORMAT cf;
	m_editRecvMSG.GetDefaultCharFormat(cf);

	CHARFORMAT cfNew;
	ZeroMemory(&cfNew, sizeof(CHARFORMAT));
	cfNew.cbSize = sizeof(CHARFORMAT);
	cfNew.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cfNew.dwEffects = 0;
	cfNew.yHeight = 16*16;//文字高度

	CString accountSelf;
	m_editAccount.GetWindowText(accountSelf);


	if (strcmp(CTools::UNICODE2UTF(accountSelf).c_str(), account) == 0)
	{
		cfNew.crTextColor = RGB(200, 100, 255); //文字颜色
	}
	else
	{
		cfNew.crTextColor = RGB(0, 100, 255); //文字颜色
	}

	CString recvMSG;
	m_editRecvMSG.GetWindowText(recvMSG);

	std::string msg=CTools::UNICODE2UTF(recvMSG);

	CString strShowMSGS("");
	strShowMSGS += CTools::UTF2UNICODE(account);
	strShowMSGS += _T(" ");
	strShowMSGS += CTools::FormatUTCTime(utcStamp);
	strShowMSGS += CString("\r\n");

	m_editRecvMSG.SetSel(msg.size(),msg.size()+CTools::UNICODE2UTF(strShowMSGS).size()-1);
	m_editRecvMSG.SetSelectionCharFormat(cfNew);
	m_editRecvMSG.ReplaceSel(strShowMSGS);

	
	CString strShowMSGBODY("");
	strShowMSGBODY += chatContent;
	strShowMSGBODY += CString("\r\n");

	m_editRecvMSG.SetSel(msg.size()+CTools::UNICODE2UTF(strShowMSGS).size(),msg.size()+CTools::UNICODE2UTF(strShowMSGS).size()+CTools::UNICODE2UTF(strShowMSGBODY).size()-1);
	m_editRecvMSG.SetSelectionCharFormat(cf);
	m_editRecvMSG.ReplaceSel(strShowMSGBODY);
	m_editRecvMSG.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return strShowMSGS.GetLength();
}
//************************************************************************
CString CIMMSGDemoDlg::s_SendMSG = _T("");
//************************************************************************
//////从UM服务端下载截图并返回本地存储URL///////
CString CIMMSGDemoDlg::DownloadImageFromServerce(UMINFo& m_UMinfo)
{
	s_bIsUpload = FALSE;
	/////获取%appdata%路径/////
	char myDir[MAX_PATH];
	SHGetSpecialFolderPathA(this->GetSafeHwnd(), myDir, CSIDL_APPDATA, 0);
	std::string fileSavePath(myDir);
	fileSavePath += "\\";
	///目前仅支持图片下载//////
	if (m_UMinfo.umFileType == "Img")
	{
		OFFLINEHANDLE fileHandle;
		OFFLINE_DOWN_FILEINFO downloadInfo;
		if (!m_UMinfo.umTransCode.empty())
		{
			std::string accessCode = m_UMinfo.umTransCode.c_str();
			downloadInfo.pPlainAccess = new OFFLINE_PlainAccess;
			downloadInfo.pPlainAccess->pcplainAccessCode = new HTTPChar[accessCode.length() + 1];
			memset(downloadInfo.pPlainAccess->pcplainAccessCode, 0, accessCode.length()+1);
			memcpy_s(downloadInfo.pPlainAccess->pcplainAccessCode, accessCode.length(),
				accessCode.c_str(), accessCode.length());
			downloadInfo.pPlainAccess->pcplainAccessCode[accessCode.length()] = '\0';
		}
		downloadInfo.bDownDelete = TUP_FALSE;// 适配漫游场景，文件不删除
		std::string filePath = fileSavePath + m_UMinfo.umFileName;
		downloadInfo.pcFilePath = const_cast<TUP_CHAR*>(filePath.c_str());
		downloadInfo.pcFileDownUrl = const_cast<TUP_CHAR*>(m_UMinfo.umFileUrl.c_str());
		downloadInfo.bUseSvnFile = TUP_FALSE;// 适配漫游场景，文件不删除
		TUP_RESULT tupRet = tup_offlinefile_downloadfile(&downloadInfo, &fileHandle, CIMMSGDemoDlg::ProgressCallBack, CIMMSGDemoDlg::UMMsgTransResultCallback);
		if (TUP_SUCCESS != tupRet)
		{
			AfxMessageBox(_T("tup_offlinefile_downloadfile failed!"));
		}
		if (downloadInfo.pPlainAccess)
		{
			if (downloadInfo.pPlainAccess->pcplainAccessCode)
			{
				delete[] downloadInfo.pPlainAccess->pcplainAccessCode;
			}
			delete downloadInfo.pPlainAccess;
		}
		return CTools::UTF2UNICODE(filePath);
	}
	else
		return CString("");
}
void CIMMSGDemoDlg::OnBnClickedButtonSendCatch()
{
	// TODO: Add your control notification handler code here
	// 将剪切板上的数据保存到本地
	if (IsClipboardFormatAvailable(CF_BITMAP))
	{
		if (OpenClipboard())
		{
			TCHAR path[MAX_PATH];
			SHGetSpecialFolderPath(0, path, CSIDL_APPDATA, 0);
			s_ImagePath = path;
			s_ImagePath += _T("\\");
			//使用当前时间命名
			CString dateStr = _T("");
			CTime curTime = CTime::GetCurrentTime();
			dateStr.Format(_T("%.4d%.2d%.2d%.2d%.2d%.2d"), curTime.GetYear(),curTime.GetMonth(),curTime.GetDay(),curTime.GetHour(),curTime.GetMinute(),curTime.GetSecond());
			s_ImagePath += dateStr;
			s_ImagePath += _T(".png");

			// 保存图片
			CImage image;
			BOOL bRet = FALSE;
			HBITMAP hBitmap = static_cast<HBITMAP>(::GetClipboardData(CF_BITMAP));
			if (hBitmap)
			{
				BITMAP bitmap;
				memset(&bitmap, 0, sizeof(BITMAP));
				int nResult = GetObject(hBitmap, sizeof(BITMAP), &bitmap);
				if (bitmap.bmType == 0 && nResult)
				{
					image.Attach(hBitmap);
					image.Save(s_ImagePath, Gdiplus::ImageFormatPNG);
					CSize imageSize = CTools::GetImageSize (image.GetHeight(), image.GetWidth());
					ResizeImage(imageSize.cx, imageSize.cy);// 调整图片大小
					m_SendImArg.utcStamp = CTools::GetCurUTCTime();
// 					InsertAccountTime(m_SendImArg.origin, m_SendImArg.utcStamp);
// 					InsertImage(s_ImagePath, imageSize.cx, imageSize.cy, TRUE, CTools::GetFileName(s_ImagePath, FALSE), TRUE);
		            m_pDocument->clear();
					CString strHtmlCont;
					strHtmlCont.Format(_T("<img src=%s WIDTH=%dpx HEIGHT=%dpx />"), s_ImagePath, imageSize.cx, imageSize.cy);
					UpdataChatContent(m_SendImArg.origin, m_SendImArg.utcStamp, strHtmlCont);
					// 此处应上传离线图片
					m_SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_RICHTEXT;
					// 上传图片
					OFFLINE_UP_FILEINFO fileInfo;
					UINT nLen = static_cast<UINT>(s_ImagePath.GetLength()) + 1;
					fileInfo.pcFilePath = new TUP_CHAR[nLen];
					std::string filePath = CTools::UNICODE2UTF(s_ImagePath);
					(void)memcpy_s(fileInfo.pcFilePath, sizeof(TUP_CHAR) * nLen, filePath.c_str(), nLen);

					CString imageName = CTools::GetFileName(s_ImagePath, FALSE);
					std::string strImageName = CTools::UNICODE2UTF(imageName);
					nLen = strImageName.size() + 1;
					fileInfo.pcFileName = new TUP_CHAR[nLen];
					(void)memcpy_s(fileInfo.pcFileName, sizeof(TUP_CHAR) * nLen, strImageName.c_str(), nLen);

					fileInfo.bDeleteFile = TUP_TRUE;
					fileInfo.userInfo = (void*)&m_UserInfo;
					OFFLINEHANDLE handle = 0;
					TUP_RESULT ulRet = tup_offlinefile_uploadfile(&fileInfo, &handle, CIMMSGDemoDlg::ProgressCallBack, CIMMSGDemoDlg::UMMsgTransResultCallback);
					if (ulRet != TUP_SUCCESS)
					{
						AfxMessageBox(_T("tup_offlinefile_uploadfile failed!"));
					}
					s_bIsUpload = TRUE;// 表示上传图片
					image.Destroy();
				}
			}
			DeleteObject(hBitmap);
			CloseClipboard();
		}
	}
	else
	{
		AfxMessageBox(_T("Interception picture then send!"));
	}

	GetDlgItem(IDC_BUTTON_SEND_CATCH)->EnableWindow(FALSE);
}
//************************************************************************
 void CIMMSGDemoDlg::OnEnKillfocusEditOppsiteAccount()
{
	// TODO: Add your control notification handler code here

	if (m_bLogOff) return;
	if (!m_bLoginFlag) return;
	CString recvAccount;
	m_editOppsiteAccount.GetWindowText(recvAccount);
	if (recvAccount.IsEmpty()) return;
	if (recvAccount != m_cstrOppositeAccount)
	{
// 		if (m_bIsOfflineMsg);
// 		else
// 		{
// 		}
		IM_S_GETUSERINFOARG argRecv;
		IM_S_USERINFO userInfoRecv;
		CTools::CString2Char(recvAccount, argRecv.account, IM_D_MAX_ACCOUNT_LENGTH);

		//精确查找接收方用户的信息
		TUP_RESULT tRet = tup_im_getuserinfo(&argRecv, &userInfoRecv);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("Username error, please re-enter!"));
			m_editOppsiteAccount.SetWindowText(_T(""));
			return;
		}
		m_stcInputStatic.SetWindowText(_T(""));
		CTools::CString2Char(recvAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);

		// 启用IM输入状态服务
		tRet = tup_im_notifyiminputting(&m_statusArg);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("Username error, please re-enter!"));
			return;
		}
		m_cstrOppositeAccount = recvAccount;
	}
 }

 void CIMMSGDemoDlg::OnBnClickedButton1()
 {
	 // TODO: Add your control notification handler code here
	 CString strAccount;
	 GetDlgItem(IDC_EDIT_OPPSITE_ACCOUNT)->GetWindowText(strAccount);
	 if (strAccount.IsEmpty())
	 {
		 AfxMessageBox(_T("The receiver account is empty,  please enter the account first!"));
		 GetDlgItem(IDC_EDIT_OPPSITE_ACCOUNT)->SetFocus();
		 return;
	 }
	 CFileDialog fd(TRUE);
	 CString strFile;
	 OPENFILENAME &ofn = fd.GetOFN();
	 ofn.lpstrFilter = _T("图像文件(*.bmp;*.jpg;*.jpeg;*.gif;*.png)\0*.bmp;*.jpg;*.jpeg;*.gif;*.png\0\0");
	 ofn.lpstrTitle = _T("添加文件");
	 ofn.lpstrFile = strFile.GetBuffer(MAX_PATH);
	 INT_PTR ret = fd.DoModal();
	 strFile.ReleaseBuffer();
	 if (ret == IDOK) {

		 int tempIndex=m_editSendMSG.picIndex++;

		 m_editSendMSG.InsertImage(strFile,tempIndex);

		 PicPathInfo pic;
		 pic.index= tempIndex;
		 pic.picPath=CTools::UNICODE2UTF(strFile);
		 m_editSendMSG.msgTxtPic.pictures.push_back(pic);
	 }
 }


 void CIMMSGDemoDlg::OnBnClickedButton2()
 {
	 // TODO: Add your control notification handler code here

	 CString sendMSG;
	 m_editSendMSG.GetWindowText(sendMSG);

	 m_editSendMSG.msgTxtPic.txtMsg=CTools::UNICODE2UTF(sendMSG);
	 m_editSendMSG.analysisMsg();

	 CString recvAccount;
	 m_editOppsiteAccount.GetWindowText(recvAccount);

	 IM_S_GETUSERINFOARG argRecv;
	 IM_S_USERINFO userInfoRecv;
	 memset(&argRecv,0,sizeof(IM_S_GETUSERINFOARG));
	 memset(&userInfoRecv,0,sizeof(IM_S_USERINFO));
	 CTools::CString2Char(recvAccount, argRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
	 CTools::CString2Char(recvAccount, m_statusArg.account, IM_D_MAX_ACCOUNT_LENGTH);

	 // 启用IM输入状态服务
	 TUP_RESULT tRet = tup_im_notifyiminputting(&m_statusArg);
	 if (TUP_SUCCESS != tRet)
	 {
		 AfxMessageBox(_T("Username error,please re-enter!"));
		 return;
	 }

	 //精确查找接收方用户的信息
	 tRet = tup_im_getuserinfo(&argRecv, &userInfoRecv);
	 if (TUP_FAIL == tRet)
	 {
		 AfxMessageBox(_T("Username error,please re-enter!"));
		 return;
	 }
	 ////精确匹配账户
	 if(0 != strcmp(userInfoRecv.account,CTools::UNICODE2UTF(recvAccount).c_str()))
	 {
		 AfxMessageBox(_T("No Such User"));
		 return;
	 }

	 CString isEmptyStr=CTools::ANSI2UNICODE(m_editSendMSG.msgTxtPic.txtMsg);
	 isEmptyStr=isEmptyStr.Trim();

	 ////图文均无，禁止发送////
	 if (isEmptyStr.IsEmpty() && (m_editSendMSG.msgTxtPic.pictures.size()<=0))
	 {
		 AfxMessageBox(_T("Message is empty,please re-enter!"));
		 m_editSendMSG.SetFocus();
		 return;
	 }
	 /////超过两张截图，禁止发送/////
	 m_strScrathURI.clear();
	 int m_ScratchPicNUm = GetScrachPicNum(m_editSendMSG.msgTxtPic,m_strScrathURI);
	 if (m_ScratchPicNUm > 1)
	 {
		 AfxMessageBox(_T("Over One Scratched Picture!"));
		 m_editSendMSG.SetWindowText(_T(""));
		 m_editSendMSG.SetFocus();
		 return;
	 }
	 ////组装消息/////
	 ////处理截图信息/////
	 if (m_ScratchPicNUm == 1)
	 {
		 ////上传截图////
		 CString strTempPath;
		 strTempPath= CTools::UTF2UNICODE(m_strScrathURI);
		 OFFLINE_UP_FILEINFO fileInfo;
		 UINT nLen = static_cast<UINT>(strTempPath.GetLength()) + 1;
		 fileInfo.pcFilePath = new TUP_CHAR[nLen];
		 std::string filePath = CTools::UNICODE2UTF(strTempPath);
		 (void)memcpy_s(fileInfo.pcFilePath, sizeof(TUP_CHAR) * nLen, filePath.c_str(), nLen);

		 CString imageName = CTools::GetFileName(strTempPath, FALSE);
		 std::string strImageName = CTools::UNICODE2UTF(imageName);
		 nLen = strImageName.size() + 1;
		 fileInfo.pcFileName = new TUP_CHAR[nLen];
		 (void)memcpy_s(fileInfo.pcFileName, sizeof(TUP_CHAR) * nLen, strImageName.c_str(), nLen);

		 fileInfo.bDeleteFile = TUP_TRUE;
		 fileInfo.userInfo = (void*)&m_UserInfo;
		 OFFLINEHANDLE handle = 0;
		 TUP_RESULT ulRet = tup_offlinefile_uploadfile(&fileInfo, &handle, CIMMSGDemoDlg::ProgressCallBack, CIMMSGDemoDlg::UMMsgTransResultCallback);
		 if (ulRet != TUP_SUCCESS)
		 {
			 AfxMessageBox(_T("tup_offlinefile_uploadfile failed!"));
		 }
		 s_bIsUpload = TRUE;// 表示上传图片
		 /////有截图信息等待上传完毕后发送/////
	 }
	 else
	 {
		 int m_length = m_editSendMSG.msgTxtPic.txtMsg.length();
		 std::string Content("");
		 FontInfo m_font;
		 m_font.m_size = 14,m_font.face = _T("Segoe UI"),m_font.m_rgb = RGB(0,0,0);
		 if (m_length <= 500)
		 {
			 // 未压缩的消息格式
			 Content = CTools::MakeUncomMessage(m_font,m_editSendMSG.msgTxtPic);
		 }
		 else if (m_length <= 1000)
		 {
			 // 压缩的消息格式
			 Content = CTools::MakeRARMessage(m_font,m_editSendMSG.msgTxtPic);
			 ComCodeMsg(Content,Content);
		 }
		 else
		 {
			 AfxMessageBox(_T("Message is too long, please re-enter!"));
			 m_editSendMSG.SetWindowText(_T(""));
			 m_editSendMSG.SetFocus();
			 return;
		 }

		// 设置发送消息请求参数
		memcpy(m_SendImArg.target, userInfoRecv.account, IM_D_MAX_ACCOUNT_LENGTH);
		strncpy_s(m_SendImArg.content, IM_D_MAX_MESSAGE_LENGTH*sizeof(char),Content.c_str(),_TRUNCATE);
		m_SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
		m_SendImArg.mediaType = tagIM_E_IM_CHATMEDIA_TYPE_TEXT;
		m_SendImArg.utcStamp = CTools::GetCurUTCTime();
		// 判断信息是否发送给自己
		if (strcmp(m_SendImArg.target, m_SendImArg.origin) == 0)
		{
			AfxMessageBox(_T("The sender and receiver can't be the same!"));
			return;
		}
		// 发送即时消息
		tRet = tup_im_sendim(&m_SendImArg);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_sendim failed."));
			return;
		}
		else
		{
			UpdataChatContent(m_SendImArg.origin, m_SendImArg.utcStamp, sendMSG);
			InsertEmotion(m_editSendMSG.msgTxtPic.pictures,sendMSG.GetLength());
		}
		//发送完成清空输入框
		m_editSendMSG.msgTxtPic.txtMsg="";
		if (m_editSendMSG.msgTxtPic.pictures.size())
		{
			m_editSendMSG.msgTxtPic.pictures.clear();
		}
		m_editSendMSG.picIndex=0;

		m_editSendMSG.SetSel(0, -1);
		m_editSendMSG.Clear();

	 }
 }
 void  CIMMSGDemoDlg::InsertEmotion(vector<PicPathInfo>& OutImagelist,int Pos)
 {
	 ////插入收到消息所带有的本地表情消息/////
	 vector<PicPathInfo>::iterator itbegin = OutImagelist.begin();
	 for(;itbegin != OutImagelist.end();itbegin++)
	 {
		 /////获取当前光标的位置/////
		 m_editRecvMSG.SetSel(-1,-1);
		 long nStartChar = 0;
		 long nEndChar = 0;
		 m_editRecvMSG.GetSel(nStartChar,nEndChar);
		 m_editRecvMSG.SetSel(nStartChar - Pos + itbegin->pos - 1,nStartChar - Pos + itbegin->pos - 1);
		 m_editRecvMSG.InsertImage(CTools::UTF2UNICODE(itbegin->picPath),0);
	 }
 }

 int CIMMSGDemoDlg::GetScrachPicNum(MsgToSend& msgTxtPic,std::string& m_strScrathURI)
 {
	 int m_scrachPic = 0;
	 m_strScrathURI.clear();
	 ////判断即将发送消息的（主要是判断图片信息）/////
	 vector<PicPathInfo>::iterator itBegin = msgTxtPic.pictures.begin();
	 for (;itBegin != msgTxtPic.pictures.end();itBegin++)
	 {
		 if (std::string::npos == itBegin->picPath.find("Emotion"))
		 {
			 ////查询路径中是否含有Emotion////
			 m_scrachPic ++;
			 m_strScrathURI.clear();
			 m_strScrathURI = itBegin->picPath;
		 }
	 }
	 return m_scrachPic;
 }