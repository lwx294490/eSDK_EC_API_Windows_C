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

// CeSDK_TUP_PC_CALL_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_CALL_Demo.h"
#include "eSDK_TUP_PC_CALL_DemoDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include "NotifyCallBack.h"

#define CALL_CONNECTED_TIME (1*1000)
#define HEARTBEAT_TIME (30*1000)
const int HEART_BEAT_TIMEID = 1000;
const int CALL_CONNECTED_TIME_ID = 2000;
const int VOLUME_LOWER = 0;
const int VOLUME_UPPER = 100;
// CeSDK_TUP_PC_CALL_DemoDlg dialog

IMPLEMENT_DYNAMIC(CeSDK_TUP_PC_CALL_DemoDlg, CDialogEx)

CeSDK_TUP_PC_CALL_DemoDlg::CeSDK_TUP_PC_CALL_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CeSDK_TUP_PC_CALL_DemoDlg::IDD, pParent)
	, bLoginFlag(false)
	, bCalledFlag(false)
	, m_callid(0)
	, m_callConnectTime(0)
	, m_strSipAccount("")
	,m_strCalleerSipNumber("")
{
	memset(&localIP, 0, sizeof(localIP));
}

CeSDK_TUP_PC_CALL_DemoDlg::~CeSDK_TUP_PC_CALL_DemoDlg()
{
}

void CeSDK_TUP_PC_CALL_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipCtrlServerIP);
	DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_editServerPort);
	DDX_Control(pDX, IDC_EDIT_LOGIN_ACCOUNT, m_editLoginAccount);
	DDX_Control(pDX, IDC_EDIT_LOGIN_PASSWORD, m_editLoginPassword);
	DDX_Control(pDX, IDC_BUTTON_CALL_HOLD, m_btnCallHold);
	DDX_Control(pDX, IDC_BUTTON_SPEAKER, m_btnSpeaker);
	DDX_Control(pDX, IDC_BUTTON_MICROPHONE, m_btnMicro);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT, m_btnDisconnect);
	DDX_Control(pDX, IDC_STATIC_CALL_STATUS, m_stcCallStatus);
	DDX_Control(pDX, IDC_BUTTON_CALL, m_btnCall);
	DDX_Control(pDX, IDC_STATIC_CALL_TIME, m_stcCallTime);
	DDX_Control(pDX, IDC_STATIC_CALL_NUMBER, m_stcCallNumber);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT_CALL, m_btnAcceptCall);
	DDX_Control(pDX, IDC_BUTTON_REFUSE_CALL, m_btnRefuseCall);
	DDX_Control(pDX, IDC_BUTTON_LOGOFF, m_btnLogOff);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_btnLogOut);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_EDIT_CALL_STATUS, m_editCallStatus);
	DDX_Control(pDX, IDC_EDIT_CALL_TIME, m_editCallTime);
	DDX_Control(pDX, IDC_EDIT_CALL_NUMBER, m_editCallNumber);
	DDX_Control(pDX, IDC_SLIDER_SPEAKER, m_sldSpeaker);
	DDX_Control(pDX, IDC_SLIDER_MICRO, m_sldMicro);
	DDX_Control(pDX, IDC_EDIT_TARGET_ACCOUNT, m_editTargetAccount);
	DDX_Control(pDX, IDC_EDIT_CALL_NAME, m_editCallName);
	DDX_Control(pDX, IDC_STATIC_CALL_NAME, m_stcCallName);
}


BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_CALL_DemoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_CALL, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonCall)
	ON_MESSAGE(WM_CAll_INCMING, &CeSDK_TUP_PC_CALL_DemoDlg::OnCallIncoming)
	ON_MESSAGE(WM_CAll_RING, &CeSDK_TUP_PC_CALL_DemoDlg::OnCallRing)
	ON_MESSAGE(WM_CAll_CONNECTED, &CeSDK_TUP_PC_CALL_DemoDlg::OnCallConnected)
	ON_MESSAGE(WM_CAll_ENDED, &CeSDK_TUP_PC_CALL_DemoDlg::OnCallEnded)
	ON_MESSAGE(WM_KICK_USER, &CeSDK_TUP_PC_CALL_DemoDlg::OnKickOutUser)
	ON_MESSAGE(WM_LOGIN_RESULT, &CeSDK_TUP_PC_CALL_DemoDlg::OnLoginResult)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT_CALL, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonAcceptCall)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_LOGOFF, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonLogoff)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_REFUSE_CALL, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonRefuseCall)
	ON_BN_CLICKED(IDC_BUTTON_CALL_HOLD, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonCallHold)
	ON_BN_CLICKED(IDC_BUTTON_SPEAKER, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonSpeaker)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_MICROPHONE, &CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonMicrophone)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPEAKER, &CeSDK_TUP_PC_CALL_DemoDlg::OnNMReleasedcaptureSliderSpeaker)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MICRO, &CeSDK_TUP_PC_CALL_DemoDlg::OnNMReleasedcaptureSliderMicro)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CeSDK_TUP_PC_CALL_DemoDlg message handlers


BOOL CeSDK_TUP_PC_CALL_DemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editLoginAccount.SetWindowTextW(L"486123pc");
	m_editLoginPassword.SetWindowTextW(L"");
	m_ipCtrlServerIP.SetAddress(172, 22, 9, 47);
	m_editServerPort.SetWindowTextW(L"5060");
	SetLoginSectionCtrl(true);
	SetCallSectionCtrl(CALL_INIT);
	SetLogOutSectionCtrl(false);

	/////限制用户名、密码长度以及被叫账户长度长度 byc00327158  Start/////
	m_editLoginAccount.LimitText(32);
	m_editLoginPassword.LimitText(512);
	m_editTargetAccount.LimitText(32);
	// 对端口长度没有进行限制
	m_editServerPort.LimitText(10);
	/////限制用户名、密码长度以及被叫账户长度长度 byc00327158  Start/////

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	if(bLoginFlag)
		return;

	//获取服务器IP
	BYTE field0, field1, field2, field3;
	m_ipCtrlServerIP.GetAddress(field0, field1, field2, field3);
	char IP[100] = {0};
	sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);
	//计算本地的IP
	strncpy_s(localIP, 1024*sizeof(char), CTools::GetBestHostip(IP).c_str(),_TRUNCATE);


	////获取sipaccount,sipserver port////、
	CString cstrPort;
	m_editServerPort.GetWindowText(cstrPort);
	if (cstrPort.IsEmpty())
	{
		AfxMessageBox(L"port is empty!");
		return ;
	}
	CString cstrsipaccount;
	CString cstrsippwd;
	m_editLoginPassword.GetWindowText(cstrsippwd);
	m_editLoginAccount.GetWindowText(cstrsipaccount);
	std::string strserver(IP);
	strserver = strserver + ":" + (CTools::UNICODE2UTF(cstrPort));

	//先登录UC服务器，然后再登录call服务器
	if(!LoginCallService(CTools::UNICODE2UTF(cstrsipaccount),strserver,CTools::UNICODE2UTF(cstrsippwd)))
	{
		//服务器登录成功
		/*

		*/
		AfxMessageBox(_T("LoginCallService Failed"));
	}

	return;
}





bool CeSDK_TUP_PC_CALL_DemoDlg::LoginCallService(std::string strsipaccount,std::string strsipserver,std::string strsippwd)
{
	m_strSipAccount = strsipaccount;

	//设置呼叫回调函数
	TUP_RESULT tRet = tup_call_register_process_notifiy(NotifyCallBack::CallNotify);
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
	CTools::GetIPPort(strsipserver, ip, iServerPort);

	//设置呼叫注册服务器
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

	std::string sipAccount = m_strSipAccount; ///sip NUmber////
	std::string sipUserName = sipAccount + "@" + localIP; ////sip@LocalURL////
	//发送注册请求
	tRet = tup_call_register(sipAccount.c_str(), sipUserName.c_str(), strsippwd.c_str());
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_register failed."));
		return false;
	}
	return true;
}


