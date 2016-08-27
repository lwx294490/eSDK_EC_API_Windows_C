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


// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "LoginDlg.h"
#include "Tools.h"
#include "NotifyCallBack.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLoginDlg 对话框

////offline/////
static const TUP_UINT64 def_max_offline_size = 3 * 1024u * 1024u * 1024u;

template<typename T>
void NEW_NULL_MEMORY_TPL(T*& t,unsigned int len)
{
	if(len > 1)
	{
		t = new T[len];
		memset( t, 0, sizeof(T) * len );
	}
}

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	,m_bLoginFlag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ipCtrlServerIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_edtServerPort);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_edtLoginAccount);
	DDX_Control(pDX, IDC_EDIT_PWD, m_edtPWD);
	DDX_Control(pDX, IDC_COMBO1, m_cbxStatus);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()

string GetLocalIPAddress()
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

// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_edtServerPort.SetWindowText(L"8011");
	m_ipCtrlServerIP.SetAddress(172,22,9,42);
	m_edtLoginAccount.SetWindowText(L"chenensheng01");
	m_edtPWD.SetWindowText(L"huawei.123");
	m_cbxStatus.InsertString(0,_T("在线"));
	m_cbxStatus.InsertString(1,_T("忙碌"));
	m_cbxStatus.InsertString(2,_T("离开"));
	m_cbxStatus.SetCurSel(0);
	/////DTS2015110405099 限制用户名、密码输入字符长度   by c00327158 Start////
	m_edtLoginAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_edtPWD.LimitText(IM_D_MAX_PASSWORD_LENGTH);
	m_edtServerPort.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	/////DTS2015110405099 限制用户名、密码输入字符长度   by c00327158 End////

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件IP数据
	BYTE field0,field1,field2,field3;
	m_ipCtrlServerIP.GetAddress(field0,field1,field2,field3);
	char IP[100] = {0};
	sprintf_s(IP,"%d.%d.%d.%d",field0,field1,field2,field3);
	std::string _serverIP(IP);
	//获取控件端口数据
	CString cstrPort;
	m_edtServerPort.GetWindowText(cstrPort);
	if (cstrPort.IsEmpty())
	{
		AfxMessageBox(_T("port is empty!"));
		return;
	}
	std::string strPort = CTools::UNICODE2UTF(cstrPort);
	int iPort = atoi(strPort.c_str());
	//设置服务器IP和端口
	TUP_RESULT tRet = tup_im_setserveraddress(_serverIP.c_str(),iPort);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_setserveraddress Failed!");
		return;
	}
	//设置回调函数
	tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_register_callback Failed!");
		return;
	}

	//设置登录参数

	CString account;
	CString cstrpwd;
	m_edtPWD.GetWindowText(cstrpwd);
	m_edtLoginAccount.GetWindowText(account);
	if (account.IsEmpty() || cstrpwd.IsEmpty())
	{
		AfxMessageBox(_T("Username or password is empty!"));
		return;
	}

	IM_S_LOGIN_ARG m_loginarg;
	memset(&m_loginarg,0,sizeof(IM_S_LOGIN_ARG));
	CTools::CString2Char(account,m_loginarg.account,IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(cstrpwd,m_loginarg.password,IM_D_MAX_PASSWORD_LENGTH);
	CString cstrversion=L"v2.3.6.10";
	CTools::CString2Char(cstrversion,m_loginarg.version,IM_D_MAX_VERSION_LENGTH);
	m_loginarg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;


	//调用登录接口
	IM_S_LOGIN_ACK ack;
	memset(&ack,0,sizeof(IM_S_LOGIN_ACK));
	tRet = tup_im_login(&m_loginarg,&ack);
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
		//使能消息分发/////
		tRet = tup_im_setdispatchmessage(TUP_TRUE);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
			return;
		}
		/////获取账号状态///////

		int i = m_cbxStatus.GetCurSel();
		IM_S_STATUSARG arg;
		if(i == 1)
		{
			arg.status = IM_E_STATUS_BUSY;
		}
		else if(i == 2)
		{
			arg.status = IM_E_STATUS_LEAVE;
		}
		else
		{
			arg.status = IM_E_STATUS_ONLINE;
		}
		
		CTools::CString2Char(L"desc",arg.desc,IM_D_MAX_STATUS_DESCLEN);
		
		TUP_RESULT tRet = tup_im_publishstatus(&arg);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_publishstatus failed."));
			return;
		}

		m_bLoginFlag = true;
		m_edtLoginAccount.GetWindowText(m_cstrAccount);
		m_iStatus = arg.status;

		IM_S_GETSERVICEPROFILEARG serviceArg={0};
		serviceArg.isSyncAll  = TUP_TRUE;
		serviceArg.isVpnAccess = TUP_FALSE;
		serviceArg.needIcon = TUP_TRUE;
		std::string LocalIPAddr;
		if (!CTools::GetBestHostip(LocalIPAddr,_serverIP))
		{
			return;
		}
		strcpy_s(serviceArg.localIP,IM_D_IP_LENGTH,LocalIPAddr.c_str());
		strcpy_s(serviceArg.timestamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");

		IM_S_SERVICEPROFILEACK serviceAck={0};
		tRet = tup_im_getserviceprofile(&serviceArg,&serviceAck);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_getserviceprofile failed."));
			return;
		}

		if(serviceAck.dataConfAddrList->data != NULL)
		{
			IM_S_DATACONFADDRINFO* pDataAddr = (IM_S_DATACONFADDRINFO*)serviceAck.dataConfAddrList->data;
			g_DataConfAddr = pDataAddr->dataConfAddr;
		}

		m_strSipAccount = serviceAck.sipAccount;		

		tRet = tup_call_register_process_notifiy(NotifyCallBack::CallNotify);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_register_process_notifiy failed."));
			return;
		}

		CALL_E_TRANSPORTMODE eTransMode =  CALL_E_TRANSPORTMODE_UDP;
		tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TRANS_MODE, &eTransMode);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SIP_TRANS_MODE failed."));
			return;
		}

		std::string ip;
		int iServerPort;
		CTools::GetIPPort(serviceAck.sipServer,ip,iServerPort);

		TUP_UINT32 server_port = iServerPort;

		CALL_S_SERVER_CFG sipServerCfg = {0};
		strcpy_s(sipServerCfg.server_address, ip.c_str());
		sipServerCfg.server_port = iServerPort;
		tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg );
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_REG_PRIMARY failed."));
			return;
		}

		memset(&sipServerCfg,0,sizeof(sipServerCfg));
		strcpy_s(sipServerCfg.server_address, ip.c_str());
		sipServerCfg.server_port = iServerPort;

		tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_PROXY_PRIMARY,&sipServerCfg);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_PROXY_PRIMARY failed."));
			return;
		}

		tRet = tup_call_set_cfg(CALL_D_CFG_ENV_USEAGENT,  USER_AGENT);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_USEAGENT failed."));
			return;
		}

		CALL_E_PRODUCT_TYPE eProductType = CALL_E_PRODUCT_TYPE_PC;
		tRet = tup_call_set_cfg(CALL_D_CFG_ENV_PRODUCT_TYPE, (TUP_VOID*)&eProductType);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_PRODUCT_TYPE failed."));
			return;
		}

		CALL_S_IF_INFO IFInfo  ;
		memset(&IFInfo,0,sizeof(CALL_S_IF_INFO));
		IFInfo.ulType =  CALL_E_IP_V4;
		IFInfo.uAddress.ulIPv4 = inet_addr(LocalIPAddr.c_str());
		tRet = tup_call_set_cfg(CALL_D_CFG_NET_NETADDRESS,  &IFInfo);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_NET_NETADDRESS failed."));
			return;
		}


		std::string sipAccount = serviceAck.sipAccount;
		std::string sipUserName = sipAccount + "@" + LocalIPAddr;

		tRet = tup_call_register(sipAccount.c_str(),sipUserName.c_str(),serviceAck.sipPassword);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_register."));
			return;
		}
		/////登录离线文件信息//////
		if (!LoginUM(m_loginarg,serviceAck,LocalIPAddr))
		{
			AfxMessageBox(_T("LoginUM Failed"));
		}

		g_Account = CTools::UNICODE2UTF(m_cstrAccount);
		g_SipAccount =  serviceAck.sipAccount;
		
		IM_S_QUERY_USERINFO_ARG accountArg;
		IM_S_QUERY_USERINFO_ACK ack;
		memset(&accountArg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
		memset(&ack,0,sizeof(IM_S_QUERY_USERINFO_ACK));
		strcpy_s(accountArg.key, IM_D_MAX_ACCOUNT_LENGTH, g_Account.c_str());
		accountArg.type = IM_E_IMUSERQUERYTYPE_BY_ACCOUNT;
		tRet = tup_im_queryuserinfo(&accountArg, &ack);
		if (TUP_SUCCESS != tRet)
		{
			return;
		}

		IM_S_USERINFO* self = (IM_S_USERINFO*)(ack.userList->data);
		g_UserID = self->staffID;
		g_Name = self->name;
		g_BindNO = self->bindNO;
		this->EnableWindow(FALSE);
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
		tup_im_release_tup_list(ack.userList);

		OnOK();

	}
}


BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;           
		if(nVirtKey == VK_RETURN)   
		{   
			return TRUE;   
		}   
		if(nVirtKey == VK_ESCAPE)   
		{   
			return TRUE;   
		}   
	}

	return CDialog::PreTranslateMessage(pMsg);
}
BOOL CLoginDlg::LoginUM(IM_S_LOGIN_ARG& m_LoginArg,IM_S_SERVICEPROFILEACK& m_serverceAck,std::string& m_strLocalIP)
{
	////离线文件信息////
	OFFLINE_LOGININFO  m_offlineLoginInfo;// 离线文件登录信息
	OFFLINE_USERINFO   m_offlineUserInfo; // 离线文件用户信息
	
	GetOffLineLoginInfo(m_offlineLoginInfo,m_serverceAck,m_strLocalIP);

	GetOffLineUserInfo(m_offlineUserInfo,m_LoginArg);

	////登录UM服务器信息/////
	TUP_ULONG loginRes = 0L;
	 TUP_RESULT tRet = tup_offlinefile_login(&m_offlineLoginInfo, &m_offlineUserInfo, &loginRes);
	if (tRet != TUP_SUCCESS || loginRes != 200)/*loginRes返回200表示正常登陆，具体代码含义在C50中维护 */
	{
		DeleteOfflineInfo(m_offlineLoginInfo,m_offlineUserInfo);
		return FALSE;
	}

	DeleteOfflineInfo(m_offlineLoginInfo,m_offlineUserInfo);
	return TRUE;
}

