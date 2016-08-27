
// eSDK_TUP_PC_DeskShare_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_DeskShare_Demo.h"
#include "eSDK_TUP_PC_DeskShare_DemoDlg.h"
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


// CeSDK_TUP_PC_DeskShare_DemoDlg dialog




CeSDK_TUP_PC_DeskShare_DemoDlg::CeSDK_TUP_PC_DeskShare_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CeSDK_TUP_PC_DeskShare_DemoDlg::IDD, pParent)
	, bLoginFlag(false)
	, bChairmanFlag(false)
	, bInMeetFlag(false)
	, m_handle(0)
	, bInDataConfFlag(false)
	, m_strSipAccount("")
	, cstrOwnAccount(_T(""))
	, m_uiConfID(0)
	,m_uiCallID(0)
	,m_bisPresent(false)
	,m_OwnerBindNum("")
	,m_dlgModel(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGIN_ACCOUNT, m_editLoginAccount);
	DDX_Control(pDX, IDC_EDIT_LOGIN_PASSWORD, m_editLoginPassword);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ipCtrlServerIP);
	DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_editServerPort);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_EDIT_MEET_STATUS, m_editMeetStatus);
	DDX_Control(pDX, IDC_EDIT_MEET_COMPERE, m_editMeetCompere);
	DDX_Control(pDX, IDC_EDIT2, m_editMeetTime);
	DDX_Control(pDX, IDC_EDIT_MEET_SPEAKER, m_editMeetSpeaker);
	DDX_Control(pDX, IDC_LIST_MEET_MEMBER, m_listMeetMember);
	DDX_Control(pDX, IDC_BUTTON_MEET_START, m_btnMeetStart);
	DDX_Control(pDX, IDC_BUTTON_MEET_END, m_btnMeetEnd);
	DDX_Control(pDX, IDC_BUTTON_START_SHARE, m_btnShareStart);
	DDX_Control(pDX, IDC_BUTTON_END_SHARE, m_btnShareEnd);
	DDX_Control(pDX, IDC_EDIT_TARGET_ACCOUNT, m_editTargetAccount);
	DDX_Control(pDX, IDC_BUTTON_MEMBER_ADD, m_btnAddMember);
	DDX_Control(pDX, IDC_BUTTON_MEMBER_DELETE, m_btnDelMember);
	DDX_Control(pDX, IDC_EDIT3, m_editComingAccount);
	DDX_Control(pDX, IDC_BUTTON_FULL_SCREEN, m_btnFullScreen);
	DDX_Control(pDX, IDC_BUTTON_MEET_ACCEPT, m_btnAcceptMeet);
	DDX_Control(pDX, IDC_BUTTON_MEET_REFUSE, m_btnReFuseMeet);
	DDX_Control(pDX, IDC_BUTTON_MEET_LEAVE, m_btnLeaveMeet);
	DDX_Control(pDX, IDC_BUTTON_LOGOFF, m_btnLogOff);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_btnLogOut);
	DDX_Control(pDX, IDC_STATIC_DESKTOP, m_stcDeskTop);
	DDX_Control(pDX, IDC_BUTTON1, m_toShareDesk);
	DDX_Control(pDX, IDC_BUTTON2, m_getPresent);
}

BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_DeskShare_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonLogin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_ADD, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMemberAdd)
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_DELETE, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMemberDelete)
	ON_BN_CLICKED(IDC_BUTTON_MEET_START, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetStart)
	ON_BN_CLICKED(IDC_BUTTON_MEET_END, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetEnd)
	ON_BN_CLICKED(IDC_BUTTON_MEET_LEAVE, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetLeave)
	ON_BN_CLICKED(IDC_BUTTON_MEET_REFUSE, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetRefuse)
	ON_BN_CLICKED(IDC_BUTTON_MEET_ACCEPT, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetAccept)
	ON_BN_CLICKED(IDC_BUTTON_LOGOFF, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonLogoff)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonLogout)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_MEET_CREATE_SUCCESS, &CeSDK_TUP_PC_DeskShare_DemoDlg::MeetCreateSuccess)
	ON_MESSAGE(WM_MEET_INVITE, &CeSDK_TUP_PC_DeskShare_DemoDlg::MeetInvite)
	ON_MESSAGE(WM_MEET_MEMBER_JOINED_SUCCESS, &CeSDK_TUP_PC_DeskShare_DemoDlg::MeetMemberJoined)
	ON_MESSAGE(WM_MEET_MEMBER_REFRESH, &CeSDK_TUP_PC_DeskShare_DemoDlg::MeetMemberRefresh)
	ON_MESSAGE(WM_MEET_ENDED, &CeSDK_TUP_PC_DeskShare_DemoDlg::MeetEnded)
	ON_MESSAGE(WM_MEET_MANAGER_CONNECTED, &CeSDK_TUP_PC_DeskShare_DemoDlg::ManagetConnect)
	ON_MESSAGE(WM_DATACONF_CREAT, &CeSDK_TUP_PC_DeskShare_DemoDlg::DataConfCreate)
	ON_MESSAGE(WM_DATACONF_JOINSUCCESS, &CeSDK_TUP_PC_DeskShare_DemoDlg::DataConfJoinSuccess)
	ON_BN_CLICKED(IDC_BUTTON_START_SHARE, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonStartShare)
	ON_BN_CLICKED(IDC_BUTTON_FULL_SCREEN, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonFullScreen)
	ON_MESSAGE(WM_USER_KICKOUT, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnUserBeKickOut)
	ON_MESSAGE(WM_DATACONF_AS_STATE_NOTIFY,&CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfASStateShare)
	ON_MESSAGE(WM_DATACONF_AS_OWNER_NOTIFY,&CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfASGetOwerOK)
	ON_MESSAGE(WM_DATACONF_AS_SCREENDATA_NOTIFY,&CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfASUpdateScreen)
	ON_MESSAGE(WM_DATACONF_USER_ADD,&CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfUserAdd)
	ON_MESSAGE(WM_DATACONF_USER_DEL,&CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfUserDEL)
	ON_MESSAGE(WM_DATACONF_UPDATE_PRESENTINFO,&CeSDK_TUP_PC_DeskShare_DemoDlg::UpdatePresentInfo)
	ON_MESSAGE(WM_DATACONF_END,&CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfEnd)
	ON_MESSAGE(WM_DATACONF_UPDATE_CHAIRMAININFO,&CeSDK_TUP_PC_DeskShare_DemoDlg::UpdateChairmainInfo) 
	ON_BN_CLICKED(IDC_BUTTON1, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_END_SHARE, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonEndShare)
	ON_BN_CLICKED(IDC_BUTTON2, &CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CeSDK_TUP_PC_DeskShare_DemoDlg message handlers

BOOL CeSDK_TUP_PC_DeskShare_DemoDlg::OnInitDialog()
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


	//获取屏幕中间的位置
	int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
	int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);

	MoveWindow((cxFrame-WIDTH)/2,(cyFrame-HEITH)/2,WIDTH,HEITH);


	// TODO: Add extra initialization here
	m_editLoginAccount.SetWindowTextW(_T("chenensheng01"));
	m_editLoginAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_editLoginPassword.SetWindowTextW(_T("huawei.123"));
	m_ipCtrlServerIP.SetAddress(172, 22, 9, 42);
	m_editServerPort.SetWindowTextW(_T("8011"));
	SetLoginSectionCtrl(true);
	SetShareSectionCtrl(MEET_INIT);
	SetLogOutSectionCtrl(false);
	ListMemberInit();
	m_mapMeetMember.clear();
	m_mapMeetMembers.clear();
	m_stcDeskTop.SetBitmap2(NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CeSDK_TUP_PC_DeskShare_DemoDlg::OnPaint()
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
HCURSOR CeSDK_TUP_PC_DeskShare_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfEnd(WPARAM,LPARAM)
{
	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}
	////语音会议也需要关闭////
	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			tup_call_serverconf_leave(m_uiConfID);
		}

		m_uiCallID = 0;
	}


	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}
	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	SetShareSectionCtrl(MEET_IDLE);

	////界面显示信息清空////
	m_editMeetCompere.SetWindowTextW(_T(""));
	m_editComingAccount.SetWindowTextW(_T(""));
	m_editMeetSpeaker.SetWindowTextW(_T(""));


	return 0L;
}

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfUserAdd(WPARAM w,LPARAM l)
{
	TUP_ULONG role = (TUP_ULONG)w;
	TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)l;
	if(NULL == pRecord || (pRecord->user_alt_id<0) || (pRecord->user_alt_id >4294967295))
	{
		return -1L;
	}
	AddConfMemBer(pRecord);

	
	if(NULL != pRecord)
	{
		delete pRecord;
		pRecord = NULL;
	}
	return 0L;
}
LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfUserDEL(WPARAM w,LPARAM l)
{
	TUP_ULONG role = (TUP_ULONG)w;
	TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)l;
	if(NULL == pRecord)
	{
		return -1L;
	}
	//DleConfMemBer(pRecord);

	if(NULL != pRecord)
	{
		delete pRecord;
		pRecord = NULL;
	}
	return 0L;
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::AddConfMemBer(TC_Conf_User_Record* pRecord)
{
	std::string name = pRecord->user_name;
	std::string bindno = pRecord->user_alt_uri;
	CString cstrID;
	char strID[25]={0};
	itoa(pRecord->user_alt_id,strID,10);
	//CTools::string2CString(strID,cstrID);

	///查询与会者是否存在
	if (!SetUseridByBindNum(pRecord->user_alt_uri,pRecord->user_alt_id))
	{
		m_LocalMenber[pRecord->user_alt_uri] = pRecord->user_alt_id;
	}
}

