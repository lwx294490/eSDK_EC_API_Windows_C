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


// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_IM_Demo.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include "NotifyCallBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// LoginDlg dialog




CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	,m_bLoginFlag(false)
	,m_cstrAccount(L"")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipCtrlServerIP);
	DDX_Control(pDX, IDC_EDIT1, m_edtServerPort);
	DDX_Control(pDX, IDC_EDIT3, m_edtLoginAccount);
	DDX_Control(pDX, IDC_EDIT2, m_edtPWD);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN_BUTTON, &CLoginDlg::OnBnClickedLoginButton)
END_MESSAGE_MAP()


// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog()
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
	//登录对话框初始化
	m_ipCtrlServerIP.SetAddress(172, 22, 9, 42);
	m_edtServerPort.SetWindowText(L"8011");
	m_edtLoginAccount.SetWindowText(L"chenensheng01");
	m_edtPWD.SetWindowText(L"1qaz@WSX");
	//设置窗口标题
	SetWindowText(L"IMDEMO");

	//////限制输入用户名、密码长度 c00327158 Start///////
	m_edtLoginAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_edtPWD.LimitText(IM_D_MAX_PASSWORD_LENGTH);
	m_edtServerPort.LimitText(10);
	//////限制输入用户名、密码长度 c00327158 End///////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLoginDlg::OnPaint()
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
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLoginDlg::OnBnClickedLoginButton()
{
	// TODO: Add your control notification handler code here

//获取控件上IP数据
	BYTE field0, field1, field2, field3;
	m_ipCtrlServerIP.GetAddress(field0, field1, field2, field3);
	char IP[100] = {0};
	sprintf_s(IP,"%d.%d.%d.%d",field0,field1,field2,field3);
//获取控件上端口数据
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
	TUP_RESULT tRet = tup_im_setserveraddress(IP,iPort);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_setserveraddress Failed!");
		return ;
	}
//设置IM部分回调消息上报的函数地址
	tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_register_callback Failed!");
	}
//使能消息分发，否则消息不会上报
	tRet = tup_im_setdispatchmessage(TUP_TRUE);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
		return;
	}

//获取控件上的登录账号、密码
	CString account;
	CString cstrpwd;
	m_edtPWD.GetWindowText(cstrpwd);
	m_edtLoginAccount.GetWindowText(account);
	if (account.IsEmpty() || cstrpwd.IsEmpty())
	{
		AfxMessageBox(_T("Username or password is empty!"));
		return;
	}

	IM_S_LOGIN_ARG arg;
	CTools::CString2Char(account,arg.account,IM_D_MAX_ACCOUNT_LENGTH);
	CTools::CString2Char(cstrpwd,arg.password,IM_D_MAX_PASSWORD_LENGTH);
	arg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;
//版本号固定
	CString cstrversion=L"v1.1.11.103";
	CTools::CString2Char(cstrversion,arg.version,IM_D_MAX_VERSION_LENGTH);
//登录UC服务器
	IM_S_LOGIN_ACK ack;
	tRet = tup_im_login(&arg,&ack);
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
		//UC服务器登录成功
		m_bLoginFlag = true;
		m_edtLoginAccount.GetWindowText(m_cstrAccount);
		g_Account = CTools::UNICODE2UTF(m_cstrAccount);

		OnOK();
	}
}



BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(VK_RETURN == nVirtKey)
		{
			OnBnClickedLoginButton();
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
