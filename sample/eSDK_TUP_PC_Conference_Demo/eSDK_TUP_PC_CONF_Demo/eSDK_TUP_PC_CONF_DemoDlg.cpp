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
#include "Tools.h"
#include "NotifyCallBack.h"
#include "ConferenceDetailDlg.h"
#include "NotifyCallBack.h"
#include "ConfInComing.h"

#include <string>
#include <utility>
#include <afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int HEARTBEAT_TIME = 30000;	 // ���ʱ��30��
const int HEART_BEAT_TIMEID = 1000;	 // ������ʱ��ID

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
	, m_bLoginFlag(FALSE)
	, m_bLogOff(FALSE)
	,m_strSipAccount("")
	,m_pConfDlg(NULL)
	,m_pDataConfDlg(NULL)
	,m_bInConference(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeSDK_TUP_PC_CONF_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_editIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPSD);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDX_Control(pDX, IDC_LIST1, m_listMeetingInfo);
	DDX_Control(pDX, IDC_BUTTON_APPINTMENT, m_btnMeeting);
	DDX_Control(pDX, IDC_BUTTON_GET_MEETINGLIST, m_btnGetMeeting);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_BUTTON_LOGOFF, m_btnLogoff);
}

BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_CONF_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_APPINTMENT, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonAppintment)
	ON_BN_CLICKED(IDC_BUTTON_GET_MEETINGLIST, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonGetMeetinglist)
	ON_BN_CLICKED(IDC_BUTTON_LOGOFF, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogoff)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogout)
	ON_MESSAGE(WM_USER_KICKOUT, &CeSDK_TUP_PC_CONF_DemoDlg::OnKickoutUser)
	ON_MESSAGE(WM_INTOCONF,&CeSDK_TUP_PC_CONF_DemoDlg::OnInConf)
	ON_MESSAGE(WM_LOGOUT, &CeSDK_TUP_PC_CONF_DemoDlg::OnLogoutEvent)
	ON_MESSAGE(WM_REFRESHMEMBER,&CeSDK_TUP_PC_CONF_DemoDlg::OnReshMember)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CeSDK_TUP_PC_CONF_DemoDlg::OnNMRClickList1)
	ON_COMMAND(IDR_DETAIL, &CeSDK_TUP_PC_CONF_DemoDlg::OnDetail)
	ON_COMMAND(IDR_ADD, &CeSDK_TUP_PC_CONF_DemoDlg::OnAdd)
	ON_MESSAGE(WM_CONF_INCMING, &CeSDK_TUP_PC_CONF_DemoDlg::OnConfIncming)
	ON_MESSAGE(WM_CONF_CREATE_RET, &CeSDK_TUP_PC_CONF_DemoDlg::OnConfCreateRet)
	ON_MESSAGE(WM_CLEAR_MEETING_LIST, &CeSDK_TUP_PC_CONF_DemoDlg::OnClearMeetingList)
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
	// ��ʼ����¼�Ի���
	m_editAccount.SetWindowText(_T("chenensheng02"));
	m_editPSD.SetWindowText(_T("huawei.123"));
	m_editPort.SetWindowText(_T("8011"));
	m_editIP.SetAddress(172, 22, 9, 42);
	// �����˻�����������볤��
	m_editAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_editPSD.LimitText(IM_D_MAX_PASSWORD_LENGTH);
	m_editPort.LimitText(10);
	// ���ý����ڵ�¼��ť��
	GetDlgItem(IDC_BUTTON_LOGIN)->SetFocus();

	// ����ListCtrl�ؼ����
	LONG lStyle;
	lStyle = GetWindowLong(m_listMeetingInfo.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_SINGLESEL;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listMeetingInfo.m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = m_listMeetingInfo.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES; // ������
	m_listMeetingInfo.SetExtendedStyle(dwStyle);

	m_listMeetingInfo.InsertColumn(0, _T("��ϯ"), LVCFMT_LEFT, 70);
	m_listMeetingInfo.InsertColumn(1, _T("����"), LVCFMT_LEFT, 80);
	m_listMeetingInfo.InsertColumn(2, _T("���鷽ʽ"), LVCFMT_LEFT, 90);
	m_listMeetingInfo.InsertColumn(3, _T("���鿪ʼʱ��"), LVCFMT_LEFT, 90);
	m_listMeetingInfo.InsertColumn(4, _T("����ʱ��"), LVCFMT_LEFT, 90);


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



void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	// ��ȡIP����
	UpdateData(TRUE);
	BYTE field0, field1, field2, field3;
	m_editIP.GetAddress(field0, field1, field2, field3);
	char IP[100];
	memset(IP, 0, 100);
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);

	// ��ȡ������IP�Ͷ˿�
	CString cstrPort(_T(""));
	m_editPort.GetWindowText(cstrPort);
	if (cstrPort.IsEmpty())
	{
		AfxMessageBox(_T("port is empty!"));
		return;
	}
	std::string strPort = CTools::UNICODE2UTF(cstrPort);
	int iPort = atoi(strPort.c_str());

	// ���÷�����IP�Ͷ˿�
	TUP_RESULT tRet = tup_im_setserveraddress(IP, iPort);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setserveraddress failed!"));
		return;
	}

	// ���ûص���Ϣ�ϱ�������ַ
	tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_register_callback failed!"));
		return;
	}
	
	// ʹ����Ϣ�ַ���������Ϣ�����ϱ�
	tRet = tup_im_setdispatchmessage(TUP_TRUE);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
		return;
	}

	// ��ȡ�ؼ��ϵĵ�¼�˺ź�����
	CString cstrAccount;
	CString cstrPSD;
	m_editPSD.GetWindowText(cstrPSD);
	m_editAccount.GetWindowText(cstrAccount);
	if (cstrAccount.IsEmpty() || cstrPSD.IsEmpty())
	{
		AfxMessageBox(_T("Username or password is empty!"));
		return;
	}

	IM_S_LOGIN_ARG arg;
	CTools::CString2Char(cstrAccount, arg.account, IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(cstrPSD, arg.password, IM_D_MAX_PASSWORD_LENGTH);
	arg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;

	// �汾�Ź̶�
	CString cstrVersion(_T("v1.1.11.103"));
	CTools::CString2Char(cstrVersion, arg.version, IM_D_MAX_VERSION_LENGTH);

	// ��¼UC������
	IM_S_LOGIN_ACK ack;
	tRet = tup_im_login(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		switch (ack.reason)
		{
				// ��Ϣ��ʱ
			case IM_E_LOGING_RESULT_TIMEOUT:
				{
					AfxMessageBox(_T("Message timeout!"));
					break;
				}
				// �����ڲ�����
			case IM_E_LOGING_RESULT_INTERNAL_ERROR:
				{
					AfxMessageBox(_T("Internal error!"));
					break;
				}
				// �������
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
					break;
				}
				// �˺Ų�����
			case IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST:
				{
					AfxMessageBox(_T("Account does not exist!"));
					break;
				}
				// �û��Ѵ���
			case IM_E_LOGING_RESULT_ALREADY_LOGIN:
				{
					AfxMessageBox(_T("User already exist!"));
					break;
				}
				// �ʺ�������
			case IM_E_LOGING_RESULT_ACCOUNT_LOCKED:
				{
					AfxMessageBox(_T("Account has been locked!"));
					break;
				}
				// ��Ҫ�����°汾�������¼
			case IM_E_LOGING_RESULT_NEED_NEW_VERSION:
				{
					AfxMessageBox(_T("Need to download the new version of this to allow login!"));
					break;
				}
				// �û�δ����
			case IM_E_LOGING_RESULT_NOT_ACTIVE:
				{
					AfxMessageBox(_T("User is not activated!"));
					break;
				}
				// �û��˺ű���ͣ
			case IM_E_LOGING_RESULT_ACCOUNT_SUSPEND:
				{
					AfxMessageBox(_T("User account was suspended!"));
					break;
				}
				// �û��˺Ź���
			case IM_E_LOGING_RESULT_ACCOUNT_EXPIRE:
				{
					AfxMessageBox(_T("User account expired!"));
					break;
				}
				// ��Ϣ����ʧ��
			case IM_E_LOGING_RESULT_DECRYPT_FAILED:
				{
					AfxMessageBox(_T("Message decryption failed!"));
					break;
				}
				// ֤������ʧ��
			case IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED:
				{
					AfxMessageBox(_T("Certificate download failed!"));
					break;
				}
				// ֤��У��ʧ��
			case IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED:
				{
					AfxMessageBox(_T("Certificate validation failed!"));
					break;
				}
				// ������������
			case IM_E_LOGING_RESULT_DNS_ERROR:
				{
					AfxMessageBox(_T("Domain name resolution error!"));
					break;
				}
			default:break;
		}
		return;
	}
	LoginCallService();
	EnableRelativeControl();
	m_bLoginFlag = TRUE;// ��¼�ɹ���ΪTRUE
	m_btnLogoff.EnableWindow(TRUE);
	SetTimer(HEART_BEAT_TIMEID, HEARTBEAT_TIME, NULL);

	//m_editAccount.GetWindowText(cstrAccount);
	theApp.m_Account = CTools::UNICODE2UTF(cstrAccount);
	//m_SipAccount =  serviceAck.sipAccount;

	IM_S_QUERY_USERINFO_ARG accountArg;
	IM_S_QUERY_USERINFO_ACK accountAck;
	memset(&accountArg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
	memset(&accountAck,0,sizeof(IM_S_QUERY_USERINFO_ACK));
	strcpy_s(accountArg.key, IM_D_MAX_ACCOUNT_LENGTH, theApp.m_Account.c_str());
	accountArg.type = IM_E_IMUSERQUERYTYPE_BY_ACCOUNT;
	tRet = tup_im_queryuserinfo(&accountArg, &accountAck);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_queryuserinfo failed!"));
		return;
	}

	memcpy(&m_CurrentUserInfo, (IM_S_USERINFO*)(accountAck.userList->data), sizeof(IM_S_USERINFO));
	theApp.m_BindNO = m_CurrentUserInfo.bindNO;
}