void CLoginDlg::GetOffLineLoginInfo(OFFLINE_LOGININFO& m_offlineLoginInfo,IM_S_SERVICEPROFILEACK& m_serverceAck,std::string& m_strLocalIP)
{
	TUP_CHAR* umServerHttpsList = new TUP_CHAR[UMSERVERLENT+1];
	memset(umServerHttpsList,0,128+1);
	memcpy(umServerHttpsList,m_serverceAck.umServerHttpsList->data,UMSERVERLENT);

	TUP_CHAR* umServerHttpList = new TUP_CHAR[UMSERVERLENT+1];
	memset(umServerHttpList,0,UMSERVERLENT);
	memcpy(umServerHttpList,m_serverceAck.umServerHttpList->data,UMSERVERLENT);

	// 初始化loginInfo参数字段
	m_offlineLoginInfo.enTlsMode = EN_TLS_VERIFY_NONE;
	m_offlineLoginInfo.bPartTrans = TUP_FALSE;// 不支持分片传输
	m_offlineLoginInfo.stTlsPara.pcCaCertPath = HTTP_NULL;
	m_offlineLoginInfo.stTlsPara.pcClientCertPath = HTTP_NULL;
	m_offlineLoginInfo.stTlsPara.pcClientCertType = HTTP_NULL;
	m_offlineLoginInfo.stTlsPara.pcClientKeyPath = HTTP_NULL;
	m_offlineLoginInfo.stTlsPara.pcClientKeyType = HTTP_NULL;
	m_offlineLoginInfo.stTlsPara.pcClientPrivKeyPw = HTTP_NULL;
	m_offlineLoginInfo.stTlsPara.enVerifyServerMode = EN_VERIFY_SERVER_PEER;
	NEW_NULL_MEMORY_TPL(m_offlineLoginInfo.pcLocalIP, 20);

	// 获取IP数据
	(void)memcpy_s(m_offlineLoginInfo.pcLocalIP, 20, m_strLocalIP.c_str(), static_cast<UINT>(m_strLocalIP.size()));
	m_offlineLoginInfo.timeout = 0;
	m_offlineLoginInfo.tryConnectTimeout = 0;
	m_offlineLoginInfo.enServerMode = OFFLINE_TRANSFER_UM;   /////目前仅支持UM服务器模式，云盘模式为华为内部私有，有核心资产校验
	m_offlineLoginInfo.bEncryTrans = TUP_FALSE;//云盘为TRUE

	//////开放给ISV时，只支持UM服务器这种模式  c00327158 Start//////
	if (OFFLINE_TRANSFER_UM == m_offlineLoginInfo.enServerMode)
	{
		unsigned int iSize = strlen(umServerHttpsList);
		m_offlineLoginInfo.stHttpsSerList.ulCnt = 1;
		m_offlineLoginInfo.stHttpsSerList.stServerUrl->pcUrl = new TUP_CHAR[iSize + 1];
		memset(m_offlineLoginInfo.stHttpsSerList.stServerUrl->pcUrl,0,iSize + 1);
		memcpy(m_offlineLoginInfo.stHttpsSerList.stServerUrl->pcUrl,umServerHttpsList,iSize + 1);
	}
	//////开放给ISV时，只支持UM服务器这种模式  c00327158 End//////

	//////开放给ISV时，只支持UM服务器这种模式  c00327158 Start//////
	if (OFFLINE_TRANSFER_UM == m_offlineLoginInfo.enServerMode)
	{
		unsigned int iSize = strlen(umServerHttpList);
		m_offlineLoginInfo.stHttpSerList.ulCnt = 1;
		m_offlineLoginInfo.stHttpSerList.stServerUrl->pcUrl = new TUP_CHAR[iSize + 1];
		memset(m_offlineLoginInfo.stHttpSerList.stServerUrl->pcUrl,0,iSize);
		memcpy(m_offlineLoginInfo.stHttpSerList.stServerUrl->pcUrl,umServerHttpList,iSize + 1);
	}
	//////开放给ISV时，只支持UM服务器这种模式  c00327158 End//////

	m_offlineLoginInfo.ulMaxFileSize = 30 * 1024u * 1024u;// 30M(文件大小)
	//探测服务器刷新时间
	m_offlineLoginInfo.lServerExpiredAt = 1000 * 60;// 1分钟

	////释放参数/////
	SAFE_DELETE_ARRAY(umServerHttpsList);
	SAFE_DELETE_ARRAY(umServerHttpList);
}