bool CeSDK_TUP_PC_DeskShare_DemoDlg::SetUseridByBindNum(std::string BindNum,TUP_ULONG id)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			iter->second = id; 
			return true ;
		}

	}

	return false;
}

bool CeSDK_TUP_PC_DeskShare_DemoDlg::LoginUCService(void)
{
	//获取服务器IP
	BYTE field0, field1, field2, field3;
	m_ipCtrlServerIP.GetAddress(field0, field1, field2, field3);
	char IP[100] = {0};
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);
	//获取端口
	CString cstrPort;
	m_editServerPort.GetWindowText(cstrPort);
	std::string strPort = CTools::UNICODE2UTF(cstrPort);
	int iPort = atoi(strPort.c_str());
	//设置服务器IP和端口
	TUP_RESULT tRet = tup_im_setserveraddress(IP,iPort);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setserveraddress Failed!"));
		return false;
	}

	// 设置回调函数
	tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_register_callback failed!"));
		return false;
	}

	// 使能分发消息
	tRet = tup_im_setdispatchmessage(TUP_TRUE);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
		return false;
	}


	//获取用户名、密码
	IM_S_LOGIN_ARG arg;
	CString account;
	m_editLoginAccount.GetWindowText(account);
	CTools::CString2Char(account, arg.account, IM_D_MAX_ACCOUNT_LENGTH);
	CString cstrpwd;
	m_editLoginPassword.GetWindowText(cstrpwd);
	CTools::CString2Char(cstrpwd, arg.password, IM_D_MAX_PASSWORD_LENGTH);
	//版本号固定
	CString cstrversion=_T("v1.1.11.103");
	CTools::CString2Char(cstrversion, arg.version, IM_D_MAX_VERSION_LENGTH);
	arg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;
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


bool CeSDK_TUP_PC_DeskShare_DemoDlg::LoginCallService(void)
{
	IM_S_GETSERVICEPROFILEARG serviceArg = {0};
	serviceArg.isSyncAll = TUP_TRUE;
	serviceArg.isVpnAccess = TUP_FALSE;
	serviceArg.needIcon = TUP_TRUE;

	BYTE field0, field1, field2, field3;
	m_ipCtrlServerIP.GetAddress(field0, field1, field2, field3);
	char IP[100] = {0};
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);
	std::string LocalIPAddr;
	if (!CTools::GetBestHostip(LocalIPAddr,IP))
	{
		return false;
	}
	strcpy_s(serviceArg.localIP, IM_D_IP_LENGTH, LocalIPAddr.c_str());
	strcpy_s(serviceArg.timestamp, IM_D_MAX_TIMESTAMP_LENGTH, "19000000000000");

	//获取业务参数
	IM_S_SERVICEPROFILEACK serviceAck = {0};
	TUP_RESULT tRet = tup_im_getserviceprofile(&serviceArg, &serviceAck);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getserviceprofile failed"));
		return false;
	}
	m_strSipAccount = serviceAck.sipAccount;
	if(serviceAck.dataConfAddrList->data != NULL)
	{
		IM_S_DATACONFADDRINFO* pDataAddr = (IM_S_DATACONFADDRINFO*)serviceAck.dataConfAddrList->data;
		strOwnDataConfAddr = pDataAddr->dataConfAddr;
	}


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
	strcpy_s(sipServerCfg.server_address, CALL_D_MAX_URL_LENGTH, ip.c_str());
	sipServerCfg.server_port = iServerPort;
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_REG_PRIMARY failed."));
		return false;
	}

	memset(&sipServerCfg, 0, sizeof(sipServerCfg));
	strcpy_s(sipServerCfg.server_address, CALL_D_MAX_URL_LENGTH, ip.c_str());
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
	IFInfo.uAddress.ulIPv4 = inet_addr(LocalIPAddr.c_str());
	tRet = tup_call_set_cfg(CALL_D_CFG_NET_NETADDRESS, &IFInfo);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_NET_NETADDRESS failed."));
		return false;
	}

	std::string sipAccount = serviceAck.sipAccount;
	std::string sipUserName = sipAccount + "@" + LocalIPAddr;
	//发送注册请求
	tRet = tup_call_register(sipAccount.c_str(), sipUserName.c_str(), serviceAck.sipPassword);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_register failed."));
		return false;
	}

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