bool CeSDK_TUP_PC_CONF_DemoDlg::LoginCallService(void)
{
	BYTE field0, field1, field2, field3;
	m_editIP.GetAddress(field0, field1, field2, field3);
	char IP[100];
	memset(IP, 0, 100);
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);
	IM_S_GETSERVICEPROFILEARG serviceArg = {0};
	serviceArg.isSyncAll = TUP_TRUE;
	serviceArg.isVpnAccess = TUP_FALSE;
	serviceArg.needIcon = TUP_TRUE;
	std::string LocalIPAddr;
	if (!CTools::GetBestHostip(LocalIPAddr,IP))
	{
		return false;
	}
	strncpy_s(serviceArg.localIP, IM_D_IP_LENGTH*sizeof(TUP_CHAR), LocalIPAddr.c_str(),_TRUNCATE);
	strncpy_s(serviceArg.timestamp, IM_D_MAX_TIMESTAMP_LENGTH*sizeof(TUP_CHAR), "19000000000000",_TRUNCATE);

	//��ȡҵ�����
	IM_S_SERVICEPROFILEACK serviceAck = {0};
	TUP_RESULT tRet = tup_im_getserviceprofile(&serviceArg, &serviceAck);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getserviceprofile failed"));
		return false;
	}
	////�ӷ����������ļ��л�ȡԤԼ����ĵ�ַ c003287158 2015-11-27 Start/////
	m_cstrMettingUrl = CTools::UTF2UNICODE(serviceAck.eConsoleAddr);
	////�ӷ����������ļ��л�ȡԤԼ����ĵ�ַ c003287158 2015-11-27 End/////
	m_strConfServerAddress = serviceAck.dataConfAddrs ;
	m_strSipAccount = serviceAck.sipAccount;
	//���ú��лص�����
	tRet = tup_call_register_process_notifiy(NotifyCallBack::CallNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_register_process_notify failed"));
		return false;
	}

	//���ô���ģʽ
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

	//���ú���ע�������
	CALL_S_SERVER_CFG sipServerCfg;
	memset(&sipServerCfg,0,sizeof(CALL_S_SERVER_CFG));
	strncpy_s(sipServerCfg.server_address, CALL_D_MAX_URL_LENGTH, ip.c_str(),_TRUNCATE);
	sipServerCfg.server_port = (TUP_UINT32)iServerPort;
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_REG_PRIMARY failed."));
		return false;
	}

	memset(&sipServerCfg, 0, sizeof(sipServerCfg));
	strncpy_s(sipServerCfg.server_address, CALL_D_MAX_URL_LENGTH, ip.c_str(),_TRUNCATE);
	sipServerCfg.server_port = iServerPort;
	//���ú��д��������,һ���ע���������ͬ
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_PROXY_PRIMARY, &sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_PROXY_PRIMARY failed."));
		return false;
	}

	//�����û�����
	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_USEAGENT, USER_AGENT);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_USEAGENT failed."));
		return false;
	}

	//���ú����ն�����
	CALL_E_PRODUCT_TYPE eProductType = CALL_E_PRODUCT_TYPE_PC;
	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_PRODUCT_TYPE, (TUP_VOID*)&eProductType);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_PRODUCT_TYPE failed."));
		return false;
	}

	//���ñ��ص�ַ
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
	//����ע������
	tRet = tup_call_register(sipAccount.c_str(), sipUserName.c_str(), serviceAck.sipPassword);		//�û�����SIP�˻��������¼Call��������
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_register failed."));
		return false;
	}
	//////�ͷ�tup_im_getserviceprofile�ṹ��ָ��/////
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


