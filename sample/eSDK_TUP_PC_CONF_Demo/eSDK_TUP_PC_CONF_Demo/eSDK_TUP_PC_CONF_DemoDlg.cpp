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


// eSDK_TUP_PC_CONF_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_CONF_Demo.h"
#include "eSDK_TUP_PC_CONF_DemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define USER_AGENT				"Huawei SoftCoPCA"
#define HEARTBEAT_TIME (30*1000)
const int HEART_BEAT_TIMEID = 1000;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CeSDK_TUP_PC_CONF_DemoDlg dialog




CeSDK_TUP_PC_CONF_DemoDlg::CeSDK_TUP_PC_CONF_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CeSDK_TUP_PC_CONF_DemoDlg::IDD, pParent)
	, bLoginFlag(false)
	, m_strSipAccount("")
	, cstrOwnAccount(_T(""))
	, m_uiConfID(0)
	, bChairmanFlag(false)
	, bInMeetFlag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&localIP, 0, sizeof(localIP));
}

void CeSDK_TUP_PC_CONF_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGIN_ACCOUNT, m_editLoginAccount);
	DDX_Control(pDX, IDC_EDIT_LOGIN_PASSWORD, m_editLoginPassword);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ipCtrlServerIP);
	DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_editServerPort);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_BUTTON_LOGOFF, m_btnLogOff);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_btnLogOut);
	DDX_Control(pDX, IDC_EDIT_MEET_STATUS, m_editMeetStatus);
	DDX_Control(pDX, IDC_BUTTON_MEET_START, m_btnMeetStart);
	DDX_Control(pDX, IDC_BUTTON_MEET_END, m_btnMeetEnd);
	DDX_Control(pDX, IDC_BUTTON_MEMBER_ADD, m_btnAddMember);
	DDX_Control(pDX, IDC_BUTTON_MEMBER_DELETE, m_btnDelMember);
	DDX_Control(pDX, IDC_BUTTON_MEET_ACCEPT, m_btnAcceptMeet);
	DDX_Control(pDX, IDC_BUTTON_MEET_LEAVE, m_btnLeaveMeet);
	DDX_Control(pDX, IDC_LIST_MEET_MEMBER, m_listMeetMember);
	DDX_Control(pDX, IDC_EDIT_TARGET_ACCOUNT, m_editTargetAccount);
	DDX_Control(pDX, IDC_BUTTON_MEET_REFUSE, m_btnReFuseMeet);
}

BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_CONF_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOFF, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogoff)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_MEET_START, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetStart)
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_ADD, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMemberAdd)
	ON_MESSAGE(WM_MEET_CREATE_SUCCESS, &CeSDK_TUP_PC_CONF_DemoDlg::OnMeetCreateSuccess)
	ON_MESSAGE(WM_MEET_INVITE, &CeSDK_TUP_PC_CONF_DemoDlg::OnMeetInvite)
	ON_MESSAGE(WM_MEET_MEMBER_JOINED_SUCCESS, &CeSDK_TUP_PC_CONF_DemoDlg::OnMeetMemberJoined)
	ON_MESSAGE(WM_MEET_MEMBER_REFRESH, &CeSDK_TUP_PC_CONF_DemoDlg::OnMeetMemberRefresh)
	ON_MESSAGE(WM_MEET_ENDED, &CeSDK_TUP_PC_CONF_DemoDlg::OnMeetEnded)
	ON_MESSAGE(WM_MEET_MEM_SPEAK, &CeSDK_TUP_PC_CONF_DemoDlg::OnMeetShowSpkMember)
	ON_MESSAGE(WM_MEET_MANAGER_CONNECTED, &CeSDK_TUP_PC_CONF_DemoDlg::OnManagetConnect)
	ON_MESSAGE(WM_KICK_USER, &CeSDK_TUP_PC_CONF_DemoDlg::OnKickOutUser)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_MEET_ACCEPT, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetAccept)
	ON_BN_CLICKED(IDC_BUTTON_MEET_REFUSE, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetRefuse)
	ON_BN_CLICKED(IDC_BUTTON_MEET_END, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetEnd)
	ON_BN_CLICKED(IDC_BUTTON_MEET_LEAVE, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetLeave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_DELETE, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMemberDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEET_MEMBER, &CeSDK_TUP_PC_CONF_DemoDlg::OnNMClickListMeetMember)
END_MESSAGE_MAP()