void CeSDK_TUP_PC_CALL_DemoDlg::SetCallSectionCtrl(int iCallStatus)
{
	switch(iCallStatus)
	{
	case CALL_INIT:
		m_btnDisconnect.ShowWindow(SW_HIDE);
		m_stcCallStatus.ShowWindow(SW_HIDE);
		m_editCallStatus.ShowWindow(SW_HIDE);
		m_stcCallNumber.ShowWindow(SW_HIDE);
		m_stcCallName.ShowWindow(SW_HIDE);
		m_editCallNumber.ShowWindow(SW_HIDE);
		m_editCallName.ShowWindow(SW_HIDE);
		m_btnAcceptCall.ShowWindow(SW_HIDE);
		m_btnRefuseCall.ShowWindow(SW_HIDE);
		m_sldSpeaker.ShowWindow(SW_HIDE);
		m_sldMicro.ShowWindow(SW_HIDE);
		m_editTargetAccount.EnableWindow(false);
		m_btnCall.EnableWindow(false);
		m_sldSpeaker.SetRange(VOLUME_LOWER, VOLUME_UPPER);
		m_sldMicro.SetRange(VOLUME_LOWER, VOLUME_UPPER);	
		SetPartCallSectionCtrl(SW_HIDE);
		break;
	case CALL_IDLE:
		m_editTargetAccount.EnableWindow(true);
		m_btnCall.EnableWindow(true);
		break;
	case CALL_REQUEST:
		m_editTargetAccount.EnableWindow(false);
		m_btnCall.EnableWindow(false);
		m_btnDisconnect.ShowWindow(SW_SHOW);
		m_stcCallStatus.ShowWindow(SW_SHOW);
		m_editCallStatus.ShowWindow(SW_SHOW);
		m_editCallStatus.SetWindowTextW(_T("正在呼叫..."));
		break;
	case CALL_INCOMING:
		m_editTargetAccount.EnableWindow(false);
		m_btnCall.EnableWindow(false);
		m_stcCallNumber.ShowWindow(SW_SHOW);
		m_stcCallName.ShowWindow(SW_SHOW);
		m_editCallNumber.ShowWindow(SW_SHOW);
		m_editCallName.ShowWindow(SW_SHOW);
		m_stcCallStatus.ShowWindow(SW_SHOW);
		m_editCallStatus.ShowWindow(SW_SHOW);
		m_btnAcceptCall.ShowWindow(SW_SHOW);
		m_btnRefuseCall.ShowWindow(SW_SHOW);
		m_editCallStatus.SetWindowTextW(_T("有新来电..."));
		break;
	case CALL_RING:
		m_btnDisconnect.ShowWindow(SW_SHOW);
		m_stcCallStatus.ShowWindow(SW_SHOW);
		m_editCallStatus.ShowWindow(SW_SHOW);
		m_editCallStatus.SetWindowTextW(_T("对方正在振铃..."));
		break;
	case CALL_CONNECTED:
		m_editTargetAccount.EnableWindow(false);
		m_btnCall.EnableWindow(false);
		m_btnDisconnect.ShowWindow(SW_SHOW);
		m_stcCallStatus.ShowWindow(SW_SHOW);
		m_editCallStatus.ShowWindow(SW_SHOW);
		m_stcCallNumber.ShowWindow(SW_SHOW);
		m_stcCallName.ShowWindow(SW_SHOW);
		m_editCallNumber.ShowWindow(SW_SHOW);
		m_editCallName.ShowWindow(SW_SHOW);
		m_btnAcceptCall.ShowWindow(SW_HIDE);
		m_btnRefuseCall.ShowWindow(SW_HIDE);
		m_editCallStatus.SetWindowTextW(_T("正常接通"));
		SetPartCallSectionCtrl(SW_SHOW);
//Add by lwx294490 to fix DTS2015071706093 at 2015-07-17 begin
		if(bCalledFlag)
		{
			m_btnCallHold.EnableWindow(false);
		}
		else
		{
			m_btnCallHold.EnableWindow(true);
		}
//Add by lwx294490 to fix DTS2015071706093 at 2015-07-17 end
		break;
	case CALL_ENDED:
		m_btnDisconnect.ShowWindow(SW_HIDE);
		m_stcCallStatus.ShowWindow(SW_HIDE);
		m_editCallStatus.ShowWindow(SW_HIDE);
		m_editCallTime.SetWindowTextW(_T(""));
		m_stcCallNumber.ShowWindow(SW_HIDE);
		m_stcCallName.ShowWindow(SW_HIDE);
		m_editCallNumber.ShowWindow(SW_HIDE);
		m_editCallName.ShowWindow(SW_HIDE);
		m_btnAcceptCall.ShowWindow(SW_HIDE);
		m_btnRefuseCall.ShowWindow(SW_HIDE);
		m_sldSpeaker.ShowWindow(SW_HIDE);
		m_sldMicro.ShowWindow(SW_HIDE);
		m_editTargetAccount.EnableWindow(true);
		m_btnCall.EnableWindow(true);
		SetPartCallSectionCtrl(SW_HIDE);
		break;
	}
}