void CeSDK_TUP_PC_CONF_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	// ��ʱ�����������������Ϣ
	if (HEART_BEAT_TIMEID == nIDEvent)
	{
		// ������������
		TUP_RESULT tRet = tup_im_sendheartbeat();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_sendheartbeat failed!"));
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonAppintment()
{
	// TODO: Add your control notification handler code here
	if (m_cstrMettingUrl.IsEmpty())
	{
		AfxMessageBox(_T("Open Appointment  URL Failed"));
		return;
	}

	CTools::OpenURL(m_cstrMettingUrl);
	/*==============
	//����һ����������
	//TUP_UINT32 uiConfID;
	//TUP_UINT32 uiCallID;
	//TUP_RESULT tRet = tup_call_serverconf_create(&uiConfID, &uiCallID, "");
	//if (TUP_SUCCESS != tRet)
	//{
		//AfxMessageBox(_T("tuo_call_serverconf_create failed!"));
		//return;
	//}
	==============*/
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonGetMeetinglist()
{
	// TODO: Add your control notification handler code here
	m_listMeetingInfo.DeleteAllItems();
	m_ConferenceList.clear();
	IM_S_GETCONFERENCELISTARG conferenceArg = {0};
	conferenceArg.count = 10;
	conferenceArg.pageNo = 1;
	IM_S_GETCONFERENCELISTACK conferenceAck = {0};
	TUP_RESULT tRet = tup_im_GetConferenceList(&conferenceArg, &conferenceAck);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("You have no conf to attend!"));
		return;
	}

	TUP_S_LIST *meetingList = conferenceAck.meetingList;
	if (NULL == meetingList) return;
	IM_S_MEETINGINFO *meetingInfo = (IM_S_MEETINGINFO*)(meetingList->data);

	int i = 0;
	while (meetingList)
	{
		meetingInfo = (IM_S_MEETINGINFO *)(meetingList->data);
		if (NULL == meetingInfo) break;
		int itemIndex = 0;
		// ��ϯ����
		std::wstring wstrTemp = CTools::string2wstring(std::string(meetingInfo->chairman));
		m_listMeetingInfo.InsertItem(i, wstrTemp.c_str());
		// ����
		wstrTemp = CTools::string2wstring(std::string(meetingInfo->subject));
		m_listMeetingInfo.SetItemText(i, ++itemIndex, wstrTemp.c_str());
		// ��������
		wstrTemp = CTools::string2wstring(std::string(meetingInfo->mediaType));
		int iResult = _wcsicmp(wstrTemp.c_str(), _T("100"));
		if (iResult == 0)
		{
			m_listMeetingInfo.SetItemText(i, ++itemIndex, _T("��������"));
		}
		iResult = _wcsicmp(wstrTemp.c_str(), _T("111"));
		if (iResult == 0)
		{
			m_listMeetingInfo.SetItemText(i, ++itemIndex, _T("��ý�����"));
		}
		// ���鿪ʼʱ��
		wstrTemp = CTools::string2wstring(meetingInfo->startTime);
		m_listMeetingInfo.SetItemText(i, ++itemIndex, wstrTemp.c_str());
		// ����ʱ��
		wstrTemp = CTools::string2wstring(meetingInfo->duration);
		m_listMeetingInfo.SetItemText(i, ++itemIndex, wstrTemp.c_str());
		// ����map����
		m_ConferenceList.insert(std::make_pair<int, IM_S_MEETINGINFO>(i, *meetingInfo));
		++i;
		meetingList = meetingList->next;
	}
}
//************************************************************************
void CeSDK_TUP_PC_CONF_DemoDlg::EnableRelativeControl()
{
	m_editAccount.EnableWindow(FALSE);
	m_editIP.EnableWindow(FALSE);
	m_editPort.EnableWindow(FALSE);
	m_editPSD.EnableWindow(FALSE);
	m_btnLogin.EnableWindow(FALSE);
	m_btnMeeting.EnableWindow(TRUE);
	m_btnGetMeeting.EnableWindow(TRUE);
}
//************************************************************************
void CeSDK_TUP_PC_CONF_DemoDlg::DisableRelativeControl()
{
	m_editAccount.EnableWindow(TRUE);
	m_editIP.EnableWindow(TRUE);
	m_editPort.EnableWindow(TRUE);
	m_editPSD.EnableWindow(TRUE);
	m_btnLogin.EnableWindow(TRUE);
	m_btnMeeting.EnableWindow(FALSE);
	m_btnGetMeeting.EnableWindow(FALSE);
}