// CeSDK_TUP_PC_CONF_DemoDlg message handlers

BOOL CeSDK_TUP_PC_CONF_DemoDlg::OnInitDialog()
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
	m_editLoginAccount.SetWindowTextW(_T("chenensheng01"));
	m_editLoginPassword.SetWindowTextW(_T("huawei.123"));
	m_ipCtrlServerIP.SetAddress(172, 22, 9, 42);
	m_editServerPort.SetWindowTextW(_T("8011"));
	SetLoginSectionCtrl(true);
	SetMeetSectionCtrl(MEET_INIT);
	SetLogOutSectionCtrl(false);
	OnListMemberInit();
	m_mapMeetMember.clear();

	////限制用户名，密码以及被叫方账户长度  c00327158 Start/////
	m_editLoginAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_editLoginPassword.LimitText(IM_D_MAX_PASSWORD_LENGTH);
	m_editTargetAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_editServerPort.LimitText(10);
	////限制用户名，密码以及被叫方账户长度  c00327158 End/////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CeSDK_TUP_PC_CONF_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CeSDK_TUP_PC_CONF_DemoDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CeSDK_TUP_PC_CONF_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CeSDK_TUP_PC_CONF_DemoDlg::OnListMemberInit()
{
	CRect rclistSize;
	m_listMeetMember.GetWindowRect(&rclistSize);
	int iColumnWidth = rclistSize.Width() / 5;
	m_listMeetMember.InsertColumn(COL_MEM_NAME, _T("姓名"), LVCFMT_LEFT, iColumnWidth);
	m_listMeetMember.InsertColumn(COL_MEM_ACCOUNT, _T("账号"), LVCFMT_LEFT, iColumnWidth);
	m_listMeetMember.InsertColumn(COL_MEM_STATUS, _T("成员状态"), LVCFMT_LEFT, iColumnWidth);
	m_listMeetMember.InsertColumn(COL_MEM_COMPERE, _T("是否主席"), LVCFMT_LEFT, iColumnWidth);
	m_listMeetMember.InsertColumn(COL_MEM_SPEAK_STATUS, _T("是否发言"), LVCFMT_LEFT, iColumnWidth);
	DWORD dwStyle = m_listMeetMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listMeetMember.SetExtendedStyle(dwStyle); //设置扩展风格
}

void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	if(bLoginFlag)
		return;

	//先登录UC服务器，然后再登录call服务器
	if(LoginUCService() && LoginCallService())
	{
		//服务器登录成功
		bLoginFlag = true;
		SetLoginSectionCtrl(false);
		SetLogOutSectionCtrl(true);
		SetMeetSectionCtrl(MEET_IDLE);
		m_editLoginAccount.GetWindowTextW(cstrOwnAccount);
		ListCtrlAndMapAddMember(cstrOwnAccount);
	}
}

bool CeSDK_TUP_PC_CONF_DemoDlg::LoginUCService(void)
{
	//获取服务器IP
	BYTE field0, field1, field2, field3;
	m_ipCtrlServerIP.GetAddress(field0, field1, field2, field3);
	char IP[100] = {0};
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);
	//计算本地的IP
	strncpy_s(localIP, IM_D_IP_LENGTH*sizeof(TUP_CHAR), CTools::GetBestHostip(IP).c_str(),_TRUNCATE);

	//获取端口
	CString cstrPort;
	m_editServerPort.GetWindowText(cstrPort);
	if (cstrPort.IsEmpty())
	{
		AfxMessageBox(_T("port is empty!"));
		return false;
	}
	int iPort = atoi(CTools::UNICODE2UTF(cstrPort).c_str());
	//设置服务器IP和端口
	TUP_RESULT tRet = tup_im_setserveraddress(IP,iPort);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setserveraddress Failed!"));
		return false;
	}

	// 设置IM回调消息上报函数地址
	tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(TEXT("tup_im_register_callback failed."));
		return false;
	}

	// 使能消息分发，否则消息不会上报
	tRet = tup_im_setdispatchmessage(TUP_TRUE);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(TEXT("tup_im_setdispatchmessage failed."));
		return false;
	}

	//获取用户名、密码
	CString account;
	CString cstrpwd;
	m_editLoginPassword.GetWindowText(cstrpwd);
	m_editLoginAccount.GetWindowText(account);
	if (account.IsEmpty() || cstrpwd.IsEmpty())
	{
		AfxMessageBox(_T("Username or password is empty!"));
		return false;
	}

	IM_S_LOGIN_ARG arg;
	memset(&arg,0,sizeof(IM_S_LOGIN_ARG));
	CTools::CString2Char(account, arg.account, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(cstrpwd, arg.password, IM_D_MAX_PASSWORD_LENGTH);
	arg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;
	//版本号固定
	CString cstrversion=_T("v1.1.11.103");
	CTools::CString2Char(cstrversion, arg.version, IM_D_MAX_VERSION_LENGTH);
	//登录UC服务器
	IM_S_LOGIN_ACK ack;
	memset(&ack,0,sizeof(IM_S_LOGIN_ACK));
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
		return false;
	}

	//定时向UC服务器发送心跳消息
	SetTimer(HEART_BEAT_TIMEID, HEARTBEAT_TIME, NULL);
	return true;
}