void CeSDK_TUP_PC_DeskShare_DemoDlg::SetLoginSectionCtrl(bool bState)
{
	m_btnLogin.EnableWindow(bState);
	m_ipCtrlServerIP.EnableWindow(bState);
	m_editServerPort.EnableWindow(bState);
	m_editLoginAccount.EnableWindow(bState);
	m_editLoginPassword.EnableWindow(bState);
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::SetLogOutSectionCtrl(bool bState)
{
	m_btnLogOff.EnableWindow(bState);
	m_btnLogOut.EnableWindow(bState);
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::SetShareSectionCtrl(int iCallStatus)
{
	switch(iCallStatus)
	{
	case MEET_INIT:
		m_btnMeetStart.EnableWindow(false);
		m_getPresent.EnableWindow(false);
		m_btnMeetEnd.EnableWindow(false);
		m_btnShareStart.EnableWindow(false);
		m_toShareDesk.EnableWindow(false);
		m_btnShareEnd.EnableWindow(false);
		m_editTargetAccount.EnableWindow(false);
		m_btnAddMember.EnableWindow(false);
		m_btnDelMember.EnableWindow(false);
		m_btnFullScreen.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		m_btnLeaveMeet.EnableWindow(false);
		m_editMeetStatus.SetWindowTextW(_T("空闲"));
		break;
	case MEET_IDLE:
		m_btnMeetStart.EnableWindow(true);
		m_btnMeetEnd.EnableWindow(false);
		m_getPresent.EnableWindow(false);
		m_btnShareStart.EnableWindow(false);
		m_toShareDesk.EnableWindow(false);
		m_btnShareEnd.EnableWindow(false);
		m_editTargetAccount.EnableWindow(true);
		m_btnAddMember.EnableWindow(true);
		m_btnDelMember.EnableWindow(true);
		m_btnFullScreen.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		m_btnLeaveMeet.EnableWindow(false);
		m_editMeetStatus.SetWindowTextW(_T("空闲"));
		break;
	case MEET_INCOMING:
		m_getPresent.EnableWindow(false);
		m_btnMeetStart.EnableWindow(false);
		m_btnMeetEnd.EnableWindow(false);
		m_btnShareStart.EnableWindow(false);
		m_toShareDesk.EnableWindow(false);
		m_btnShareEnd.EnableWindow(false);
		m_editTargetAccount.EnableWindow(false);
		m_btnAddMember.EnableWindow(false);
		m_btnDelMember.EnableWindow(false);
		m_btnFullScreen.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(true);
		m_btnReFuseMeet.EnableWindow(true);
		m_btnLeaveMeet.EnableWindow(false);
		m_editMeetStatus.SetWindowTextW(_T("有新来电"));
		break;
	case MEET_CONNECTED:

		m_btnMeetStart.EnableWindow(false);
		if(bChairmanFlag)
		{
			m_btnMeetEnd.EnableWindow(true);
			m_btnShareStart.EnableWindow(true);
			m_btnShareEnd.EnableWindow(false);
			m_btnLeaveMeet.EnableWindow(false);
			m_editTargetAccount.EnableWindow(true);
			m_btnAddMember.EnableWindow(true);
			m_btnDelMember.EnableWindow(true);
		}
		else
		{
			m_btnMeetEnd.EnableWindow(false);
			m_btnShareStart.EnableWindow(false);
			m_btnShareEnd.EnableWindow(false);
			m_btnLeaveMeet.EnableWindow(true);
			m_editTargetAccount.EnableWindow(false);
			m_btnAddMember.EnableWindow(false);
			m_btnDelMember.EnableWindow(false);
		}
		m_btnFullScreen.EnableWindow(false);
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		m_editMeetStatus.SetWindowTextW(_T("会议中"));
		break;
	case DATAMEET_CONNECTED:
		m_btnMeetStart.EnableWindow(false);
		if(bChairmanFlag)
		{
			m_btnMeetEnd.EnableWindow(true);
			m_btnShareStart.EnableWindow(false);
			m_btnShareEnd.EnableWindow(true);
			m_btnLeaveMeet.EnableWindow(false);
			m_editTargetAccount.EnableWindow(true);
			m_btnAddMember.EnableWindow(true);
			m_btnDelMember.EnableWindow(true);
		}
		else
		{
			m_btnMeetEnd.EnableWindow(false);
			m_btnShareStart.EnableWindow(false);
			m_btnShareEnd.EnableWindow(false);
			m_btnLeaveMeet.EnableWindow(true);
			m_editTargetAccount.EnableWindow(false);
			m_btnAddMember.EnableWindow(false);
			m_btnDelMember.EnableWindow(false);
		}
		m_btnFullScreen.EnableWindow(true);
		m_btnAcceptMeet.EnableWindow(false);
		m_btnReFuseMeet.EnableWindow(false);
		m_editMeetStatus.SetWindowTextW(_T("数据会议中"));
		break;
	}
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::ListMemberInit()
{
	CRect rclistSize;
	m_listMeetMember.GetWindowRect(&rclistSize);
	int iColumnWidth = rclistSize.Width() / 3;
	m_listMeetMember.InsertColumn(COL_MEM_NAME, _T("姓名"), LVCFMT_LEFT, iColumnWidth);
	m_listMeetMember.InsertColumn(COL_MEM_ACCOUNT, _T("账号"), LVCFMT_LEFT, iColumnWidth);
	m_listMeetMember.InsertColumn(COL_MEM_STATUS, _T("成员状态"), LVCFMT_LEFT, iColumnWidth);
	DWORD dwStyle = m_listMeetMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listMeetMember.SetExtendedStyle(dwStyle); //设置扩展风格
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonLogin()
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
		SetShareSectionCtrl(MEET_IDLE);
		m_editLoginAccount.GetWindowTextW(cstrOwnAccount);
		ListCtrlAndMapAddMember(cstrOwnAccount);

		std::string strOwnAccount = CTools::UNICODE2UTF(cstrOwnAccount);
		IM_S_USERINFO m_NewMemberInfo;
		if(!getUserInfoByAccount(strOwnAccount, m_NewMemberInfo))
		{
			AfxMessageBox(_T("Get target user info failed by bind account."));
			return;
		}
		strOwnUserID = m_NewMemberInfo.staffID;
		strOwnName = m_NewMemberInfo.name;
		strOwnBindNO = m_NewMemberInfo.bindNO;
	}
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnTimer(UINT_PTR nIDEvent)
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


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMemberAdd()
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

bool CeSDK_TUP_PC_DeskShare_DemoDlg::AddOtherMeetMember()
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

void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMemberDelete()
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
			MAP_MEET_MEMBERS::iterator its = m_mapMeetMembers.find(strTargetAccount);
			if(its != m_mapMeetMembers.end())
			{
				m_mapMeetMembers.erase(its);
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


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetStart()
{
	// TODO: Add your control notification handler code here
	std::string groupname = strOwnName;

	MAP_MEET_MEMBERS::iterator it = m_mapMeetMembers.begin();
	MAP_MEET_MEMBERS::iterator itEnd = m_mapMeetMembers.end();
	for(;it!=itEnd;it++)
	{
		if(it->first != CTools::UNICODE2UTF(cstrOwnAccount))
		{
			groupname.append(",");
			groupname.append(it->second.name);
		}
	}

	IM_S_IMGROUP_OP_ARG addDgroupArg;
	IM_S_ADDIMGROUP_ACK addDGroupAck;
	strcpy_s(addDgroupArg.fixedgroupInfo.name,IM_D_MAX_NAME_LENGTH,groupname.c_str());
	strcpy_s(addDgroupArg.fixedgroupInfo.owner,IM_D_MAX_ACCOUNT_LENGTH,CTools::UNICODE2UTF(cstrOwnAccount).c_str());
	TUP_RESULT tRet = tup_im_adddiscussiongroup(&addDgroupArg,&addDGroupAck);
	if(tRet == TUP_FAIL || addDGroupAck.result == TUP_FALSE)
	{
		AfxMessageBox(L"tup_im_adddiscussiongroup failed");
		return;
	}

	m_strGroupID = addDGroupAck.id;

	it = m_mapMeetMembers.begin();
	itEnd = m_mapMeetMembers.end();
	for(;it!=itEnd;it++)
	{
		std::string strAccount = it->first;
		//添加讨论组成员
		IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
		strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,addDGroupAck.id);
		strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,groupname.c_str());
		strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());

		tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(L"tup_im_adddiscussiongroupmember failed");
		}
	}

	TUP_UINT32 uiConfID = 0;
	TUP_UINT32 uiCallID = 0;
	//新建会议
	tRet = tup_call_serverconf_create(&uiConfID, &uiCallID,m_strGroupID.c_str());
	if(TUP_SUCCESS != tRet)
	{
		std::string errorDesc=tup_call_get_err_description(tRet);
		AfxMessageBox(_T("tup_call_serverconf_create failed"));
		return;
	}

	//记录会议ID
	m_uiConfID = uiConfID;
	m_uiCallID=uiCallID;
	//Sleep(1000);
	//////转数据会议
	//tRet = tup_call_serverconf_transferto_dataconf(m_uiConfID);
	//if(TUP_SUCCESS != tRet)
	//{
	//	AfxMessageBox(L"tup_call_serverconf_transferto_dataconf failed.");
	//	return;
	//}
}