void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogoff()
{
	// TODO: Add your control notification handler code here
	m_listMeetingInfo.DeleteAllItems();
	if (m_bLoginFlag)
	{
		// ����ע����ť��ֻ�˳������������˳��Ի���
		m_bLogOff = TRUE;
		
		// ȡ���ײ�ģ����δ�������Ϣ����
		TUP_RESULT tRet = tup_im_setcancelsendingmessage();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
		}

		// ע��UC�������ĵ�¼
		tRet = tup_im_logout();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_logout failed!"));
		}
	    tRet = tup_call_deregister(m_strSipAccount.c_str());	//SIP�˺�ע��
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(_T("tup_call_deregister failed."));
		}

		// ������ؿؼ�
		DisableRelativeControl();
		// ���ý���
		m_btnLogin.SetFocus();

		m_bLoginFlag = FALSE;// ���õ�¼״̬
		m_btnLogoff.EnableWindow(FALSE);// ����ע����ť
	}
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	if (m_bLoginFlag)
	{
		// ȡ���ײ�ģ����δ�������Ϣ����
		TUP_RESULT tRet = tup_im_setcancelsendingmessage();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
		}
		// ע��UC�������ĵ�¼
		tRet = tup_im_logout();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_logout failed!"));
		}
		tRet = tup_call_deregister(m_strSipAccount.c_str());		//SIP�˺�ע��
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(_T("tup_call_deregister failed."));
		}
		//::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);// �򴰿ڷ���WM_CLOSE��Ϣ
	}
	else
	{
		::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);// �򴰿ڷ���WM_CLOSE��Ϣ
	}
}
//************************************************************************
LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnLogoutEvent(WPARAM wParam, LPARAM lParam)
{
	// �ر��ϱ���Ϣ���û��˳���¼ʱ����
	if (m_bLoginFlag)
	{
		TUP_RESULT tRet = tup_im_setdispatchmessage(TUP_FALSE);
		if (tRet == TUP_FAIL)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
		}
	}

	if (!m_bLogOff)
	{
		// ���µ���ע����ť���򲻷��͹ر���Ϣ
		::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
	}

	m_bLogOff = FALSE;
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnKickoutUser(WPARAM wParam, LPARAM lParam)
{
	// ȡ���ײ�ģ����δ�������Ϣ����
	TUP_RESULT tRet = tup_im_setcancelsendingmessage();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
	}
	// ע��UC��������¼
	tRet = tup_im_logout();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_logout failed!"));
		return -1L;
	}

	m_bLogOff = TRUE;// ������ΪTRUE�� ��������ʱ���˳��Ի���
	if (NULL == theApp.m_pMainDlg)
	{
		return -1L;
	}
	HWND hwndModel = theApp.m_pMainDlg->m_pConfDlg->GetSafeHwnd();
	if ( NULL != hwndModel )
	{
		::SendMessage(hwndModel, WM_CLOSE, 0, 0);
	}

	hwndModel = theApp.m_pMainDlg->m_pDataConfDlg->GetSafeHwnd();
	if ( NULL != hwndModel )
	{
		::SendMessage(hwndModel, WM_CLOSE, 0, 0);
	}

	// ��ʾ�û��������ߣ����µ�¼
	AfxMessageBox(_T("Kicked Off, Please Relogin!"));
	// ������ؿؼ�
	DisableRelativeControl();
	// ���List�ؼ�
	m_listMeetingInfo.DeleteAllItems();
	return 0L;
}