bool CeSDK_TUP_PC_CONF_DemoDlg::LoginCallService(void)
{
	IM_S_GETSERVICEPROFILEARG serviceArg = {0};
	serviceArg.isSyncAll = TUP_TRUE;
	serviceArg.isVpnAccess = TUP_FALSE;
	serviceArg.needIcon = TUP_TRUE;
	strncpy_s(serviceArg.localIP, IM_D_IP_LENGTH, localIP,_TRUNCATE);
	
	strncpy_s(serviceArg.timestamp, IM_D_MAX_TIMESTAMP_LENGTH, "19000000000000",_TRUNCATE);

	//获取业务参数
	IM_S_SERVICEPROFILEACK serviceAck = {0};
	TUP_RESULT tRet = tup_im_getserviceprofile(&serviceArg, &serviceAck);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getserviceprofile failed"));
		return false;
	}
	m_strSipAccount = serviceAck.sipAccount;

	//设置呼叫回调函数
	tRet = tup_call_register_process_notifiy(NotifyCallBack::CallNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_register_process_notify failed"));
		return false;
	}

	//设置传输模式
	CALL_E_TRANSPORTMODE eTransMode = CALL_E_TRANSPORTMODE_UDP;
	tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TRANS_MODE, &eTransMode);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SIP_TRANS_MODE failed."));
		return false;
	}

	std::string ip;
	int iServerPort;
	CTools::GetIPPort(serviceAck.sipServer, ip, iServerPort);

	//设置呼叫注册服务器
	CALL_S_SERVER_CFG sipServerCfg = {0};
	strncpy_s(sipServerCfg.server_address, CALL_D_MAX_URL_LENGTH, ip.c_str(),_TRUNCATE);
	sipServerCfg.server_port = iServerPort;
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_REG_PRIMARY failed."));
		return false;
	}

	memset(&sipServerCfg, 0, sizeof(sipServerCfg));
	strncpy_s(sipServerCfg.server_address, CALL_D_MAX_URL_LENGTH, ip.c_str(),_TRUNCATE);
	sipServerCfg.server_port = iServerPort;
	//设置呼叫代理服务器,一般和注册服务器相同
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_PROXY_PRIMARY, &sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_PROXY_PRIMARY failed."));
		return false;
	}

	//设置用户代理
	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_USEAGENT, USER_AGENT);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_USEAGENT failed."));
		return false;
	}

	//设置呼叫终端类型
	CALL_E_PRODUCT_TYPE eProductType = CALL_E_PRODUCT_TYPE_PC;
	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_PRODUCT_TYPE, (TUP_VOID*)&eProductType);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_PRODUCT_TYPE failed."));
		return false;
	}

	//设置本地地址
	CALL_S_IF_INFO IFInfo  ;
	memset(&IFInfo,0,sizeof(CALL_S_IF_INFO));
	IFInfo.ulType =  CALL_E_IP_V4;
	IFInfo.uAddress.ulIPv4 = inet_addr(localIP);
	tRet = tup_call_set_cfg(CALL_D_CFG_NET_NETADDRESS, &IFInfo);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_NET_NETADDRESS failed."));
		return false;
	}

	std::string sipAccount = serviceAck.sipAccount;
	std::string sipUserName = sipAccount + "@" + localIP;
	//发送注册请求
	tRet = tup_call_register(sipAccount.c_str(), sipUserName.c_str(), serviceAck.sipPassword);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_register failed."));
		return false;
	}
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

	return true;
}