TUP_UINT64 CeSDK_TUP_PC_DeskShare_DemoDlg::GetUserIDByBindNum(std::string BindNum)
{
	TUP_UINT64 tempid = 0;
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			tempid = iter->second;
			break;
		}
	}
	return tempid;
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetEnd()
{
	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}
	////语音会议也需要关闭////
	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			tup_call_serverconf_leave(m_uiConfID);
		}

		m_uiCallID = 0;
	}

	
	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}

	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	SetShareSectionCtrl(MEET_IDLE);

	////界面显示信息清空////
	m_editMeetCompere.SetWindowTextW(_T(""));
	m_editComingAccount.SetWindowTextW(_T(""));
	m_editMeetSpeaker.SetWindowTextW(_T(""));
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetLeave()
{
	// TODO: Add your control notification handler code here
	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}


	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
			if(TUP_SUCCESS == tRet)
			{
				ResourceClear();
				ListCtrlAndMapAddMember(cstrOwnAccount);
				SetShareSectionCtrl(MEET_IDLE);
			}
		}

		m_uiCallID = 0;
	}


	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;
	
	m_LocalMenber.clear();
	m_uiConfID = 0;
	m_uiCallID = 0;
	bChairmanFlag = false;
	m_bisPresent = false;
	m_ChaMainAccount = "";
	m_ChairMainBindNum = "";
	m_PresentAccount = "";
	m_PresentBindNUm = "";
	m_OwnerBindNum = "";

	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}

	////界面显示信息清空////
	m_editMeetCompere.SetWindowTextW(_T(""));
	m_editComingAccount.SetWindowTextW(_T(""));
	m_editMeetSpeaker.SetWindowTextW(_T(""));
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetRefuse()
{
	// TODO: Add your control notification handler code here
	//拒绝会议
	tup_call_serverconf_end(m_uiConfID);
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	m_editTargetAccount.SetWindowTextW(_T(""));
	SetShareSectionCtrl(MEET_IDLE);
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonMeetAccept()
{
	// TODO: Add your control notification handler code here
	//接听会议
	TUP_RESULT tRet = tup_call_serverconf_accept(m_uiConfID);
	if(TUP_SUCCESS == tRet)
	{
		bInMeetFlag = true;
		m_editMeetStatus.SetWindowTextW(_T("会议中"));
		SetShareSectionCtrl(MEET_CONNECTED);
	}
	else
	{
		std::string errorDesc=tup_call_get_err_description(tRet);
	}
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonLogoff()
{
	// TODO: Add your control notification handler code here
	if(!bLoginFlag)
		return;

	//if(bChairmanFlag)
	//{
	//	//结束会议
	//	tup_call_serverconf_end(m_uiConfID);
	//}
	//else
	//{
	//	//离开会议
	//	tup_call_serverconf_leave(m_uiConfID);
	//}

	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}


	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
			if(TUP_SUCCESS == tRet)
			{
				ResourceClear();
				ListCtrlAndMapAddMember(cstrOwnAccount);
				SetShareSectionCtrl(MEET_IDLE);
			}
		}

		m_uiCallID = 0;
	}


	



	LogoutService();

	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;

	m_LocalMenber.clear();
	m_uiConfID = 0;
	m_uiCallID = 0;
	bChairmanFlag = false;
	m_bisPresent = false;
	m_ChaMainAccount = "";
	m_ChairMainBindNum = "";
	m_PresentAccount = "";
	m_PresentBindNUm = "";
	m_OwnerBindNum = "";

	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}

	ResourceClear();
	bLoginFlag = false;
	cstrOwnAccount.Empty();
	m_editMeetStatus.SetWindowTextW(_T(""));
	m_editTargetAccount.SetWindowTextW(_T(""));
	KillTimer(HEART_BEAT_TIMEID);
	SetLoginSectionCtrl(true);
	SetShareSectionCtrl(MEET_INIT);
	SetLogOutSectionCtrl(false);
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	if(bLoginFlag)
	{
		//if(bChairmanFlag)
		//{
		//	//结束会议
		//	tup_call_serverconf_end(m_uiConfID);
		//}
		//else
		//{
		//	//离开会议
		//	tup_call_serverconf_leave(m_uiConfID);
		//}
		if(m_handle != 0)
		{

			if(bChairmanFlag)
			{
				tup_conf_terminate(m_handle);
			}	
			else
			{
				/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
				if(m_bisPresent)
				{
					tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
					tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
				}
				tup_conf_leave(m_handle);
			}

		}


		if(m_uiCallID != 0)
		{
			tup_call_end_call(m_uiCallID);
			m_uiCallID = 0;
		}
		if(m_uiConfID != 0)
		{
			if(bChairmanFlag)
			{
				tup_call_serverconf_end(m_uiConfID);
			}
			else
			{
				TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
				if(TUP_SUCCESS == tRet)
				{
					ResourceClear();
					ListCtrlAndMapAddMember(cstrOwnAccount);
					SetShareSectionCtrl(MEET_IDLE);
				}
			}

			m_uiCallID = 0;
		}






		LogoutService();

		bChairmanFlag = false;

		m_OwnerBindNum="";
		m_LocalMenber.clear();
		m_bisPresent = false;

		m_LocalMenber.clear();
		m_uiConfID = 0;
		m_uiCallID = 0;
		bChairmanFlag = false;
		m_bisPresent = false;
		m_ChaMainAccount = "";
		m_ChairMainBindNum = "";
		m_PresentAccount = "";
		m_PresentBindNUm = "";
		m_OwnerBindNum = "";

		if (m_dlgModel==1)
		{
			CRect rcSize;
			GetWindowRect(&rcSize);

			CRect rc;

			rc.left = rcSize.left;
			rc.top = rcSize.top;
			rc.right = rc.left + WIDTH;
			rc.bottom = rcSize.top + HEITH;

			MoveWindow(&rc,TRUE);
			ShowWindow(SW_SHOW);
			m_dlgModel=0;
		}
		if (m_handle)
		{
			tup_conf_release(m_handle);
			m_handle = 0;
		}

		ResourceClear();
		bLoginFlag = false;
		cstrOwnAccount.Empty();
		m_editMeetStatus.SetWindowTextW(_T(""));
		m_editTargetAccount.SetWindowTextW(_T(""));
		KillTimer(HEART_BEAT_TIMEID);
		SetLoginSectionCtrl(true);
		SetShareSectionCtrl(MEET_INIT);
		SetLogOutSectionCtrl(false);
	}

	EndDialog(IDCANCEL);    //关闭窗口
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::ResourceClear()
{
	bInMeetFlag = false;
	m_listMeetMember.DeleteAllItems();
	m_mapMeetMember.clear();
	m_mapMeetMembers.clear();
}