void CeSDK_TUP_PC_CONF_DemoDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	// ��ֹ�ڿհ�����������˵�
	if (m_listMeetingInfo.GetSelectedCount() <= 0)
	{
		return;
	}

	CPoint hitPt;
	::GetCursorPos(&hitPt);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	if ( NULL == menu.m_hMenu )
	{
		AfxMessageBox(_T("Load menu fail"));
	}
	else
	{
		CMenu *pop = menu.GetSubMenu(0);
		if ( NULL != pop )
		{
			if ( true == m_bInConference )
			{
				pop->EnableMenuItem(IDR_ADD,MF_GRAYED);			
			}
			else
			{
				pop->EnableMenuItem(IDR_ADD,MF_BYCOMMAND);
			}
			//menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, hitPt.x, hitPt.y, this);
			pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, hitPt.x, hitPt.y, this);
		}
	}
	*pResult = 0;
}
//************************************************************************
void CeSDK_TUP_PC_CONF_DemoDlg::OnDetail()
{
	// TODO: Add your command handler code here
	int nRow = m_listMeetingInfo.GetNextItem(-1, LVIS_SELECTED);
	CConferenceDetailDlg detailDlg;
	for (std::map<int, IM_S_MEETINGINFO>::iterator item = m_ConferenceList.begin(); item != m_ConferenceList.end(); ++item)
	{
		int nNum = item->first;
		if (nNum == nRow)
		{
			CString cstrTemp;
			// ����ID
			std::wstring wstrTemp = CTools::string2wstring(std::string(item->second.id));
			detailDlg.m_cstrID = wstrTemp.c_str();
			// ��������
			wstrTemp = CTools::string2wstring(std::string(item->second.subject));
			detailDlg.m_cstrTitle = wstrTemp.c_str();
			// ����ʱ��
			wstrTemp = CTools::string2wstring(std::string(item->second.duration));
			detailDlg.m_cstrDuration = wstrTemp.c_str();
			// ���鿪ʼʱ��
			wstrTemp = CTools::string2wstring(std::string(item->second.startTime));
			detailDlg.m_cstrStart = wstrTemp.c_str();
			// ����״̬
			CTime tm = CTime::GetCurrentTime();
			CString cstrStatus;
			cstrStatus.Format(_T("%d-%.2d-%.2d %.2d:%.2d"), tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute());
			int nStatus = cstrStatus.Compare(detailDlg.m_cstrStart);
			if (nStatus < 0)
			{
				detailDlg.m_cstrStatus = _T("������δ�ٿ�");
			}
			else
			{
				detailDlg.m_cstrStatus = _T("���������ٿ�");
			}
			// �������ʱ��
			int iTime = ((item->second.holdTime) / 1000) / 60;
			cstrTemp.Format(_T("%d ����"), iTime);
			detailDlg.m_cstrHoldTime = cstrTemp;
			// �����ټ����˺�
			wstrTemp = CTools::string2wstring(std::string(item->second.convenerAccount));
			detailDlg.m_cstrConvenerAccount = wstrTemp.c_str();
			// �����ټ�������
			wstrTemp = CTools::string2wstring(std::string(item->second.convenerName));
			detailDlg.m_cstrConvenerName = wstrTemp.c_str();
			// �Ƿ���ת������
			int nForward = item->second.isForward;
			if (nForward == 0)
				detailDlg.m_cstrIsForward = _T("��ת������");
			else if (nForward == 1)
				detailDlg.m_cstrIsForward = _T("ת������");
			// ת���������˺�
			wstrTemp = CTools::string2wstring(std::string(item->second.forwarderAccount));
			detailDlg.m_cstrForwarderAccount = wstrTemp.c_str();			
			// �������
			wstrTemp = CTools::string2wstring(std::string(item->second.agenda));
			detailDlg.m_cstrAgenda = wstrTemp.c_str();
			// ���������
			wstrTemp = CTools::string2wstring(std::string(item->second.accessNumber));
			detailDlg.m_cstrAccessNumber = wstrTemp.c_str();
			detailDlg.m_cstrAccessNumber.Remove(_T('|'));
			// ���鰲ȫ��
			wstrTemp = CTools::string2wstring(std::string(item->second.securityCode));
			detailDlg.m_cstrSecurityCode = wstrTemp.c_str();
			// �ټ���Ԥ������ʱ��ʱ��
			wstrTemp = CTools::string2wstring(std::string(item->second.convenerTimezone));
			detailDlg.m_cstrConvenerTimeZone = wstrTemp.c_str();
			// ������ϯ����
			wstrTemp = CTools::string2wstring(std::string(item->second.chairman));
			detailDlg.m_cstrChairman = wstrTemp.c_str();
			// ������ϯ�˺�
			wstrTemp = CTools::string2wstring(std::string(item->second.chairmanAccount));
			detailDlg.m_cstrChairmanAccount = wstrTemp.c_str();
			// ����᳡
			wstrTemp = CTools::string2wstring(std::string(item->second.meetingroom));
			detailDlg.m_cstrMeetingRoom = wstrTemp.c_str();
			// ������Ļ��������
			wstrTemp = CTools::string2wstring(std::string(item->second.translateAccessNumber));
			detailDlg.m_cstrTranslateAccessNumber = wstrTemp.c_str();
			// ý������
			wstrTemp = CTools::string2wstring(std::string(item->second.mediaType));
			int nType = _wcsicmp(wstrTemp.c_str(), _T("100"));
			if (nType == 0)
				detailDlg.m_cstrMediaType = _T("��������");
			nType = _wcsicmp(wstrTemp.c_str(), _T("111"));
			if (nType == 0)
				detailDlg.m_cstrMediaType = _T("��ý�����");
			UpdateData(FALSE);
			detailDlg.DoModal();
		}
	}
}
void CeSDK_TUP_PC_CONF_DemoDlg::OnAdd()
{
	// TODO: Add your command handler code here
	//////һ�����/////
	//1.��ȡѡ�еĻ�����Ϣ////
 	HWND hwndParent = theApp.m_pMainWnd->GetSafeHwnd();
	int nRow = m_listMeetingInfo.GetNextItem(-1, LVIS_SELECTED);
	IM_S_MEETINGINFO m_meetingINfo = m_ConferenceList[nRow];
	/////��ȡ�����룺�����+�����+*+��������+#//////
	std::string m_accessCode("");
	///////accessNumber������һ����|����Ҫɾ����/////
	for (int i = 0;i < strlen(m_meetingINfo.accessNumber);i++)
	{
		if (isdigit(m_meetingINfo.accessNumber[i]))
		{
			m_accessCode = m_accessCode + m_meetingINfo.accessNumber[i];
		}
	}

	//�������������
	std::string strMediaType = m_meetingINfo.mediaType;

	m_accessCode = m_accessCode + m_meetingINfo.id + "*"  + m_meetingINfo.securityCode + "#";
	TUP_UINT32 m_callid = 0;
	TUP_RESULT tRet = tup_call_serverconf_access_reservedconf(&m_callid,m_accessCode.c_str());  //����ԤԼ����
	if (tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("Attend Conf Failed"));
		return ;
	}
	if ( "100" == strMediaType )
	{
		if(NULL == m_pConfDlg)
		{
			m_pConfDlg = new ConfDlg();
		}
		if(!IsWindow(m_pConfDlg->GetSafeHwnd()))
		{
			//m_pConfDlg->Create(ConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
			m_pConfDlg->Create(ConfDlg::IDD,CWnd::FromHandle(hwndParent));
		}
		if ( NULL != m_pConfDlg->m_hWnd )
		{
			m_pConfDlg->ShowWindow(SW_SHOW);
			//m_pConfDlg->SetCallID( m_callid, m_meetingINfo.subject );
			m_pConfDlg->SetCallID( m_callid, "" );
			CString cstrAccount; 
			m_editAccount.GetWindowText(cstrAccount);
			m_pConfDlg->m_strAccount.SetWindowText(cstrAccount);
			m_bInConference = true;
		}
		else
		{
			AfxMessageBox(_T("Create Conference dialog failed"));
			return;
		}
	}
	//��������ݻ���
	else if ( "111" == strMediaType )
	{
		if ( NULL == m_pDataConfDlg->GetSafeHwnd() )
		{
			m_pDataConfDlg = new CDataConfDlg();
		}
		if(!IsWindow(m_pDataConfDlg->GetSafeHwnd()))	//�ж�һ�������Ƿ����
		{
			//m_pConfDlg->Create(ConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
			m_pDataConfDlg->Create(CDataConfDlg::IDD,CWnd::FromHandle(hwndParent));
		}
		if ( NULL != m_pDataConfDlg->GetSafeHwnd() )
		{
			m_pDataConfDlg->ShowWindow(SW_SHOW);
			m_pDataConfDlg->SetCallId(m_callid);
			CString cstrAccount; 
			m_editAccount.GetWindowText(cstrAccount);
			m_pDataConfDlg->m_txtAccountName.SetWindowText(cstrAccount);
			m_bInConference = true;
		}
		else
		{
			AfxMessageBox(_T("Create data Conference dialog failed"));
			return;
		}
	}

}