void CeSDK_TUP_PC_CONF_DemoDlg::SetLoginSectionCtrl(bool bState)
{
	m_btnLogin.EnableWindow(bState);
	m_ipCtrlServerIP.EnableWindow(bState);
	m_editServerPort.EnableWindow(bState);
	m_editLoginAccount.EnableWindow(bState);
	m_editLoginPassword.EnableWindow(bState);
}

void CeSDK_TUP_PC_CONF_DemoDlg::SetLogOutSectionCtrl(bool bState)
{
	m_btnLogOff.EnableWindow(bState);
	m_btnLogOut.EnableWindow(bState);
}

void CeSDK_TUP_PC_CONF_DemoDlg::SetMeetSectionCtrl(int iCallStatus)
{
	switch(iCallStatus)
	{
	case MEET_INIT:
		m_editTargetAccount.EnableWindow(false);
		m_btnAddMember.EnableWindow(false);
		m_btnDelMember.EnableWindow(false);
		m_btnMeetStart.EnableWindow(false);
		m_btnMeetEnd.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		m_btnLeaveMeet.EnableWindow(false);
		m_listMeetMember.EnableWindow(false);
		break;
	case MEET_IDLE:
		m_btnAddMember.EnableWindow(true);
		m_btnDelMember.EnableWindow(true);
		m_btnMeetStart.EnableWindow(true);
		m_btnMeetEnd.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		m_btnLeaveMeet.EnableWindow(false);
		m_editTargetAccount.EnableWindow(true);
		m_listMeetMember.EnableWindow(true);
		m_editMeetStatus.SetWindowTextW(_T("空闲"));
		break;
	case MEET_INCOMING:
		m_btnAddMember.EnableWindow(false);
		m_btnDelMember.EnableWindow(false);
		m_btnMeetStart.EnableWindow(false);
		m_btnMeetEnd.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(true);
		m_btnReFuseMeet.EnableWindow(true);
		m_btnLeaveMeet.EnableWindow(false);
		m_editTargetAccount.EnableWindow(false);
		break;
	case MEET_CONNECTED:
		m_btnMeetStart.EnableWindow(false);
		if(bChairmanFlag)
		{
			m_btnMeetEnd.EnableWindow(true);
			m_btnLeaveMeet.EnableWindow(false);
		}
		else
		{
			m_btnMeetEnd.EnableWindow(false);
			m_btnLeaveMeet.EnableWindow(true);
		}
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		break;
	}

}

//注销服务器
void CeSDK_TUP_PC_CONF_DemoDlg::LogoutService()
{
	TUP_RESULT tRet = tup_call_deregister(m_strSipAccount.c_str());
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(_T("tup_call_deregister failed."));
	}

	tRet = tup_im_logout();
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(_T("tup_im_logout failed."));
	}
}

//注销
void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogoff()
{
	// TODO: Add your control notification handler code here
	if(!bLoginFlag)
		return;

	if(bChairmanFlag)
	{
		//结束会议
		tup_call_serverconf_end(m_uiConfID);
	}
	else
	{
		//离开会议
		tup_call_serverconf_leave(m_uiConfID);
	}

	LogoutService();
	bChairmanFlag = false;
	ResourceClear();
	bLoginFlag = false;
	cstrOwnAccount.Empty();
	m_editMeetStatus.SetWindowTextW(_T(""));
	m_editTargetAccount.SetWindowTextW(_T(""));
	KillTimer(HEART_BEAT_TIMEID);
	SetLoginSectionCtrl(true);
	SetMeetSectionCtrl(MEET_INIT);
	SetLogOutSectionCtrl(false);
}