//注销服务器
void CeSDK_TUP_PC_DeskShare_DemoDlg::LogoutService()
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

bool CeSDK_TUP_PC_DeskShare_DemoDlg::ListCtrlAndMapAddMember(const CString& AddMemberAccount)
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
		//插入表格中
		MAP_MEET_MEMBER::iterator it = m_mapMeetMember.find(strTargetAccount);
		if(it == m_mapMeetMember.end())
		{
			m_mapMeetMember.insert(map<std::string, std::string>::value_type(m_NewMemberInfo.account, m_NewMemberInfo.bindNO));
		}
		MAP_MEET_MEMBERS::iterator its = m_mapMeetMembers.find(strTargetAccount);
		if(its == m_mapMeetMembers.end())
		{
			m_mapMeetMembers.insert(map<std::string, IM_S_USERINFO>::value_type(m_NewMemberInfo.account, m_NewMemberInfo));
		}
	}
	else
	{
		AfxMessageBox(_T("No Such User"));
		return false;
	}

	return true;
}

//从入会成员list控件中寻找
bool CeSDK_TUP_PC_DeskShare_DemoDlg::MemberListFindColum(const CString& cstrKey, int iColnum, int& iFind)
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
bool CeSDK_TUP_PC_DeskShare_DemoDlg::MemberListMapFindByBindNo(std::string& strAccount, const std::string& strBindNo)
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

bool CeSDK_TUP_PC_DeskShare_DemoDlg::getUserInfoByAccount(std::string _account, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	ack.userList = NULL;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _account.c_str());
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

	if(!bRet)
	{
		return false;
	}

	return true;
}

bool CeSDK_TUP_PC_DeskShare_DemoDlg::getUserInfoByBindNo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, acTelNum);
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

	return true;
}

//邀请新的联系人参加会议
bool CeSDK_TUP_PC_DeskShare_DemoDlg::InviteNewMember(const CString& cstrTargetAccount)
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


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}
	////语音会议也需要关闭////
	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			tup_call_serverconf_leave(m_uiConfID);
		}

		m_uiCallID = 0;
	}


	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}

	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}

	ResourceClear();

	if (cstrOwnAccount!="")
	{
		ListCtrlAndMapAddMember(cstrOwnAccount);
	}
	
	SetShareSectionCtrl(MEET_IDLE);


	OnBnClickedButtonLogout();
	CDialogEx::OnClose();
}


BOOL CeSDK_TUP_PC_DeskShare_DemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
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
	return CDialogEx::PreTranslateMessage(pMsg);
}



LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::MeetCreateSuccess(WPARAM wParam, LPARAM lParam)
{
	bChairmanFlag = true;
	int iFind = -1;
	if(MemberListFindColum(cstrOwnAccount, COL_MEM_ACCOUNT, iFind))
	{
		bInMeetFlag = true;
		m_editMeetStatus.SetWindowTextW(_T("会议中"));
		m_listMeetMember.SetItemText(iFind, COL_MEM_STATUS, _T("会议中"));
		SetShareSectionCtrl(MEET_CONNECTED);
	}
	else
	{
		AfxMessageBox(_T("Chairman is failure to join the meeting!"));
		return false;
	}
	return 0L;
}


LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::MeetInvite(WPARAM wParam, LPARAM lParam)
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
		m_editComingAccount.SetWindowTextW(CTools::UTF2UNICODE(userInfo.account));
	}
	SetShareSectionCtrl(MEET_INCOMING);
	//清空目前的会议列表
	ResourceClear();
	ListCtrlAndMapAddMember(cstrOwnAccount);
	return 0L;
}

//新加入一名会议员
LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::MeetMemberJoined(WPARAM wParam, LPARAM lParam)
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

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::MeetMemberRefresh(WPARAM wParam, LPARAM lParam)
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
		IM_S_USERINFO userInfo;
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
	}

	delete pMemList;
	return 0L;
}


LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::MeetEnded(WPARAM wParam, LPARAM lParam)
{
	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}
	////语音会议也需要关闭////
	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			tup_call_serverconf_leave(m_uiConfID);
		}

		m_uiCallID = 0;
	}


	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}


	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}

	ResourceClear();

	if (cstrOwnAccount!="")
	{
		ListCtrlAndMapAddMember(cstrOwnAccount);
	}

	SetShareSectionCtrl(MEET_IDLE);

	////界面显示信息清空////
	m_editMeetCompere.SetWindowTextW(_T(""));
	m_editComingAccount.SetWindowTextW(_T(""));
	m_editMeetSpeaker.SetWindowTextW(_T(""));

	return 0L;
}

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::ManagetConnect(WPARAM wParam, LPARAM lParam)
{
	//添加其他人员入会
//	AddOtherMeetMember();

	MAP_MEET_MEMBERS::iterator it = m_mapMeetMembers.begin();
	MAP_MEET_MEMBERS::iterator itEnd = m_mapMeetMembers.end();

	it = m_mapMeetMembers.begin();
	itEnd = m_mapMeetMembers.end();
	for(;it!=itEnd;it++)
	{
		if (it->second.bindNO == strOwnBindNO)
		{
			continue;
		}
		std::string strCallno =it->second.bindNO;
		TUP_RESULT tRet = tup_call_serverconf_add_attendee(m_uiConfID,1,strCallno.c_str(),strCallno.size()+1);
	}
	return 0L;
}

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::DataConfCreate(WPARAM wParam, LPARAM lParam)
{
	if(0 != m_handle)
	{
		return 0L;
	}
	CALL_S_DATACONF_PARAM* pNotify = (CALL_S_DATACONF_PARAM*)wParam;

	m_editMeetStatus.SetWindowText(_T("正在加入数据会议"));
	//会议信息
	TC_CONF_INFO* confInfo = new TC_CONF_INFO;
	TUP_UINT8 * pdata = new TUP_UINT8[10];
	memset(pdata, '8', 10);
	pdata[9] = 0;
	confInfo->conf_id = atoi(pNotify->acDataConfID);
	confInfo->user_id = strOwnUserID;
	confInfo->os_type = CONF_OS_WIN;
	confInfo->dev_type = CONF_DEV_PC;
	confInfo->user_info = pdata;
	confInfo->user_info_len = 9;
	if(CALL_E_CONF_ROLE_CHAIRMAN == pNotify->enRole)
	{
		confInfo->user_type = CONF_ROLE_HOST|CONF_ROLE_PRESENTER;
		bChairmanFlag = true;
	}
	else if(CALL_E_CONF_ROLE_ATTENDEE == pNotify->enRole)
	{
		confInfo->user_type = CONF_ROLE_GENERAL;
		bChairmanFlag = false;
	}

	strcpy_s(confInfo->user_name, TC_MAX_USER_NAME_LEN, strOwnName.c_str());
	strcpy_s(confInfo->host_key, TC_MAX_HOST_KEY_LEN, "111111");

	strcpy_s(confInfo->site_id, TC_MAX_CONF_SITE_ID_LEN,  "6jf1");
	strcpy_s(confInfo->ms_server_ip, TC_MAX_CONF_SERVER_IP, strOwnDataConfAddr.c_str());
	strcpy_s(confInfo->encryption_key, TC_MAX_ENCRYPTION_KEY, pNotify->acAuthKey);

	//strcpy_s(confInfo->site_url, TC_MAX_SITE_URL_LEN, "10.170.103.86:5060");
	strcpy_s(confInfo->site_url, TC_MAX_SITE_URL_LEN,pNotify->acCmAddr);
	strcpy_s(confInfo->user_log_uri, TC_MAX_USER_LOG_URI_LEN, strOwnBindNO.c_str());
	CONF_HANDLE handle;
	TUP_RESULT tRet = tup_conf_new(NotifyCallBack::ConfNotify, confInfo, CONF_OPTION_BASE | CONF_OPTION_USERLIST|CONF_OPTION_PHONE|CONF_OPTION_PRESENTER_GRAB,&handle);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_new failed."));
		return 0L;
	}

	m_handle = handle;

	tRet = tup_conf_join(handle);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_join failed."));
		return 0L;
	}

	
	m_uiConfID=pNotify->ulConfID;
	m_uiCallID=pNotify->ulCallID;
	
	IM_S_USERINFO m_CharmanInfo;
	if (0 == strlen(pNotify->acCharman))
	{
		////此时pNotify.acCharman（USM不带主席信息）那么，我们就查询群组的拥有者，指定其为主席//////
		IM_S_IMGROUPINFO _groupInfo;
		tRet = tup_im_getfixedgroupdetail(pNotify->acGroupUri,&_groupInfo);
		if (tRet != TUP_SUCCESS || !getUserInfoByAccount(std::string(_groupInfo.owner),m_CharmanInfo))
		{
			AfxMessageBox(_T("获取主席信息失败"));
			return 0L;
		}

	}
	else
	{
		if (!getAccountINfoByBingNum(std::string(pNotify->acCharman),m_CharmanInfo))
		{
			AfxMessageBox(_T("获取主席信息失败"));
			return 0L;
		}
	}
	m_ChairMainBindNum = m_CharmanInfo.bindNO;
	m_ChaMainAccount = m_CharmanInfo.account;
	std::string m_ChairmanName = m_CharmanInfo.name;
	m_editMeetCompere.SetWindowText(CTools::UTF2UNICODE(m_ChairmanName));

	m_stcDeskTop.m_handle = m_handle;
	return 0L;
}


LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::DataConfJoinSuccess(WPARAM wParam, LPARAM lParam)
{
	//加载指定的组件
	TUP_UINT32 compts = IID_COMPONENT_BASE|
		IID_COMPONENT_DS|
		IID_COMPONENT_AS|
		IID_COMPONENT_AUDIO|
		IID_COMPONENT_VIDEO|
		IID_COMPONENT_RECORD|
		IID_COMPONENT_CHAT|
		IID_COMPONENT_POLLING|
		IID_COMPONENT_MS|
		IID_COMPONENT_FT|
		IID_COMPONENT_WB;

	TUP_RESULT tRet = tup_conf_load_component(m_handle,compts);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_load_component failed."));
		return -1L;
	}

	tRet = tup_conf_reg_component_callback(m_handle,IID_COMPONENT_AS,NotifyCallBack::ConfComASNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_reg_component_callback AS failed."));
		return -1L;
	}
// 	//设置屏幕共享回调函数
// 	tRet = tup_conf_reg_component_callback(m_handle, IID_COMPONENT_AS, NotifyCallBack::ConfComASNotify);
// 	if(TUP_SUCCESS != tRet)
// 	{
// 		AfxMessageBox(_T("tup_conf_reg_component_callback AS failed."));
// 		return -1L;
// 	}
	if (bChairmanFlag)
	{
		//m_toShareDesk.EnableWindow(TRUE);
		m_btnShareStart.EnableWindow(FALSE);
		m_getPresent.EnableWindow(TRUE);
	}
	m_editMeetStatus.SetWindowTextW(_T("数据会议中"));

	return 0L;
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonStartShare()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_call_serverconf_transferto_dataconf(m_uiConfID);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_serverconf_transferto_dataconf failed"));
	}
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonFullScreen()
{
	// TODO: Add your control notification handler code here
}


//************************************************************************
LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnUserBeKickOut(WPARAM wParam, LPARAM lParam)
{
	if(!bLoginFlag)
		return 0L;


	if(m_handle != 0)
	{

		if(bChairmanFlag)
		{
			tup_conf_terminate(m_handle);
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}

	}


	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(bChairmanFlag)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
			if(TUP_SUCCESS == tRet)
			{
				ResourceClear();
				ListCtrlAndMapAddMember(cstrOwnAccount);
				SetShareSectionCtrl(MEET_IDLE);
			}
		}

		m_uiCallID = 0;
	}






	LogoutService();

	bChairmanFlag = false;

	m_OwnerBindNum="";
	m_LocalMenber.clear();
	m_bisPresent = false;

	m_LocalMenber.clear();
	m_uiConfID = 0;
	m_uiCallID = 0;
	bChairmanFlag = false;
	m_bisPresent = false;
	m_ChaMainAccount = "";
	m_ChairMainBindNum = "";
	m_PresentAccount = "";
	m_PresentBindNUm = "";
	m_OwnerBindNum = "";

	if (m_dlgModel==1)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;

		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=0;
	}
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}

	ResourceClear();
	bLoginFlag = false;
	cstrOwnAccount.Empty();
	m_editMeetStatus.SetWindowTextW(_T(""));
	m_editTargetAccount.SetWindowTextW(_T(""));
	KillTimer(HEART_BEAT_TIMEID);
	SetLoginSectionCtrl(true);
	SetShareSectionCtrl(MEET_INIT);
	SetLogOutSectionCtrl(false);

	//if(bChairmanFlag)
	//{
	//	//结束会议
	//	tup_call_serverconf_end(m_uiConfID);
	//}
	//else
	//{
	//	//离开会议
	//	tup_call_serverconf_leave(m_uiConfID);
	//}

	//LogoutService();
	//bChairmanFlag = false;
	//ResourceClear();
	//bLoginFlag = false;
	//cstrOwnAccount.Empty();
	//m_editMeetStatus.SetWindowTextW(_T(""));
	//m_editTargetAccount.SetWindowTextW(_T(""));
	//KillTimer(HEART_BEAT_TIMEID);
	//SetLoginSectionCtrl(true);
	//SetShareSectionCtrl(MEET_INIT);
	//SetLogOutSectionCtrl(false);
	AfxMessageBox(_T("You Are Kicked Off,Please Relogin!"));
	return 0L;
}