void CeSDK_TUP_PC_CONF_DemoDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void CeSDK_TUP_PC_CONF_DemoDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if ( NULL != m_pConfDlg )
	{
		delete m_pConfDlg;
		m_pConfDlg = NULL;
	}
	if ( NULL != m_pDataConfDlg )
	{
		delete m_pDataConfDlg;
		m_pDataConfDlg = NULL;
	}
	CDialogEx::OnCancel();
}

LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnInConf(WPARAM wParam, LPARAM lParam)
{
	/////�������״̬/////
	CALL_S_CONF_BETRANSFERTOCONF* pNotify = (CALL_S_CONF_BETRANSFERTOCONF*)wParam;
	if ( NULL != pNotify )
	{
		if ( CALL_E_SERVERCONF_AUDIO == pNotify ->eConfType )
		{
			if ( NULL != m_pConfDlg->GetSafeHwnd() )
			{
				if(NULL == pNotify || m_pConfDlg->GetCallID() != pNotify->ulCallID)
				{
					pNotify = NULL;
					return -1L;
				}
				m_pConfDlg->SetConfPara(pNotify->acGroupUri,pNotify->ulConfID);
				m_pConfDlg->SetConfType(pNotify->eConfType);
			}
		}
		else if ( CALL_E_SERVERCONF_DATA == pNotify ->eConfType )
		{
			if ( NULL != m_pDataConfDlg->GetSafeHwnd() )
			{
				if( NULL == pNotify || m_pDataConfDlg->GetCallId() != pNotify->ulCallID )
				{
					pNotify = NULL;
					return -1L;
				}
				m_pDataConfDlg->SetCallId(pNotify->ulConfID);
			}
		}
		pNotify = NULL;
	}
	return 0L;
}
LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnReshMember(WPARAM wParam, LPARAM lParam)
{
	if ( NULL != m_pConfDlg )
	{
		if ( NULL != m_pConfDlg->GetSafeHwnd() )
		{
			m_pConfDlg->RefreshMember((CALL_S_CONF_MEMBER*)wParam,(TUP_UINT32)lParam);
		}
	}
	if ( NULL != m_pDataConfDlg )
	{
		if ( NULL != m_pDataConfDlg->GetSafeHwnd() )
		{
			m_pDataConfDlg->RefreshMember((CALL_S_CONF_MEMBER*)wParam,(TUP_UINT32)lParam);
		}
	}
	return 0L;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnConfIncming(WPARAM wParam, LPARAM lParam)
{
	if ( true == m_bInConference )
	{
		return -1L;
	}
	CALL_S_CONF_INFO *notifyInfo = (CALL_S_CONF_INFO*)wParam;
	if (NULL == notifyInfo) return -1L;
	TUP_UINT32 uiCallID = notifyInfo->ulCallID;
	TUP_UINT32 uiConfID = notifyInfo->ulConfID;
	CALL_E_SERVERCONF_TYPE uiConfType = notifyInfo->eConfType ;
	TUP_RESULT tRet = TUP_FAIL;

	IM_S_USERINFO userInfo;
	getAccountINfoByBingNum(std::string(notifyInfo->acUserNumber), userInfo);

	CConfInComing IncomingDlg;
	IncomingDlg.m_strNum = CTools::UTF2UNICODE(std::string(notifyInfo->acUserNumber));
	IncomingDlg.m_strName = CTools::UTF2UNICODE(std::string(userInfo.name));
	int nResult = IncomingDlg.DoModal();
	if (IDOK == nResult)
	{
		//IM_S_MEETINGINFO meetingINfo = m_ConferenceList[0];
		tRet = tup_call_serverconf_accept(notifyInfo->ulConfID);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_serverconf_accept failed!"));
		}
		if ( CALL_E_SERVERCONF_AUDIO == notifyInfo->eConfType )
		{
			if(NULL == m_pConfDlg)
			{
				m_pConfDlg = new ConfDlg();
			}
			if(!IsWindow(m_pConfDlg->GetSafeHwnd()))
			{
				HWND hwndParent = theApp.m_pMainWnd->GetSafeHwnd();
				m_pConfDlg->Create(ConfDlg::IDD,CWnd::FromHandle(hwndParent));
			}
			if ( NULL != m_pConfDlg->m_hWnd )
			{
				m_pConfDlg->ShowWindow(SW_SHOW);
				std::string strTemp = "";
				m_pConfDlg->SetCallID( uiCallID, strTemp);
				m_pConfDlg->SetConfPara ("",notifyInfo->ulConfID);
				m_pConfDlg->SetConfType(uiConfType);
				CString cstrAccount; 
				m_editAccount.GetWindowText(cstrAccount);
				m_pConfDlg->m_strAccount.SetWindowText(cstrAccount);
				m_bInConference = true;
			}
		}
		else if( CALL_E_SERVERCONF_DATA == notifyInfo->eConfType )
		{
			if ( NULL == m_pDataConfDlg->GetSafeHwnd() )
			{
				m_pDataConfDlg = new CDataConfDlg();
			}
			if(!IsWindow(m_pDataConfDlg->GetSafeHwnd()))	//�ж�һ�������Ƿ����
			{
				HWND hwndParent = theApp.m_pMainWnd->GetSafeHwnd();
				m_pDataConfDlg->Create(CDataConfDlg::IDD,CWnd::FromHandle(hwndParent));
			}
			if ( NULL != m_pDataConfDlg->GetSafeHwnd() )
			{
				m_pDataConfDlg->ShowWindow(SW_SHOW);
				m_pDataConfDlg->SetCallId(uiCallID);
				CString cstrAccount; 
				m_editAccount.GetWindowText(cstrAccount);
				m_pDataConfDlg->m_txtAccountName.SetWindowText(cstrAccount);
				m_bInConference = true;
			}
			else
			{
				AfxMessageBox(_T("Create data Conference dialog failed"));
			}
		}
	}
	else
	{
		tRet = tup_call_serverconf_end(notifyInfo->ulConfID);
	}
	notifyInfo = NULL;
	return 0;
}