void CLoginDlg::GetOffLineUserInfo(OFFLINE_USERINFO& m_offlineUserInfo,IM_S_LOGIN_ARG& m_LoginArg)
{
	// 初始化userInfo参数字段
	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcLoginName,IM_D_MAX_ACCOUNT_LENGTH);
	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcPassword,IM_D_MAX_PASSWORD_LENGTH);
	strncpy_s(m_offlineUserInfo.pcLoginName,IM_D_MAX_ACCOUNT_LENGTH,m_LoginArg.account,_TRUNCATE);
	strncpy_s(m_offlineUserInfo.pcPassword,IM_D_MAX_PASSWORD_LENGTH,m_LoginArg.password,_TRUNCATE);

	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcDeviceType, IM_D_MAX_ACCOUNT_LENGTH);
	strncpy_s(m_offlineUserInfo.pcDeviceType,IM_D_MAX_ACCOUNT_LENGTH,"PC",_TRUNCATE);
	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcDeviceName, IM_D_MAX_ACCOUNT_LENGTH);
	TCHAR  szBuff[256] = {0};
	DWORD  dwSize = 256;
	if (::GetComputerName(szBuff ,&dwSize))
	{
 		CString strTempp(szBuff);
 		std::string name = CTools::UNICODE2UTF(strTempp);
		strncpy_s(m_offlineUserInfo.pcDeviceName,IM_D_MAX_ACCOUNT_LENGTH,name.c_str(),_TRUNCATE);
	}
	std::string sysinfo, sysversion, syssn;
	GetDeviceInfo(sysinfo, sysversion, syssn);
	unsigned int oslength = sysinfo.length() + 1;
	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcDeviceOS, oslength);
	unsigned int snlength = syssn.length() + 1;
	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcDeviceSN, snlength);
	unsigned int verlength = sysversion.length() + 1;
	NEW_NULL_MEMORY_TPL(m_offlineUserInfo.pcDeviceVersion, verlength);
	(void)memcpy_s(m_offlineUserInfo.pcDeviceOS, oslength, sysinfo.c_str(), sysinfo.length());
	(void)memcpy_s(m_offlineUserInfo.pcDeviceSN, snlength, syssn.c_str(), syssn.length());
	(void)memcpy_s(m_offlineUserInfo.pcDeviceVersion, verlength, sysversion.c_str() ,sysversion.length());
}
BOOL CLoginDlg::GetDeviceInfo(std::string& sys, std::string& ver, std::string& sn)
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

VOID CLoginDlg::DeleteOfflineInfo(OFFLINE_LOGININFO& m_offlineLoginInfo,OFFLINE_USERINFO& m_offlineUserInfo)
{
	// 	////析构m_offlineLoginInfo/////
	SAFE_DELETE_ARRAY(m_offlineLoginInfo.pcLocalIP);
	SAFE_DELETE_ARRAY(m_offlineLoginInfo.stHttpSerList.stServerUrl->pcUrl);
	SAFE_DELETE_ARRAY(m_offlineLoginInfo.stHttpsSerList.stServerUrl->pcUrl);
	////析构m_offlineUserInfo/////
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcLoginName);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcPassword);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcAppName);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcLoginType);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcDeviceType);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcDeviceName);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcDeviceOS);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcDeviceSN);
	SAFE_DELETE_ARRAY(m_offlineUserInfo.pcDeviceVersion);


	
}