//设置语音呼叫部分控件状态，包括通话时间、呼叫保持、扬声器调节、麦克风调节
void CeSDK_TUP_PC_CALL_DemoDlg::SetPartCallSectionCtrl(int nCmdShow)
{
	m_stcCallTime.ShowWindow(nCmdShow);
	m_editCallTime.ShowWindow(nCmdShow);
	m_btnCallHold.ShowWindow(nCmdShow);
	m_btnSpeaker.ShowWindow(nCmdShow);
	m_btnMicro.ShowWindow(nCmdShow);
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonCall()
{
	// TODO: Add your control notification handler code here
	//获取目标账号
	CString cstrTargetSipAccount;
	m_editTargetAccount.GetWindowTextW(cstrTargetSipAccount);
	m_strCalleerSipNumber = CTools::UNICODE2UTF(cstrTargetSipAccount);

	//发起呼叫请求
	TUP_UINT32 callRequestId;
	TUP_RESULT tRet = tup_call_start_call(&callRequestId, CALL_E_CALL_TYPE_IPAUDIO, m_strCalleerSipNumber.c_str());
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(L"tup_call_start_call failed.");
		return;
	}
	else
	{
		m_callid = callRequestId;
		m_editCallNumber.SetWindowTextW(CTools::UTF2UNICODE(m_strCalleerSipNumber));
		SetCallSectionCtrl(CALL_REQUEST);
	}
}


LRESULT CeSDK_TUP_PC_CALL_DemoDlg::OnCallIncoming(WPARAM wParam,LPARAM lParam)
{
	CALL_S_CALL_INFO* notifyInfo = (CALL_S_CALL_INFO*)wParam;
	if(NULL == notifyInfo)
	{
		return -1L;
	}

	m_callid = notifyInfo->stCallStateInfo.ulCallID;
	//通知对方本方正在振铃
	tup_call_alerting_call(m_callid);

		////修改界面显示////
	CString cstrSourceName = CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acDisplayName);
	CString cstrSourceNumber = CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acTelNum);
	m_editCallName.SetWindowTextW(cstrSourceName);
	m_editCallNumber.SetWindowTextW(cstrSourceNumber);

	SetCallSectionCtrl(CALL_INCOMING);

	return 0L;
}

LRESULT CeSDK_TUP_PC_CALL_DemoDlg::OnCallRing(WPARAM wParam,LPARAM lParam)
{
	SetCallSectionCtrl(CALL_RING);

	return 0L;
}

void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonAcceptCall()
{
	// TODO: Add your control notification handler code here
	//接收呼叫
//Modify by lwx294490 to fix DTS2015071706093 at 2015-07-17 begin
	TUP_RESULT tRet = tup_call_accept_call(m_callid, TUP_FALSE);
	if(TUP_SUCCESS == tRet)
	{
		bCalledFlag = true;
	}
//Modify by lwx294490 to fix DTS2015071706093 at 2015-07-17 begin
}


LRESULT CeSDK_TUP_PC_CALL_DemoDlg::OnCallConnected(WPARAM wParam,LPARAM lParam)
{
	m_callConnectTime = 0;
	SetCallSectionCtrl(CALL_CONNECTED);
	SetTimer(CALL_CONNECTED_TIME_ID, CALL_CONNECTED_TIME, NULL);
	return 0L;
}