BOOL CeSDK_TUP_PC_CONF_DemoDlg::getAccountINfoByBingNum(std::string _phoneID, IM_S_USERINFO& _userInfo)
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
		AfxMessageBox(L"Query Account Failed");
		return FALSE;
	}

	BOOL bRet = FALSE;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if( NULL != pUser)
		{
			IM_S_USERINFO curUserInfo;
			memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

			//accurate search
			if (strcmp(curUserInfo.bindNO, _phoneID.c_str()) == 0)
			{
				_userInfo = curUserInfo;
				bRet = TRUE;
				break;
			}
		}

		pUserList = pUserList->next;
	}
	/////�ͷ�IM_S_QUERY_USERINFO_ACK��TUPLISTָ��////
	tup_im_release_tup_list(ack.userList);

	if(!bRet)
	{
		AfxMessageBox(L"Query Account Failed");
		return FALSE;
	}

	return TRUE;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnConfCreateRet(WPARAM wParam, LPARAM lParam)
{
	//TRACE0("CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfCreate\n");
	HWND hwndParent = theApp.m_pMainWnd->GetSafeHwnd();
	//TUP_UINT32 m_callid = 0;
	CALL_S_CONF_CREATE_RESULT *result = (CALL_S_CONF_CREATE_RESULT*)wParam;
	TUP_UINT32 uiCallConfID = result->ulConfID;
	CALL_E_SERVERCONF_TYPE uiConfType = result->eConfType;
	if (TUP_SUCCESS == result->ulResult)
	{
		if(NULL == m_pConfDlg)
		{
			m_pConfDlg = new ConfDlg();
		}
		if(!IsWindow(m_pConfDlg->GetSafeHwnd()))
		{
			//m_pConfDlg->Create(ConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
			m_pConfDlg->Create(ConfDlg::IDD,CWnd::FromHandle(hwndParent));
		}
		if ( NULL != m_pConfDlg->m_hWnd )
		{
			m_pConfDlg->ShowWindow(SW_SHOW);
			m_pConfDlg->SetConfPara("Conference",uiCallConfID);
			m_pConfDlg->SetConfType(uiConfType);
		}
	}
	else
	{
		AfxMessageBox(_T("Create conference failed!"));
	}
	result = 0;
	return 0;
}