//退出
void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	if(bLoginFlag)
	{
		if(bChairmanFlag)
		{
			//结束会议
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			//离开会议
			tup_call_serverconf_leave(m_uiConfID);
		}

		LogoutService();
		KillTimer(HEART_BEAT_TIMEID);
	}

	EndDialog(IDCANCEL);    //关闭窗口
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetStart()
{
	// TODO: Add your control notification handler code here
	TUP_UINT32 uiConfID;
	TUP_UINT32 uiCallID;
	//新建会议
	TUP_RESULT tRet = tup_call_serverconf_create(&uiConfID, &uiCallID, "");
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_serverconf_create failed"));
		return;
	}

	//记录会议ID
	m_uiConfID = uiConfID;
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMemberAdd()
{
	// TODO: Add your control notification handler code here
	CString cstrTargetAccount;
	m_editTargetAccount.GetWindowTextW(cstrTargetAccount);
	if(cstrTargetAccount.GetLength() <= 0)
	{
		AfxMessageBox(_T("Target Account is not allowed empty"));
		return;
	}
	else
	{
		if(bInMeetFlag)
		{
			//处于会议状态
			int iFind = -1;
			if(MemberListFindColum(cstrTargetAccount, COL_MEM_ACCOUNT, iFind))
			{
				//该被邀请人已经在会议列表中
				CString m_MeetMemberStatus = m_listMeetMember.GetItemText(iFind, COL_MEM_STATUS);
				if(0 != m_MeetMemberStatus.Compare(_T("退出会议")))
				{
					AfxMessageBox(_T("The Target Account is existed!"));
					return;
				}
				else
				{
					if(!InviteNewMember(cstrTargetAccount))
					{
						AfxMessageBox(_T("Add Member Failed"));
						return;
					}
					m_editTargetAccount.SetWindowTextW(_T(""));
				}
			}
			else
			{
				//该被邀请人是新的联系人
				if(ListCtrlAndMapAddMember(cstrTargetAccount))
				{
					if(!InviteNewMember(cstrTargetAccount))
					{
						AfxMessageBox(_T("Add Member Failed"));
						return;
					}
				}
			}
		}
		else
		{
			//处于非会议状态
			if(ListCtrlAndMapAddMember(cstrTargetAccount))
			{
				m_editTargetAccount.SetWindowTextW(_T(""));
			}
		}
	}

	return;
}


bool CeSDK_TUP_PC_CONF_DemoDlg::getUserInfoByAccount(std::string _account, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg = {0};
	IM_S_QUERY_USERINFO_ACK ack = {0};
	ack.userList = NULL;
	strncpy_s(arg.key, IM_D_MAX_PHONE_LENGTH*sizeof(TUP_CHAR), _account.c_str(),_TRUNCATE);
	arg.type = IM_E_IMUSERQUERYTYPE_BY_ACCOUNT;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		return false;
	}

	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (0 == strcmp(curUserInfo.account, _account.c_str()))
		{
			_userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}
	tup_im_release_tup_list(ack.userList);

	if(!bRet)
	{
		return false;
	}

	return true;
}

bool CeSDK_TUP_PC_CONF_DemoDlg::getUserInfoByBindNo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg = {0};
	IM_S_QUERY_USERINFO_ACK ack = {0};
	strncpy_s(arg.key, IM_D_MAX_PHONE_LENGTH*sizeof(TUP_CHAR), acTelNum,_TRUNCATE);
	arg.type = IM_E_IMUSERQUERYTYPE_BY_BINDNO;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		return false;
	}

	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (0 == strcmp(curUserInfo.bindNO, acTelNum))
		{
			userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}
	tup_im_release_tup_list(ack.userList);

	return true;
}