void CeSDK_TUP_PC_CALL_DemoDlg::SetLoginSectionCtrl(bool bState)
{
	m_btnLogin.EnableWindow(bState);
	m_ipCtrlServerIP.EnableWindow(bState);
	m_editServerPort.EnableWindow(bState);
	m_editLoginAccount.EnableWindow(bState);
	m_editLoginPassword.EnableWindow(bState);
}

void CeSDK_TUP_PC_CALL_DemoDlg::SetLogOutSectionCtrl(bool bState)
{
	m_btnLogOff.EnableWindow(bState);
	m_btnLogOut.EnableWindow(bState);
}

//退出
void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	if(!bLoginFlag)
		return;

	TUP_RESULT tRet = tup_call_deregister(m_strSipAccount.c_str());
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_call_deregister failed."));
	}
	OnOK();

	bLoginFlag = false;
}


//注销
void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonLogoff()
{
	// TODO: Add your control notification handler code here
	if(!bLoginFlag)
		return;

	TUP_RESULT tRet = tup_call_deregister(m_strSipAccount.c_str());
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_call_deregister failed."));
	}
	bLoginFlag = false;

	SetCallSectionCtrl(CALL_INIT);
	SetLoginSectionCtrl(true);
	SetLogOutSectionCtrl(false);
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonDisconnect()
{
	// TODO: Add your control notification handler code here
//Add by lwx294490 to fix DTS2015070907324 at 2015-07-14 begin
	CString cstrHold;
	m_btnCallHold.GetWindowTextW(cstrHold);

	if(cstrHold.Compare(_T("恢复通话")) == 0)
	{
		//关闭呼叫保持
		TUP_RESULT tRet = tup_call_unhold_call(m_callid);
		if(TUP_SUCCESS == tRet)
		{
			m_btnCallHold.SetWindowTextW(_T("呼叫保持"));
		}
	}
//Add by lwx294490 to fix DTS2015070907324 at 2015-07-14 end

	TUP_RESULT tRet = tup_call_end_call(m_callid);
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(L"tup_call_end_call failed.");
	}
}


LRESULT CeSDK_TUP_PC_CALL_DemoDlg::OnCallEnded(WPARAM wParam,LPARAM lParam)
{
	if(bLoginFlag)
	{
		//纯粹挂断电话操作
		SetCallSectionCtrl(CALL_ENDED);
	}
	else
	{
		//注销操作
		//m_editTargetAccount.SetWindowTextW(L"");
		SetCallSectionCtrl(CALL_INIT);
		SetLoginSectionCtrl(true);
		SetLogOutSectionCtrl(false);
	}

	bCalledFlag = false;
	m_editTargetAccount.SetWindowTextW(L"");
	m_btnCallHold.SetWindowTextW(_T("呼叫保持"));
	KillTimer(CALL_CONNECTED_TIME_ID);
	m_callConnectTime = 0;
	return 0L;
}