LRESULT CeSDK_TUP_PC_CONF_DemoDlg::OnClearMeetingList(WPARAM wParam, LPARAM lParam)
{
	m_listMeetingInfo.DeleteAllItems();
	return 0;
}


bool CeSDK_TUP_PC_CONF_DemoDlg::getAccountInfo(std::string _KeyWord, IM_E_IMUSERQUERYTYPE _ImUserQueryType, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	memset(&arg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
	memset(&ack,0,sizeof(IM_S_QUERY_USERINFO_ACK));
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _KeyWord.c_str());
	arg.type = _ImUserQueryType;
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
		if(NULL != pUser)
		{
			//IM_S_USERINFO curUserInfo;
			//memset(&curUserInfo,0,sizeof(IM_S_USERINFO));
			//memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

			//accurate search
			switch (_ImUserQueryType)
			{
				case IM_E_IMUSERQUERYTYPE_BY_PHONE:
					{
						if (strcmp(pUser->ipPhone, _KeyWord.c_str()) == 0)
						{
							//_userInfo = curUserInfo;
							//memcpy(&_userInfo, &curUserInfo, sizeof(IM_S_USERINFO));
							bRet = true;
						}
						break;
					}
				case IM_E_IMUSERQUERYTYPE_BY_ACCOUNT:
					{
						if (strcmp(pUser->account, _KeyWord.c_str()) == 0)
						{
							//_userInfo = curUserInfo;
							bRet = true;
						}
						break;
					}
				case IM_E_IMUSERQUERYTYPE_BY_BINDNO:
					{
						if (strcmp(pUser->bindNO, _KeyWord.c_str()) == 0)
						{
							//_userInfo = curUserInfo;
							bRet = true;
						}
						break;
					}
				case IM_E_IMUSERQUERYTYPE_BY_EMAIL:
					{
						if (strcmp(pUser->email, _KeyWord.c_str()) == 0)
						{
							//_userInfo = curUserInfo;
							bRet = true;
						}
						break;
					}
				case IM_E_IMUSERQUERYTYPE_BY_STAFFNO:
					{
						if (strcmp(pUser->staffNO, _KeyWord.c_str()) == 0)
						{
							//_userInfo = curUserInfo;
							bRet = true;
						}
						break;
					}
				default:
					{
						break;
					}
			}
			if (true == bRet)
			{
				memcpy(&_userInfo, pUser, sizeof(IM_S_USERINFO));
				break;
			}
		}
		pUserList = pUserList->next;
	}
	////�ͷ�IM_S_QUERY_USERINFO_ACK�ṹ���е�TUPLIST�ڴ�/////
	tup_im_release_tup_list(ack.userList);

	if(false == bRet)
	{
		//AfxMessageBox(L"Query Account Failed");
		return false;
	}
	return true;
}