bool CeSDK_TUP_PC_CONF_DemoDlg::ListCtrlAndMapAddMember(const CString& AddMemberAccount)
{
	int iFind = -1;
	if(MemberListFindColum(AddMemberAccount, COL_MEM_ACCOUNT, iFind))
	{
		AfxMessageBox(_T("The Target Account is existed!"));
		return false;
	}

	std::string strTargetAccount = CTools::UNICODE2UTF(AddMemberAccount);
	//获取目标账号的信息
	IM_S_USERINFO m_NewMemberInfo;
	if(getUserInfoByAccount(strTargetAccount, m_NewMemberInfo))
	{
		int iSize = m_listMeetMember.GetItemCount();
		m_listMeetMember.InsertItem(iSize, _T(""));
		m_listMeetMember.SetItemText(iSize, COL_MEM_NAME, CTools::UTF2UNICODE(m_NewMemberInfo.name));
		m_listMeetMember.SetItemText(iSize, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(m_NewMemberInfo.account));
		m_listMeetMember.SetItemText(iSize, COL_MEM_STATUS, _T("IDLE"));
		m_listMeetMember.SetItemText(iSize, COL_MEM_COMPERE, _T(""));
		m_listMeetMember.SetItemText(iSize, COL_MEM_SPEAK_STATUS, _T(""));
		//插入表格中
		MAP_MEET_MEMBER::iterator it = m_mapMeetMember.find(strTargetAccount);
		if(it == m_mapMeetMember.end())
		{
			m_mapMeetMember.insert(map<std::string, std::string>::value_type(m_NewMemberInfo.account, m_NewMemberInfo.bindNO));
		}
	}
	else
	{
		AfxMessageBox(_T("No Such User"));
		return false;
	}

	return true;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnMeetCreateSuccess(WPARAM wParam, LPARAM lParam)
{
	bChairmanFlag = true;
	int iFind = -1;
	if(MemberListFindColum(cstrOwnAccount, COL_MEM_ACCOUNT, iFind))
	{
		bInMeetFlag = true;
		m_editMeetStatus.SetWindowTextW(_T("会议中"));
		m_listMeetMember.SetItemText(iFind, COL_MEM_STATUS, _T("会议中"));
		m_listMeetMember.SetItemText(iFind, COL_MEM_COMPERE, _T("是"));
		SetMeetSectionCtrl(MEET_CONNECTED);
	}
	else
	{
		AfxMessageBox(_T("Chairman is failure to join the meeting!"));
		return false;
	}
	return 0L;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnMeetInvite(WPARAM wParam, LPARAM lParam)
{	
	CALL_S_CONF_INFO* notifyInfo = (CALL_S_CONF_INFO*)wParam;
	if(NULL == notifyInfo)
	{
		return -1L;
	}

	//设置”入会状态“控件
	m_editMeetStatus.SetWindowTextW(_T("被邀请加入会议"));
	m_uiConfID = notifyInfo->ulConfID;
	//显示邀请人
	IM_S_USERINFO userInfo;
	if(getUserInfoByBindNo(notifyInfo->acUserNumber, userInfo))
	{
		m_editTargetAccount.SetWindowTextW(CTools::UTF2UNICODE(userInfo.account));
	}
	SetMeetSectionCtrl(MEET_INCOMING);
	//清空目前的会议列表
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	return 0L;
}

//新加入一名会议员
LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnMeetMemberJoined(WPARAM wParam, LPARAM lParam)
{
	char* num = (char*)wParam;
	IM_S_USERINFO m_NewMemberInfo;
	if(getUserInfoByBindNo(num, m_NewMemberInfo))
	{
		int iFind = -1;
		CString cstrTargetAccount = CTools::UTF2UNICODE(m_NewMemberInfo.account);

		if(MemberListFindColum(cstrTargetAccount, COL_MEM_ACCOUNT, iFind))
		{
			m_listMeetMember.SetItemText(iFind, COL_MEM_STATUS, _T("会议中"));
		}
	}
	return 0L;
}

LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnMeetMemberRefresh(WPARAM wParam, LPARAM lParam)
{
	CALL_S_CONF_MEMBER* pMemList = (CALL_S_CONF_MEMBER*)wParam;
	TUP_UINT32 uiSize = (TUP_UINT32)lParam;

	for(TUP_UINT32 i = 0; i < uiSize; i++)
	{
		int iCurItemNum = -1;
		CString cstrConfState;
		if(pMemList[i].enState == CALL_E_CONF_ATTENDEE_INVITING)
		{	
			cstrConfState = L"邀请中";
		}
		else if(pMemList[i].enState == CALL_E_CONF_ATTENDEE_INCONF)
		{
			cstrConfState = L"会议中";
		}
		else if(pMemList[i].enState == CALL_E_CONF_ATTENDEE_INVITE_FAIL)
		{
			cstrConfState = L"邀请失败";
		}
		else if(pMemList[i].enState == CALL_E_CONF_ATTENDEE_ADD_FAIL)
		{
			cstrConfState = L"添加失败";
		}
		else if(pMemList[i].enState == CALL_E_CONF_ATTENDEE_OUT)
		{
			cstrConfState = L"退出会议";
		}

		//获取新用户信息
		IM_S_USERINFO userInfo = {0};
		if(!getUserInfoByBindNo(pMemList[i].acAttendeeNumber, userInfo))
		{
			AfxMessageBox(_T("Get target user info failed by bind no."));
		}

		std::string strAccount; 
		if(MemberListMapFindByBindNo(strAccount, pMemList[i].acAttendeeNumber))
		{
			//说明该会员已经存在列表中
			int iFind = -1;
			if(MemberListFindColum(CTools::UTF2UNICODE(strAccount), COL_MEM_ACCOUNT, iFind))
			{		
				iCurItemNum = iFind;
			}
			else
			{
				AfxMessageBox(_T("MeetMemberRefresh Failed"));
				return 0L;
			}
		}
		else
		{	
			//说明该会员还不在列表中
			ListCtrlAndMapAddMember(CTools::UTF2UNICODE(userInfo.account));
			iCurItemNum = m_listMeetMember.GetItemCount() - 1;
		}

		m_listMeetMember.SetItemText(iCurItemNum, COL_MEM_NAME, CTools::UTF2UNICODE(userInfo.name));
		m_listMeetMember.SetItemText(iCurItemNum, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(userInfo.account));
		m_listMeetMember.SetItemText(iCurItemNum, COL_MEM_STATUS, cstrConfState);

		if(pMemList[i].enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
		{
			m_listMeetMember.SetItemText(iCurItemNum, COL_MEM_COMPERE, _T("是"));
		}

		m_listMeetMember.SetItemText(iCurItemNum, COL_MEM_SPEAK_STATUS, _T(""));
	}

	delete pMemList;
	return 0L;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnMeetShowSpkMember(WPARAM wParam, LPARAM lParam)
{
	//先清空状态
	int iListSize = m_listMeetMember.GetItemCount();
	for(int i = 0; i< iListSize; i++)
	{
		m_listMeetMember.SetItemText(i, COL_MEM_SPEAK_STATUS, _T(""));
	}

	char* cPhoneNum = (char*)wParam;
	std::string strAccount; 
	if(MemberListMapFindByBindNo(strAccount, cPhoneNum))
	{
		int iFind = -1;
		CString cstrTargetAccount = CTools::UTF2UNICODE(strAccount);
		if(MemberListFindColum(cstrTargetAccount, COL_MEM_ACCOUNT, iFind))
		{
			m_listMeetMember.SetItemText(iFind, COL_MEM_SPEAK_STATUS, _T("是"));
		}
	}
	return 0L;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnMeetEnded(WPARAM wParam, LPARAM lParam)
{
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	SetMeetSectionCtrl(MEET_IDLE);
	return 0L;
}

LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnManagetConnect(WPARAM wParam, LPARAM lParam)
{
	//添加其他人员入会
	AddOtherMeetMember();
	return 0L;
}

LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnKickOutUser(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedButtonLogoff();
	AfxMessageBox(_T("Kicked Off, Please Relogin！"));
	return 0L;
}
bool CeSDK_TUP_PC_CONF_DemoDlg::AddOtherMeetMember()
{
	MAP_MEET_MEMBER::iterator it = m_mapMeetMember.begin();
	MAP_MEET_MEMBER::iterator itEnd = m_mapMeetMember.end();
	for(; it != itEnd; it++)
	{
		CString cstrOtherAccount = CTools::UTF2UNICODE(it->first);
		//排除自身
		if(cstrOwnAccount.Compare(cstrOtherAccount) != 0)
		{
			if(!InviteNewMember(cstrOtherAccount))
			{
				AfxMessageBox(_T("Add Member Failed"));
				return false;
			}
		}
	}

	return true;
}

//邀请新的联系人参加会议
bool CeSDK_TUP_PC_CONF_DemoDlg::InviteNewMember(const CString& cstrTargetAccount)
{
	std::string strTargetAccount = CTools::UNICODE2UTF(cstrTargetAccount);
	MAP_MEET_MEMBER::iterator it = m_mapMeetMember.find(strTargetAccount);

	std::string strCallno = it->second;
	TUP_RESULT tRet = tup_call_serverconf_add_attendee(m_uiConfID, 1 , strCallno.c_str(), strCallno.size()+1);
	if(TUP_SUCCESS == tRet)
	{
		int iFind = -1;
		if(MemberListFindColum(cstrTargetAccount, COL_MEM_ACCOUNT, iFind))
		{
			m_listMeetMember.SetItemText(iFind, COL_MEM_STATUS, _T("邀请中"));
		}

		return true;
	}

	return false; 
}

//从入会成员list控件中寻找
bool CeSDK_TUP_PC_CONF_DemoDlg::MemberListFindColum(const CString& cstrKey, int iColnum, int& iFind)
{
	int iSize = m_listMeetMember.GetItemCount();
	for(int i = 0; i< iSize; i++)
	{
		if(0 == cstrKey.Compare(m_listMeetMember.GetItemText(i, iColnum)))
		{
			iFind = i;
			return true;
		}
	}
	return false;
}

//从入会成员map中寻找
bool CeSDK_TUP_PC_CONF_DemoDlg::MemberListMapFindByBindNo(std::string& strAccount, const std::string& strBindNo)
{
	MAP_MEET_MEMBER::iterator it = m_mapMeetMember.begin();
	MAP_MEET_MEMBER::iterator itEnd = m_mapMeetMember.end();
	for(; it != itEnd; it++)
	{
		if(0 == strBindNo.compare(it->second))
		{
			strAccount = it->first;
			return true;
		}
	}

	return false;
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnBnClickedButtonLogout();

	CDialogEx::OnClose();
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetAccept()
{
	// TODO: Add your control notification handler code here
	//接听会议
	TUP_RESULT tRet = tup_call_serverconf_accept(m_uiConfID);
	if(TUP_SUCCESS == tRet)
	{
		bInMeetFlag = true;
		m_editMeetStatus.SetWindowTextW(_T("会议中"));
		SetMeetSectionCtrl(MEET_CONNECTED);
	}
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetRefuse()
{
	// TODO: Add your control notification handler code here
	//拒绝会议
	tup_call_serverconf_end(m_uiConfID);
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	m_editTargetAccount.SetWindowTextW(_T(""));
	SetMeetSectionCtrl(MEET_IDLE);
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetEnd()
{
	// TODO: Add your control notification handler code here
	//结束会议
	if(bChairmanFlag)
	{
		TUP_RESULT tRet = tup_call_serverconf_end(m_uiConfID);
		if(TUP_SUCCESS == tRet)
		{
			bChairmanFlag = false;
			ResourceClear();
			ListCtrlAndMapAddMember(cstrOwnAccount);
			SetMeetSectionCtrl(MEET_IDLE);
		}
	}	
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMeetLeave()
{
	// TODO: Add your control notification handler code here
	//离开会议
	TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
	if(TUP_SUCCESS == tRet)
	{
		ResourceClear();
		ListCtrlAndMapAddMember(cstrOwnAccount);
		SetMeetSectionCtrl(MEET_IDLE);
	}
}

void CeSDK_TUP_PC_CONF_DemoDlg::ResourceClear()
{
	bInMeetFlag = false;
	m_listMeetMember.DeleteAllItems();
	m_mapMeetMember.clear();
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(HEART_BEAT_TIMEID == nIDEvent)
	{
		TUP_RESULT tRet = tup_im_sendheartbeat();
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_im_sendheartbeat failed.");
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonMemberDelete()
{
	// TODO: Add your control notification handler code here
	CString cstrTargetAccount;
	m_editTargetAccount.GetWindowTextW(cstrTargetAccount);
	if(cstrTargetAccount.GetLength() <= 0)
	{
		AfxMessageBox(_T("Target Account is not allowed empty"));
		return;
	}

	if(0 == cstrOwnAccount.Compare(cstrTargetAccount))
	{
		AfxMessageBox(_T("Delete Self is not Allowed."));
		return;
	}
	
	std::string strTargetAccount = CTools::UNICODE2UTF(cstrTargetAccount);
	//假如处于会议状态，就直接剔除会议中的一员，但list控件中不删除该人；否则只要删除list控件中的一项
	if(bInMeetFlag)
	{
		IM_S_USERINFO m_NewMemberInfo;
		if(!getUserInfoByAccount(strTargetAccount, m_NewMemberInfo))
		{
			AfxMessageBox(_T("Get target user info failed by bind account."));
			return;
		}

		TUP_RESULT tRet = tup_call_serverconf_kick_attendee(m_uiConfID, m_NewMemberInfo.bindNO);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_serverconf_kick_attendee failed."));
			return;
		}
		m_editTargetAccount.SetWindowTextW(_T(""));
	}
	else
	{
		int iFind = -1;
		if(MemberListFindColum(cstrTargetAccount, COL_MEM_ACCOUNT, iFind))
		{
			m_listMeetMember.DeleteItem(iFind);
			MAP_MEET_MEMBER::iterator it = m_mapMeetMember.find(strTargetAccount);
			if(it != m_mapMeetMember.end())
			{
				m_mapMeetMember.erase(it);
			}

			m_editTargetAccount.SetWindowTextW(_T(""));
		}
		else
		{
			AfxMessageBox(_T("No Such User"));
			return;
		}
	}
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnNMClickListMeetMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	CString cstrTargetAccount = m_listMeetMember.GetItemText(pNMItemActivate->iItem, COL_MEM_ACCOUNT);
	m_editTargetAccount.SetWindowTextW(cstrTargetAccount);

	*pResult = 0;
}

void CeSDK_TUP_PC_CONF_DemoDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnCancel();
}