bool CeSDK_TUP_PC_DeskShare_DemoDlg::GetUserBindNumByid(TUP_ULONG id ,std::string& BindNum)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (id == iter->second)
		{
			BindNum = iter->first; 
			return true ;
		}
	}
	return false;
}

bool CeSDK_TUP_PC_DeskShare_DemoDlg::getAccountINfoByBingNum( std::string _phoneID, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	memset(&arg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
	memset(&ack,0,sizeof(IM_S_QUERY_USERINFO_ACK));
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _phoneID.c_str());
	arg.type = IM_E_IMUSERQUERYTYPE_BY_BINDNO;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		//AfxMessageBox(L"Query Account Failed");
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
		memset(&curUserInfo,0,sizeof(IM_S_USERINFO));
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (strcmp(curUserInfo.bindNO, _phoneID.c_str()) == 0)
		{
			_userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}
	////释放IM_S_QUERY_USERINFO_ACK结构体中的TUPLIST内存/////
	tup_im_release_tup_list(ack.userList);

	if(!bRet)
	{
		//AfxMessageBox(L"Query Account Failed");
		return false;
	}

	return true;
}



LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfASGetOwerOK(WPARAM l,LPARAM m)
{
	bool m_IsSucess = l;
	TUP_ULONG m_OwnerId = (TUP_ULONG)m;
	if (!GetUserBindNumByid(m_OwnerId,m_OwnerBindNum))
	{
		m_OwnerBindNum = "";
		return -1L;
	}
	/////查找具有共享权限的人的信息////
	IM_S_USERINFO m_OwnerInfo;
	if (!getAccountINfoByBingNum(m_OwnerBindNum,m_OwnerInfo))
	{
		return -1L;
	}
	std::string m_OwnerName = m_OwnerInfo.name;
	CString m_strname;
	//CTools::string2CString(m_OwnerName,m_strname);
	///////默认有共享权限的人是主讲人   Start/////////
	if (m_IsSucess)
	{
		if (m_bisPresent)
		{
			m_toShareDesk.EnableWindow(TRUE);
			m_getPresent.EnableWindow(FALSE);
		}
		else
		{
			m_getPresent.EnableWindow(TRUE);
		}
	}
	m_PresentBindNUm = m_OwnerInfo.bindNO;
	//{
	//	m_edtPresenter.SetWindowText(m_strname);
	//	//////检查是否是会场静音//////
	//	if (m_bisMute)
	//	{
	//		int iSize = m_DataConfMem.GetItemCount();
	//		for (int i = 0;i<iSize;i++)
	//		{
	//			if (m_OwnerInfo.bindNO == CTools::num2str(m_DataConfMem.GetItemData(i)))
	//			{
	//				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
	//				m_PresentBindNUm = m_OwnerInfo.bindNO;
	//			}
	//		}

	//	}
	//}

	///////默认有共享权限的人是主讲人   End/////////

	/*m_strname+=L"具有共享权限";
	m_stcShareState.SetWindowText(m_strname);
	InitShareButton()*/;
	if (!m_IsSucess)
	{
		/////设置没有成功//////
		//m_btnGetPresenterRole.EnableWindow(TRUE);
		if (m_bisPresent)
		{
			Sleep(1000);
			(void)tup_conf_as_set_owner(m_handle,m_OwnerId,AS_ACTION_ADD);
			//m_btnGetPresenterRole.EnableWindow(FALSE);

		}
	}

	/////默认具有共享权限的人才能更换共享模式///////
	/*if(m_OwnerId == g_UserID)
	{
	GetDlgItem(IDC_RAD_NULL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_DOC)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_WHITEBOARD)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_MEDIA)->EnableWindow(FALSE);
	}
	else
	{
	GetDlgItem(IDC_RAD_NULL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_DOC)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_WHITEBOARD)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_MEDIA)->EnableWindow(FALSE);
	}*/

	IM_S_USERINFO m_CharmanInfo;
	if (getAccountINfoByBingNum(m_ChairMainBindNum,m_CharmanInfo))
	{
		std::string m_ChairmanName = m_CharmanInfo.name;

		m_editMeetCompere.SetWindowTextW(CTools::UTF2UNICODE(m_ChairmanName.c_str()));
	}
	if (getAccountINfoByBingNum(m_PresentBindNUm,m_CharmanInfo))
	{
		std::string m_ChairmanName = m_CharmanInfo.name;

		m_editMeetSpeaker.SetWindowTextW(CTools::UTF2UNICODE(m_ChairmanName.c_str()));
	}


	return 0L;
}

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfASUpdateScreen(WPARAM,LPARAM)
{
	if (m_dlgModel==0)
	{
		CRect rcSize;
		GetWindowRect(&rcSize);

		CRect rc;
		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + DESKSHOW_WIDTH;
	    rc.bottom = rcSize.top + HEITH;
			
		
		MoveWindow(&rc,TRUE);
		ShowWindow(SW_SHOW);
		m_dlgModel=1;
	}

	TC_AS_SCREENDATA screenData;
	tup_conf_as_get_screendata(m_handle,&screenData);	

	TRACE("\nScreenData:[%d][0X%x][0X%x]\n",screenData.ucDataType,screenData.pUpdateInfo,screenData.pData);

	TC_AS_ScreenDataInfo *pInfo = (TC_AS_ScreenDataInfo*)(screenData.pUpdateInfo);
	if(NULL == pInfo)
	{
		return -1L;
	}

	if (AS_SCREENDATAFORMAT_DDB == screenData.ucDataType)
	{
		m_stcDeskTop.SetBitmap2((BITMAP*)(screenData.pData));
	}
	else if (AS_SCREENDATAFORMAT_DIB == screenData.ucDataType)
	{
		//移动终端使用此类型
	}
	else if (AS_SCREENDATAFORMAT_DC == screenData.ucDataType)
	{
		HDC hAnnotDataDC = (HDC)screenData.pData;
		BITMAP bm;
		HBITMAP hBmp = (HBITMAP)::GetCurrentObject(hAnnotDataDC, OBJ_BITMAP);
		if ( NULL == hBmp)
		{
			DWORD  nRet = GetLastError();
			TRACE("CReceViewRenderWnd::OnAsScreenData() NULL == hBmp GetLastError:%d",nRet );
		}
		(VOID)::GetObject(hBmp, sizeof(bm), &bm);
		m_stcDeskTop.SetBitmap(hBmp);
	}
	else
	{
		//to do
	}

	return 0L;
}

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::OnDataConfASStateShare(WPARAM ,LPARAM l)
{
	unsigned long ulState = (unsigned long)l;
	switch (ulState)
	{
	case AS_STATE_NULL:
		{
			m_stcDeskTop.SetBitmap2(NULL);
			if (m_bisPresent)
			{
				m_toShareDesk.EnableWindow(TRUE);
				m_btnShareEnd.EnableWindow(FALSE);
			}
			//m_stcShareState.SetWindowText(L"无人共享");
			if (m_dlgModel==1)
			{
				CRect rcSize;
				GetWindowRect(&rcSize);

				CRect rc;

				rc.left = rcSize.left;
				rc.top = rcSize.top;
				rc.right = rc.left + WIDTH;
				rc.bottom = rcSize.top + HEITH;

				MoveWindow(&rc,TRUE);
				ShowWindow(SW_SHOW);
				m_dlgModel=0;
			}
			break;
		}
	case AS_STATE_START:
	case AS_STATE_VIEW:
		{
			//m_stcShareState.SetWindowText(L"正在共享");
			if (m_bisPresent)
			{
				m_toShareDesk.EnableWindow(FALSE);
				m_btnShareEnd.EnableWindow(TRUE);
			}
			
			break;
		}
	}
	return 0L;
}

LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::UpdateChairmainInfo(WPARAM w,LPARAM l)
{

	TUP_ULONG id = TUP_ULONG(w);
	bool m_isMe = bool(l);
	IM_S_USERINFO m_CharmanInfo;

	if (m_isMe)
	{
		///从自己的登录账号查找g_BindNO
		if(!getAccountINfoByBingNum(strOwnBindNO,m_CharmanInfo))  
		{
			return -1L;
		}
		/////本地记录主持人信息/////
		m_ChairMainBindNum = strOwnBindNO;
		bChairmanFlag = true;
	} 
	else
	{
		/////查询主持人信息///////
		if (!GetUserBindNumByid(id,m_ChairMainBindNum))
		{
			return -1L;
		}

		if(!getAccountINfoByBingNum(m_ChairMainBindNum,m_CharmanInfo))  
		{
			return -1L;
		}
		if (m_ChairMainBindNum != strOwnBindNO)
		{
			bChairmanFlag = false;
		}
	}

	//////显示主持人信息/////
	m_ChaMainAccount = m_CharmanInfo.account;
	std::string m_ChairmanName = m_CharmanInfo.name;
	m_editMeetCompere.SetWindowTextW(CTools::UTF2UNICODE(m_ChairmanName.c_str()));
	m_ChairMainBindNum = m_CharmanInfo.bindNO;
	/*std::string m_ChairmanName = m_CharmanInfo.name;
	CString m_str;
	CTools::string2CString(m_ChairmanName,m_str);
	m_edtChairMan.SetWindowText(m_str);*/
	return 0L;
}


LRESULT CeSDK_TUP_PC_DeskShare_DemoDlg::UpdatePresentInfo(WPARAM w,LPARAM l)
{
	TUP_ULONG m_prePresentid = w;   ////前一个主讲人的ID
	TUP_ULONG m_Presentid = l;   ////当前主讲人的ID

	IM_S_USERINFO m_PresentInfo;

	if (m_Presentid == strOwnUserID)
	{
		////当前的主持人是自己
		///从自己的登录账号查找g_BindNO
		if (!getAccountINfoByBingNum(strOwnBindNO,m_PresentInfo))
			return  -1L;
		m_PresentBindNUm = strOwnBindNO;
		m_bisPresent = true;

		(void)tup_conf_as_set_owner(m_handle,strOwnUserID,AS_ACTION_ADD);
		m_getPresent.EnableWindow(FALSE);
		m_toShareDesk.EnableWindow(TRUE);
		/////将获取主讲权限的对话框不可用
		//m_btnGetPresenterRole.EnableWindow(FALSE);

		/////主持人或主讲人不静音/////
		//(void)tup_call_media_mute_mic(ulCallID, TUP_FALSE);
	} 
	else
	{
		////当前主持人不是自己////
		std::string m_PresentBindNum;
		if (!GetUserBindNumByid(m_Presentid,m_PresentBindNum))
		{
			return  -1L;
		}

		if(!getAccountINfoByBingNum(m_PresentBindNum,m_PresentInfo))  
		{
			return  -1L;
		}

		if (m_PresentBindNum != strOwnBindNO)
		{
			m_bisPresent = false;
			m_getPresent.EnableWindow(TRUE);
			m_toShareDesk.EnableWindow(FALSE);
		}

		/////将获取主讲权限的对话框可用
		//m_btnGetPresenterRole.EnableWindow(TRUE);

		//if(m_bisMute)
		//{
		//	if(!m_bisChairMan)
		//	{
		//		/////非主持人或者主讲人静音/////
		//		(void)tup_call_media_mute_mic(ulCallID, TUP_TRUE);
		//	}
		//}
	}
	m_PresentAccount = m_PresentInfo.account;
	std::string m_PresentName = m_PresentInfo.name;
	m_editMeetSpeaker.SetWindowTextW(CTools::UTF2UNICODE(m_PresentName.c_str()));
	m_PresentBindNUm = m_PresentInfo.bindNO;
	/*std::string m_PresentName = m_PresentInfo.name;
	CString m_str;
	CTools::string2CString(m_PresentName,m_str);
	m_edtPresenter.SetWindowText(m_str);*/

	//主讲人变更后刷新一下列表
	//UpdateMuteInfo();
	return 0L;
}

void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT  tRet = tup_conf_as_set_sharetype(m_handle,AS_SHARINGTYPE_DESKTOP);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_set_sharetype failed");
		//InitShareButton();
		return ;
	}
	tRet = tup_conf_as_start(m_handle);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_start failed");
		//InitShareButton();
		return ;
	}
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButtonEndShare()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_conf_as_stop(m_handle);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_stop failed");
		//InitShareButton();
		return ;
	}
}


void CeSDK_TUP_PC_DeskShare_DemoDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_conf_user_request_role(m_handle,CONF_ROLE_PRESENTER,"");
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("Get ROLE_PRESENTER Failed！"));
	}
	////获取共享拥有者//////
	IM_S_USERINFO m_userInfo;
	if (! getAccountINfoByBingNum(strOwnBindNO, m_userInfo))
	{
		return ;
	}

	tRet = tup_conf_as_set_owner(m_handle,m_userInfo.staffID,AS_ACTION_ADD);
	if(tRet != TC_OK)
	{
		AfxMessageBox(L"tup_conf_as_set_owner failed");
	}
}