LRESULT CeSDK_TUP_PC_CALL_DemoDlg::OnKickOutUser(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedButtonLogoff();
	AfxMessageBox(_T("Kicked OFF,Please ReLogin！"));
	return 0L;
}
LRESULT CeSDK_TUP_PC_CALL_DemoDlg::OnLoginResult(WPARAM wParam, LPARAM lParam)
{
	bLoginFlag = (bool)wParam; 
	////登录成功////
	if (bLoginFlag)
	{
		m_editTargetAccount.SetWindowTextW(L"");
		SetLoginSectionCtrl(false);
		SetCallSectionCtrl(CALL_IDLE);
		SetLogOutSectionCtrl(true);
	}
	else
	{
		AfxMessageBox(_T("CALL_E_EVT_CALL_AUTHORIZE_FAILED"));
	}
	return 0L;
}
void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonRefuseCall()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_call_end_call(m_callid);
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(L"tup_call_end_call failed.");
	}
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonCallHold()
{
	// TODO: Add your control notification handler code here
	CString cstrHold;
	m_btnCallHold.GetWindowTextW(cstrHold);

	if(cstrHold.Compare(_T("呼叫保持")) == 0)
	{
		//开启通话保持
		TUP_RESULT tRet = tup_call_hold_call(m_callid);
		if(TUP_FAIL == tRet)
		{
			AfxMessageBox(L"tup_call_hold_call failed.");
		}
		else
		{
			m_btnCallHold.SetWindowTextW(_T("恢复通话"));
		}
	}
	else
	{
		//关闭呼叫保持
		TUP_RESULT tRet = tup_call_unhold_call(m_callid);
		if(TUP_FAIL == tRet)
		{
			AfxMessageBox(L"tup_call_unhold_call failed.");
		}
		else
		{
			m_btnCallHold.SetWindowTextW(_T("呼叫保持"));
		}
	}
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_sldSpeaker.IsWindowVisible())
	{
		SpeakerVolumeSave();
		m_sldSpeaker.ShowWindow(SW_HIDE);
	}

	if(m_sldMicro.IsWindowVisible())
	{
		MicroVolumeSave();
		m_sldMicro.ShowWindow(SW_HIDE);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonSpeaker()
{
	// TODO: Add your control notification handler code here
	TUP_UINT32 iSpeakerLevel = 0;
	//获取输出音量
	TUP_RESULT tRet = tup_call_media_get_speak_volume(&iSpeakerLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_speak_volume Failed.");
	}
	else
	{
		m_sldSpeaker.SetPos(VOLUME_UPPER - iSpeakerLevel);
		m_sldSpeaker.ShowWindow(SW_SHOW);
	}
}


void CeSDK_TUP_PC_CALL_DemoDlg::SpeakerVolumeSave()
{
	int iSpeakerLevel = m_sldSpeaker.GetPos();
	//设置扬声器的输出音量大小
	TUP_RESULT tRet = tup_call_media_set_speak_volume(CALL_E_AO_DEV_SPEAKER, (VOLUME_UPPER - iSpeakerLevel));
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_speak_volume Failed.");
	}
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnBnClickedButtonMicrophone()
{
	// TODO: Add your control notification handler code here
	TUP_UINT32 iMicroLevel = 0;
	//获取输入音量
	TUP_RESULT tRet = tup_call_media_get_mic_volume(&iMicroLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_mic_volume Failed.");
	}
	else
	{
		m_sldMicro.SetPos(VOLUME_UPPER - iMicroLevel);
		m_sldMicro.ShowWindow(SW_SHOW);
	}
}

void CeSDK_TUP_PC_CALL_DemoDlg::MicroVolumeSave()
{
	int iMicroLevel = m_sldMicro.GetPos();
	//设置麦克风的输出音量大小
	TUP_RESULT tRet = tup_call_media_set_mic_volume(CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER, VOLUME_UPPER - iMicroLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_mic_volume Failed.");
	}
}

void CeSDK_TUP_PC_CALL_DemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnBnClickedButtonLogout();

	CDialogEx::OnClose();
}

//Add by lwx294490 to fix DTS2015070907187 at 2015-07-13 begin
BOOL CeSDK_TUP_PC_CALL_DemoDlg::PreTranslateMessage(MSG* pMsg)
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
//Add by lwx294490 to fix DTS2015070907187 at 2015-07-13 end

//Add by lwx294490 to fix DTS2015070907556 at 2015-07-14 begin
void CeSDK_TUP_PC_CALL_DemoDlg::OnNMReleasedcaptureSliderSpeaker(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	SpeakerVolumeSave();
	*pResult = 0;
}


void CeSDK_TUP_PC_CALL_DemoDlg::OnNMReleasedcaptureSliderMicro(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	MicroVolumeSave();
	*pResult = 0;
}
//Add by lwx294490 to fix DTS2015070907556 at 2015-07-14 end


void CeSDK_TUP_PC_CALL_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(CALL_CONNECTED_TIME_ID == nIDEvent)
	{
		m_callConnectTime++;
		CString strTimer;
		int secod = (int) m_callConnectTime % 60;
		int minte = (int) m_callConnectTime / 60;
		int hour = (int) minte / 60;
		minte = minte % 60;
		strTimer.Format(_T("%02d:%02d:%02d"), hour, minte, secod);
		m_editCallTime.SetWindowText(strTimer);
		m_editCallTime.ShowWindow(SW_SHOW);
	}

	CDialogEx::OnTimer(nIDEvent);
}
