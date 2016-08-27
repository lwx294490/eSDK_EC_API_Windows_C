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

// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "MainDlg.h"
#include "Tools.h"
#include "IMManage.h"
#include "NewCallDlg.h"
#include "NotifyCallBack.h"
#include "GroupInviteDlg.h"
#include "ConfDlg.h"

#define HEARTBEAT_TIME (30*1000)
const int HEART_BEAT_TIMEID = 1000;


// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
	,m_bLoginFlag(false)
	,m_cstrLoginAccount(L"")
	,m_strSipAccount("")
	,m_iLoginStatus(IM_E_STATUS_INIT)
	,m_pEntAddDlg(NULL)
	,m_pContactDlg(NULL)
	,m_pGroupDlg(NULL)
	,m_pSettingDlg(NULL)
	,m_pDetailDlg(NULL)
	,m_pDataDonfDlg(NULL)
	,heartSum(0)
	,m_bisDadtaConf(false)
{
}

CMainDlg::~CMainDlg()
{
	SAFE_DELETE(m_pContactDlg);
	SAFE_DELETE(m_pGroupDlg);
	SAFE_DELETE(m_pEntAddDlg);
	SAFE_DELETE(m_pSettingDlg);
	SAFE_DELETE(m_pDetailDlg);
	SAFE_DELETE(m_pDataDonfDlg);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcUserName);
	DDX_Control(pDX, IDC_COMBO_STATUS, m_cbxStatus);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tabMainWnd);
	DDX_Control(pDX, IDC_EDIT_SIGNTRUE, m_edtSign);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnSysMenu);
	DDX_Control(pDX, IDC_BUTTON_ENTADDR, m_btnEntAddr);
	DDX_Control(pDX, IDC_STATIC_HEAD, m_stcHead);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ENTADDR, &CMainDlg::OnBnClickedButtonEntaddr)
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CMainDlg::OnBnClickedButtonMenu)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMainDlg::OnTcnSelchangeTabMain)
	ON_MESSAGE(WM_MENU_SEND_IM,&CMainDlg::OnMenuSendIM)
	ON_MESSAGE(WM_CLOSE_IM_WND,&CMainDlg::OnCloseIMWnd)
	ON_MESSAGE(WM_CLOSE_CONF_WND,&CMainDlg::OnCloseConfWnd)
	ON_MESSAGE(WM_RECV_IM,&CMainDlg::OnRecvIM)
	ON_MESSAGE(WM_UPDATE_CONTACT,&CMainDlg::OnUpdateConatct)
	ON_MESSAGE(WM_CAll_CONNECTED,&CMainDlg::OnCallConnceted)
	ON_MESSAGE(WM_CAll_END,&CMainDlg::OnCallEnd)
	ON_MESSAGE(WM_CAll_INCMING,&CMainDlg::OnCallIncoming)
	ON_MESSAGE(WM_CALL_OUTGOING,&CMainDlg::OnCallOutgoing)
	ON_MESSAGE(WM_CLOSE_SET_DLG,&CMainDlg::OnCloseSetDlg)
	ON_MESSAGE(WM_CLOSE_ENT_DLG,&CMainDlg::OnCloseEntAddrDlg)
	ON_MESSAGE(WM_CLOSE_DETAIL_DLG,&CMainDlg::OnCloseDetailDlg)
	ON_MESSAGE(WM_SHOW_DETAIL,&CMainDlg::OnShowDetailDlg)
	ON_MESSAGE(WM_CONF_INCMING,&CMainDlg::OnConfIncoming)
	ON_MESSAGE(WM_CONF_CREATE_RET,&CMainDlg::OnConfCreate)
	ON_MESSAGE(WM_CONF_CONNECTED,&CMainDlg::OnConfConnect)
	ON_MESSAGE(WM_CALL_BETRANSFER_CONF,&CMainDlg::OnCALLTOfCreate)
	ON_MESSAGE(WM_GROUP_NOTIFY,&CMainDlg::OnGroupNotify)
	ON_STN_CLICKED(IDC_STATIC_HEAD, &CMainDlg::OnStnClickedStaticHead)
	ON_COMMAND_RANGE(ID_MAIN_SETTING_MENU, ID_MAIN_EXIT_MENU, &CMainDlg::OnClickMainMenuItem)
	ON_CBN_SELCHANGE(IDC_COMBO_STATUS, &CMainDlg::OnCbnSelchangeComboStatus)
	ON_MESSAGE(WM_DATACONF_CREAT,&CMainDlg::OnDataConfCreate)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT_SIGNTRUE, &CMainDlg::OnEnChangeEditSigntrue)
	ON_MESSAGE(WM_IM_KICKOUT_NOTIFY, &CMainDlg::OnKickOutNotify)
	ON_MESSAGE(WM_DATACONF_END, &CMainDlg::OnCloseDataConfWnd)
	ON_MESSAGE(WM_FIXGROUP_IDENTIFY_NOTIFY,&CMainDlg::OnIdentifyNotfiy)
	ON_MESSAGE(WM_CONFIRM_JOINFIXEDGROUP_NOTIFY,&CMainDlg::OnConfirmJoinNotify)
	ON_MESSAGE(WM_MENU_GROUP_CHAT,&CMainDlg::OnGroupChatSurface)
	ON_MESSAGE(WM_FIXGROUP_DELETE_NOTIFY,&CMainDlg::OnGroupDeleteMember)
	ON_MESSAGE(WM_HEARTBEAT_NOTIFY,&CMainDlg::OnHeartBeatNotify)
	ON_MESSAGE(WM_DISMISS_FIXEDGROUP_NOTIFY,&CMainDlg::OnDismissFixedGroupNotify)
	ON_MESSAGE(WM_GROUP_INVITEDLG_CLOSE,&CMainDlg::OnGroupInvNotyClose)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(!m_bLoginFlag)
	{
		return FALSE;
	}

	RefreshControl();

	SetTimer(HEART_BEAT_TIMEID,HEARTBEAT_TIME,NULL);

	if(NULL == m_pContactDlg)
	{
		m_pContactDlg = new CContactDlg();		
	}
	if(!::IsWindow(m_pContactDlg->GetSafeHwnd()))
	{
		m_pContactDlg->Create(CContactDlg::IDD,&m_tabMainWnd);		
	}
		

	if(NULL == m_pGroupDlg)
	{
		m_pGroupDlg = new CGroupDlg(this);		
	}
	if(!::IsWindow(m_pGroupDlg->GetSafeHwnd()))
	{
		m_pGroupDlg->Create(CGroupDlg::IDD,&m_tabMainWnd);
	}

	m_tabMainWnd.InsertItem(0,L"联系人");
	m_tabMainWnd.InsertItem(1,L"群组");

	CRect rc;
	m_tabMainWnd.GetClientRect(&rc);
	rc.top+=20; 
	rc.bottom-=4; 
	rc.left+=4; 
	rc.right-=4; 
	if(NULL != m_pContactDlg)
	{
		m_pContactDlg->MoveWindow(&rc,TRUE);
		m_pGroupDlg->MoveWindow(&rc,TRUE);
		m_pContactDlg->ShowWindow(SW_NORMAL);
	}

	/////DTS2015110405099 限制个人签名字符长度   by c00327158 Start////
	m_edtSign.LimitText(IM_D_MAX_DESC_LENGTH);
	/////DTS2015110405099 限制个人签名字符长度    by c00327158 Start////

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMainDlg::SetLoginFlag(bool bFlag)
{
	m_bLoginFlag = bFlag;	
}
void CMainDlg::SetCurLoginAccount(CString& cstrAccount)
{
	m_cstrLoginAccount = cstrAccount;
}
void CMainDlg::SetCurSipAccount(std::string& strSipAccount)
{
	m_strSipAccount = strSipAccount;
}
void CMainDlg::SetCurStatus(int istatus)
{
	m_iLoginStatus = istatus;
	///登录显示框也响应变化//////
	if (m_bLoginFlag && m_cbxStatus)
	{
		switch(istatus)
		{
		case IM_E_STATUS_ONLINE :
			m_cbxStatus.SetCurSel(0);
			break;
		case IM_E_STATUS_BUSY   :
			m_cbxStatus.SetCurSel(1);
			break;
		case IM_E_STATUS_DONTDISTURB  :
			m_cbxStatus.SetCurSel(3);
			break;
		default:
			m_cbxStatus.SetCurSel(2);
			break;
		}
		
	}
}

//Add by w00321336 to fix DTS2015010702889 at 2015-1-21
int CMainDlg::GetCurStatus() const
{
	return m_iLoginStatus;
}

void CMainDlg::RefreshControl(void)
{
	SetWindowText(m_cstrLoginAccount);

	IM_S_GETUSERINFOARG sefInfoarg;
	CTools::CString2Char(m_cstrLoginAccount,sefInfoarg.account,IM_D_MAX_ACCOUNT_LENGTH);
	IM_S_USERINFO userinfo;	
	TUP_RESULT tRet = tup_im_getuserinfo(&sefInfoarg,&userinfo);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_getuserinfo failed.");
		return;
	}

	//设置头像
	if(0 != strlen(userinfo.imageID))
	{	
		if(strcmp(userinfo.imageID,userinfo.account) == 0)
		{
			//自定义头像
			IM_S_IMAGEREQARG ImageArg;
			IM_S_USERIMAGEINFO ImageAck;
			strcpy_s(ImageArg.id,IM_D_MAX_ACCOUNT_LENGTH,userinfo.imageID);
			tRet = tup_im_getuserdefineimage(&ImageArg,&ImageAck);
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_im_getuserdefineimage failed.");
			}

			m_stcHead.SetImgBuffer(ImageAck.imagebits.data,ImageAck.imagebits.length);
		}
		else
		{
			//系统头像
			CString strAppPath = CTools::getCurrentPath();

			//Modified by w00321336 to fix image missing issue at 2015-2-21 begin
			CString strPath;
			strPath.Format(_T("%s\\face\\%s.png"), strAppPath, CTools::UTF2UNICODE(userinfo.imageID));
			m_stcHead.SetImageFile(strPath);
			//Modified by w00321336 to fix image missing issue at 2015-2-21 end
		}
	}
	else
	{
		CString strAppPath = CTools::getCurrentPath();

		//Modified by w00321336 to fix image missing issue at 2015-2-21 begin
		CString strPath;
		strPath.Format(_T("%s\\face\\0.png"), strAppPath, CTools::UTF2UNICODE(userinfo.imageID));
		m_stcHead.SetImageFile(strPath);
		//Modified by w00321336 to fix image missing issue at 2015-2-21 end
	}

	//设置用户名
	CString cstrName;
	CTools::string2CString(userinfo.name,cstrName);
	m_stcUserName.SetWindowText(cstrName);

	//设置签名
	CString signtrue;
	CTools::string2CString(userinfo.signature,signtrue);
	m_edtSign.SetWindowText(signtrue);	


	m_cbxStatus.Clear();
	m_cbxStatus.InsertString(0,_T("在线"));
	m_cbxStatus.InsertString(1,_T("忙碌"));
	m_cbxStatus.InsertString(2,_T("离开"));
	m_cbxStatus.InsertString(3,_T("勿扰"));
	switch (m_iLoginStatus)
	{
	case IM_E_STATUS_ONLINE:
		{
			m_cbxStatus.SetCurSel(0);
			break;
		}
	case IM_E_STATUS_BUSY:
		{
			m_cbxStatus.SetCurSel(1);
			break;
		}
	case IM_E_STATUS_LEAVE:
		{
			m_cbxStatus.SetCurSel(2);
			break;
		}
	case IM_E_STATUS_DONTDISTURB:
		{
			m_cbxStatus.SetCurSel(3);
			break;
		}
	}
	

}

void CMainDlg::OnBnClickedButtonEntaddr()
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL == m_pEntAddDlg)
	{
		m_pEntAddDlg = new CEntAddrDlg();	
	}
	if(!::IsWindow(m_pEntAddDlg->GetSafeHwnd()))
	{
		m_pEntAddDlg->Create(CEntAddrDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
	}
	m_pEntAddDlg->ShowWindow(SW_SHOW);
}

void CMainDlg::OnBnClickedButtonMenu()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	m_btnSysMenu.GetWindowRect(&rc);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_MAIN_SETTING_MENU, _T("设置"));
	//menu.AppendMenu(MF_STRING, ID_MAIN_PORTAL_MENU, _T("个人管理平台"));
	//menu.AppendMenu(MF_STRING, ID_MAIN_HELP_MENU, _T("帮助"));
	menu.AppendMenu(MF_STRING, ID_MAIN_LOGOUT_MENU, _T("注销"));
	menu.AppendMenu(MF_STRING, ID_MAIN_EXIT_MENU, _T("退出"));
	menu.TrackPopupMenu(TPM_BOTTOMALIGN, rc.left, rc.top, this);

}
void CMainDlg::OnClickMainMenuItem(UINT nID)
{
	switch (nID)
	{
	case ID_MAIN_SETTING_MENU:
		{
			ShowSetDlg();
			break;
		}
	case ID_MAIN_PORTAL_MENU:
		{
			
			break;
		}
	case ID_MAIN_HELP_MENU:
		{
			break;
		}
	case ID_MAIN_LOGOUT_MENU:
		{
			Logout();
			OnOK();
		}
	case ID_MAIN_EXIT_MENU:
		{
			PostMessage(WM_CLOSE,NULL,NULL);
			break;
		}
	}

}

void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(HEART_BEAT_TIMEID == nIDEvent)
	{
		TUP_RESULT tRet = tup_im_sendheartbeat();
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_im_sendheartbeat failed.");
		}
		else
		{
			heartSum++;
			if(heartSum>6)
			{
				Logout();
				OnOK();
				heartSum = 0;
				AfxMessageBox(_T("Kicked Off,Please Relogin."));
			}
		}
	
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CMainDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iIndex = m_tabMainWnd.GetCurSel();
	switch (iIndex)
	{
	case -1:
		{
			break;
		}
	case 0:
		{          
			m_pContactDlg->ShowWindow(SW_SHOW);
			m_pGroupDlg->ShowWindow(SW_HIDE);
			break;
		}
	case 1:
		{  
			m_pContactDlg->ShowWindow(SW_HIDE);
			m_pGroupDlg->ShowWindow(SW_SHOW);
			break;
		}
	}

}

LRESULT CMainDlg::OnMenuSendIM(WPARAM wParam,LPARAM lParam)
{
	IM_S_USERINFO* pUserInfo = (IM_S_USERINFO *)lParam;
	if(NULL == pUserInfo)
	{
		return -1L;
	}

	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByAccount(pUserInfo->account);
	if(NULL == pIMDlg)
	{
		pIMDlg =  CIMManage::GetIntance().CreateIMDlgByAccount(pUserInfo->account);
	}

	CHECK_POINTER_RETURN(pIMDlg,-1L);

	CString Name;
	pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
	pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
	pIMDlg->PostMessage(WM_MENU_SEND_IM,wParam,lParam);
	return 0L;
}
LRESULT CMainDlg::OnCloseIMWnd(WPARAM wParam,LPARAM lParam)
{
	CIMDlg* pDlg = (CIMDlg*)wParam;
	CIMManage::GetIntance().DeleteIMDlgByIMDlg(pDlg);
	return 0L;
}
LRESULT CMainDlg::OnGroupInvNotyClose(WPARAM wParam,LPARAM lParam)
{
	CGroupInviteDlg* pGroupInvitDlg = (CGroupInviteDlg*)wParam;
	CIMManage::GetIntance().DelGroupNotifyDlgByDlg(pGroupInvitDlg);
	return 0L;
}
LRESULT CMainDlg::OnCloseDataConfWnd(WPARAM wParam,LPARAM lParam)
{
	//没有用到入参wParam，因为实际上只能存在一个数据会议对话框
	SAFE_DELETE(m_pDataDonfDlg);
	m_bisDadtaConf = false;
	return 0L;
}
LRESULT CMainDlg::OnIdentifyNotfiy(WPARAM wparam,LPARAM lParam)
{
	IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY* pDlg = (IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY*)wparam;

	if(strcmp(pDlg->adminAccount,g_Account.c_str()) == 0 || CIMManage::GetIntance().GetGroupNotifyDlgByID(pDlg->groupID))
	{
		return -1L;
	}

	CGroupInviteDlg* pGroppNotifyDlg =  CIMManage::GetIntance().CreateGroupNotifyDlgByID(pDlg->groupID);
	pGroppNotifyDlg->m_inviteGroupName = CTools::UTF2UNICODE(pDlg->groupName);
	pGroppNotifyDlg->m_inviteOwner = CTools::UTF2UNICODE(pDlg->adminName);
	pGroppNotifyDlg->m_account = pDlg->adminAccount;
 	pGroppNotifyDlg->ShowWindow(SW_SHOW);
 	pGroppNotifyDlg->UpdateData(FALSE);

	IM_S_SETMESSAGEREAD_ARG* regMsg = new IM_S_SETMESSAGEREAD_ARG;
	IM_S_MESSAGEINFO* argMsgInfo = new IM_S_MESSAGEINFO;
	if (NULL != argMsgInfo)
	{
		strcpy_s(argMsgInfo->sender,sizeof(argMsgInfo->sender) ,pDlg->groupID);
		argMsgInfo->msgId = pDlg->serverMsgID;
		argMsgInfo->msgType = IM_E_IM_HISTORYMESSAGEMSG_TYPE_NOTIFY;
	}

	TUP_S_LIST* pData = new TUP_S_LIST;
	pData->data = (void*)argMsgInfo;
	regMsg->messageinfo = pData;
	regMsg->messageinfo->next = NULL;

	TUP_RESULT Ret = tup_im_setmessageread(regMsg);
	SAFE_DELETE(regMsg);
	SAFE_DELETE(argMsgInfo);
	SAFE_DELETE(pData);
	SAFE_DELETE(pDlg);
	return 0L;
}
LRESULT CMainDlg::OnDismissFixedGroupNotify(WPARAM wParam,LPARAM IParam)
{
	IM_S_IMGROUP_NOTIFY* pGroupInfo = (IM_S_IMGROUP_NOTIFY*)wParam;
	if(NULL == pGroupInfo)
	{
		return -1L;
	}
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pGroupInfo->groupID);

	if(pIMDlg!=NULL)
	{
		pIMDlg->CloseDlg();
	}
	if(m_pGroupDlg)
	{
		if(m_pGroupDlg->m_pGroupAddDlg)
		{
			m_pGroupDlg->m_pGroupAddDlg->GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
		}
		m_pGroupDlg->UpdateGroupListContrl();
	}
	return 0L;
}

LRESULT CMainDlg::OnConfirmJoinNotify(WPARAM wParam,LPARAM lParam)
{
	IM_S_IMGROUP_NOTIFY* pGroupInfo = (IM_S_IMGROUP_NOTIFY*)wParam;
	if(NULL == pGroupInfo)
	{
		return -1L;
	}
	
	CString Name = CTools::UTF2UNICODE(pGroupInfo->memberAccount);
	Name =Name +  _T(" joins this group");
	AfxMessageBox(Name);
	if(m_pGroupDlg)
	{
		if(m_pGroupDlg->m_pGroupAddDlg)
		{
			m_pGroupDlg->m_pGroupAddDlg->GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
		}
		m_pGroupDlg->UpdateGroupListContrl();
	}
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pGroupInfo->groupID);
	if(pIMDlg!=NULL)
	{
		pIMDlg->RefreshMemberList(pGroupInfo->groupID);
	}

	///设置消息已读/////
	IM_S_SETMESSAGEREAD_ARG *arg = new IM_S_SETMESSAGEREAD_ARG;
	IM_S_MESSAGEINFO *argMsgInfo = new IM_S_MESSAGEINFO;
	argMsgInfo->msgType = IM_E_IM_HISTORYMESSAGEMSG_TYPE_NOTIFY;
	memcpy(argMsgInfo->sender, pGroupInfo->groupID, strlen(pGroupInfo->groupID) + 1);
	argMsgInfo->msgId = pGroupInfo->serverMsgID;
	TUP_S_LIST *pData = new TUP_S_LIST;
	pData->data = (TUP_VOID *)argMsgInfo;
	pData->next = NULL;
	arg->messageinfo = pData;
	tup_im_setmessageread(arg);

	SAFE_DELETE(pData);
	SAFE_DELETE(argMsgInfo);
	SAFE_DELETE(arg);
	SAFE_DELETE(pGroupInfo);
	return 0L;
};
LRESULT CMainDlg::OnCloseConfWnd(WPARAM wParam,LPARAM)
{
	SetCurStatus(IM_E_STATUS_ONLINE);
	CConfDlg* pDlg = (CConfDlg*)wParam;
	CIMManage::GetIntance().DeleteConfDlgByConfDlg(pDlg);
	return 0L;
}

LRESULT CMainDlg::OnRecvIM(WPARAM wParam,LPARAM lParam)
{
	IM_S_CODECHAT_NOTIFY *notify  = (IM_S_CODECHAT_NOTIFY *)wParam;
	if(NULL == notify)
	{
		return -1L;
	}
	//Add by w00321336 to fix DTS2015010702889 at 2015-1-21 begin
	if (IM_E_STATUS_DONTDISTURB == GetCurStatus())
	{
		return -1L;
	}

	CString Name;
	if(notify->chatInfo.chatType == IM_E_IM_CHAT_TYPE_SINGLE)
	{	
		CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByAccount(notify->chatInfo.origin);
		if(NULL == pIMDlg)
		{
			pIMDlg =  CIMManage::GetIntance().CreateIMDlgByAccount(notify->chatInfo.origin);
		}
		CHECK_POINTER_RETURN(pIMDlg,-1L);
		pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
		pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
		pIMDlg->PostMessage(WM_RECV_IM,wParam,lParam);
	}
	else
	{
		CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(notify->chatInfo.groupID);
		if(NULL == pIMDlg)
		{
			pIMDlg =  CIMManage::GetIntance().CreateIMDlgByGroupID(notify->chatInfo.groupID);
		}
		CHECK_POINTER_RETURN(pIMDlg,-1L);
		//假如用户处于语音会议中，就将呼叫按钮置灰
		if(CIMManage::GetIntance().GetConfVectorSize() > 0)
		{
			pIMDlg->EnableCallButton(false);
		}
		pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
		pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
		pIMDlg->SetGroupID(notify->chatInfo.groupID);
		pIMDlg->PostMessage(WM_RECV_IM,wParam,lParam);
	}

	return 0L;
}

LRESULT CMainDlg::OnHeartBeatNotify(WPARAM wParam,LPARAM IParam)
{
	heartSum = 0;
	return 0L;
}

LRESULT CMainDlg::OnGroupDeleteMember(WPARAM wParam,LPARAM IParam)
{
	IM_S_IMGROUP_NOTIFY* pGroupNotify = (IM_S_IMGROUP_NOTIFY*)wParam;
	if(NULL == pGroupNotify)
	{
		return -1L;
	}
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pGroupNotify->groupID);
	if((pIMDlg!=NULL)&&( !strcmp(g_Account.c_str(),pGroupNotify->memberAccount)))
	{
		pIMDlg->CloseDlg();
	}
	if(NULL!=pIMDlg)
	{
		pIMDlg->RefreshMemberList(pGroupNotify->groupID);
	}
	if(m_pGroupDlg)
	{
		if(m_pGroupDlg->m_pGroupAddDlg)
		{
			m_pGroupDlg->m_pGroupAddDlg->GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
		}
		m_pGroupDlg->UpdateGroupListContrl();
	}
	return 0L;
}
LRESULT CMainDlg::OnGroupChatSurface(WPARAM wParam,LPARAM lParam)
{
	IM_S_IMGROUPINFO* pUserInfo = (IM_S_IMGROUPINFO*)lParam;
	if(NULL == pUserInfo)
	{
		return -1L;
	}

	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pUserInfo->id);
	if(NULL == pIMDlg)
	{
		pIMDlg =  CIMManage::GetIntance().CreateIMDlgByGroupID(pUserInfo->id);
	}

	CHECK_POINTER_RETURN(pIMDlg,-1L);

	pIMDlg->PostMessage(WM_MENU_GROUP_CHAT,wParam,lParam);
	return 0L;
}

LRESULT CMainDlg::OnUpdateConatct(WPARAM wParam,LPARAM lParam)
{
	if(NULL != m_pContactDlg)
	{
		m_pContactDlg->PostMessage(WM_UPDATE_CONTACT,wParam,lParam);
	}
	return 0L;
}

LRESULT CMainDlg::OnCallConnceted(WPARAM wParam,LPARAM lParam)
{
	CALL_S_CALL_INFO* notifyInfo = (CALL_S_CALL_INFO*)wParam;
	if(NULL == notifyInfo)
	{
		return -1L;
	}

	TUP_UINT32 callid = notifyInfo->stCallStateInfo.ulCallID;

	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);
	if(NULL == pIMDlg)
	{
		pIMDlg = CIMManage::GetIntance().CreateIMDlgByCallID(callid);
	}

	pIMDlg->PostMessage(WM_CAll_CONNECTED,wParam,lParam);

	return 0L;
}
LRESULT CMainDlg::OnCallEnd(WPARAM wParam,LPARAM lParam)
{
	CALL_S_CALL_INFO* notifyInfo = (CALL_S_CALL_INFO*)wParam;
	if(NULL == notifyInfo)
	{
		return -1L;
	}
	///关闭呼叫界面/////
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(notifyInfo->stCallStateInfo.ulCallID);
	if (pIMDlg)
	{
		pIMDlg->PostMessage(WM_CAll_END,(WPARAM)notifyInfo,NULL);
	}
	return 0L;
}

LRESULT CMainDlg::OnCallIncoming(WPARAM wParam,LPARAM lParam)
{
	CALL_S_CALL_INFO* notifyInfo = (CALL_S_CALL_INFO*)wParam;
	if(NULL == notifyInfo)
	{
		return -1L;
	}

	TUP_UINT32 callid = notifyInfo->stCallStateInfo.ulCallID;
	
    //Modified by w00321336 for DTS2015010704879 at 2015-1-20 begin: add title for each section
	CNewCallDlg dlg;
	dlg.m_strName.Format(_T("来电姓名: %s"), CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acDisplayName));
	//dlg.m_strName = CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acDisplayName);
	dlg.m_strNum.Format(_T("来电号码：%s"), CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acTelNum));
	//Modified by w00321336 for DTS2015010704879 at 2015-1-20 end

	if(notifyInfo->stCallStateInfo.enCallType == CALL_E_CALL_TYPE_IPVIDEO)
	{
		dlg.m_BVideoCall  = TRUE;
	}
	else
	{
		dlg.m_BVideoCall  = FALSE;
	}

	(void)tup_call_alerting_call(callid);

	INT_PTR retCode = dlg.DoModal();
	if(retCode == IDOK)
	{		
		CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);
		if(NULL == pIMDlg)
		{
			//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 begin
			IM_S_USERINFO userInfo;
			if(!GetTargetUserInfo(notifyInfo->stCallStateInfo.acTelNum, userInfo))
			{
				AfxMessageBox(_T("Get target user info failed by bind no."));
			}
			pIMDlg = CIMManage::GetIntance().GetIMDlgByAccount(userInfo.account);
			if(NULL == pIMDlg)
			{
				CString Name;
				pIMDlg = CIMManage::GetIntance().CreateIMDlgByCallID(callid);
				pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
				pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
				CHECK_POINTER_RETURN(pIMDlg,-1L);
				pIMDlg->ShowWindow(SW_NORMAL);
				////新增设置头像接口 DTS2016050902555/////
				pIMDlg->SetUserHeadImg(userInfo);
			}
		}
		if(NULL != pIMDlg)
		{
			pIMDlg->SendMessage(WM_CAll_INCMING,wParam,callid);
			if(notifyInfo->stCallStateInfo.enCallType == CALL_E_CALL_TYPE_IPVIDEO)
			{
				pIMDlg->SendMessage(WM_CALL_SHOW_WND,1,callid);
				tup_call_accept_call(callid,TUP_TRUE);
			}
			else
			{
				tup_call_accept_call(callid,TUP_FALSE);
			}			
		}
		
	}
	else
	{
		tup_call_end_call(callid);
	}

	SAFE_DELETE(notifyInfo);
	return 0L;
}
LRESULT CMainDlg::OnCallOutgoing(WPARAM wParam,LPARAM)
{
	////呼出事件/////
	CALL_S_CALL_INFO* notifyInfo = (CALL_S_CALL_INFO*)wParam;
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(notifyInfo->stCallStateInfo.ulCallID);
	if (NULL == pIMDlg)
	{
		////此种方式应该是盲转的reinvite消息/////
		IM_S_USERINFO userInfo;
		if(!GetTargetUserInfo(notifyInfo->stCallStateInfo.acTelNum, userInfo))
		{
			AfxMessageBox(_T("Get target user info failed by bind no."));
		}
		CString Name(CTools::UTF2UNICODE(userInfo.name));
		pIMDlg = CIMManage::GetIntance().CreateIMDlgByCallID(notifyInfo->stCallStateInfo.ulCallID);
		pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
		pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
		pIMDlg->SetWindowText(Name);
		CHECK_POINTER_RETURN(pIMDlg,-1L);
		pIMDlg->ShowWindow(SW_NORMAL);
		pIMDlg->SetUserHeadImg(userInfo);
		pIMDlg->SetCallStatus(SIGNLE_CALL);
		pIMDlg->m_pCallCtrlDlg->SetCallState(CALLING);
		pIMDlg->m_btnCall.EnableWindow(FALSE);
		pIMDlg->m_DataConfCall.EnableWindow(FALSE);
		pIMDlg->m_btnVideoCall.EnableWindow(FALSE);
	}
	SAFE_DELETE(notifyInfo);
	return 0L;
}
LRESULT CMainDlg::OnConfCreate(WPARAM w,LPARAM)
{
	CALL_S_CONF_CREATE_RESULT* result = (CALL_S_CONF_CREATE_RESULT*)w;
	if (result->eConfType == CALL_E_SERVERCONF_AUDIO && !m_bisDadtaConf)
	{
		////需要判断是否是数据会议创建中/////
		CConfDlg* pConfDlg = CIMManage::GetIntance().CreateConfDlgByConfID(result->ulConfID);
		pConfDlg->isChairman = true;			
		pConfDlg->ShowWindow(SW_NORMAL);

		////创建语音会议/////
		pConfDlg->PostMessage(WM_CONF_CREATE_RET,(WPARAM)result->ulResult,NULL);
	}
	else
	{
		/////数据会议创建//////
		if(NULL == m_pDataDonfDlg)
		{
			m_pDataDonfDlg = new CDataConfDlg();
		}
		if(!IsWindow(m_pDataDonfDlg->GetSafeHwnd()))
		{
			m_pDataDonfDlg->Create(CDataConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
		}

		m_pDataDonfDlg->ShowWindow(SW_SHOW);

	}

	SAFE_DELETE(result);

	return 0L;
}
LRESULT CMainDlg::OnConfConnect(WPARAM w,LPARAM)
{
	CALL_S_CONF_CONNECT_RESULT* pNotifyInfo = (CALL_S_CONF_CONNECT_RESULT*)w;
	if (NULL == pNotifyInfo || TUP_SUCCESS != pNotifyInfo->ulResult)
	{
		AfxMessageBox(_T("WM_CONF_CONNECTED failed"));
		return 0L;
	}
	CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(pNotifyInfo->ulConfID);
	if (pDlg)
	{
		pDlg->SendMessage(WM_CONF_CONNECTED,NULL,NULL);
	}
	else
	{
		//////判断是否是语音会议升级为数据会议/////
		if(m_bisDadtaConf)
		{
			tup_call_serverconf_transferto_dataconf(pNotifyInfo->ulConfID);
		}
	}
	SAFE_DELETE(pNotifyInfo);
	return 0L;
}

LRESULT CMainDlg::OnCALLTOfCreate(WPARAM w,LPARAM l)
{
	CALL_S_CONF_BETRANSFERTOCONF* pNotify = (CALL_S_CONF_BETRANSFERTOCONF*)w;
	CConfDlg* pConfDlg = CIMManage::GetIntance().GetConfDlgByConfID(pNotify->ulConfID);
	if(NULL == pConfDlg)
	{
		pConfDlg = CIMManage::GetIntance().CreateConfDlgByConfID(pNotify->ulConfID);
		CHECK_POINTER_RETURN(pConfDlg,-1L);
		pConfDlg->ShowWindow(SW_NORMAL);
	}
	if (pConfDlg)
	{
		pConfDlg->ReshMemberlistByGroupID(pNotify->acGroupUri);
	}
	pConfDlg->m_uiCallID = pNotify->ulCallID;
	return 0L;


}
LRESULT CMainDlg::OnDataConfCreate(WPARAM w,LPARAM)
{
	CALL_S_DATACONF_PARAM* pPara = (CALL_S_DATACONF_PARAM*)w;
	if (NULL == pPara)
	{
		AfxMessageBox(_T("OnDataConfCreate failed"));
	}

	/////数据会议创建//////
	if(NULL == m_pDataDonfDlg)
	{
		m_pDataDonfDlg = new CDataConfDlg();
		m_pDataDonfDlg->Create(CDataConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
		m_pDataDonfDlg->ShowWindow(SW_SHOW);
	}

	m_pDataDonfDlg->StartConf(pPara);
	return 0L;
}
LRESULT CMainDlg::OnConfIncoming(WPARAM wParam,LPARAM lParam)
{
	CALL_S_CONF_INFO* notifyInfo = (CALL_S_CONF_INFO*)wParam;
	if(NULL == notifyInfo)
	{
		return -1L;
	}

	TUP_UINT32 confid = notifyInfo->ulConfID;

	CNewCallDlg dlg;
	dlg.m_bConfCall = true;
	dlg.m_strName.Format(_T("会议主题: %s"), CTools::UTF2UNICODE(notifyInfo->acGroupUri));//Modified by w00321336 for DTS2015010704879 at 2015-1-20

	//char num[100] = {0};
	//_itoa_s(notifyInfo->ulSipAccountID,num,10);//Mark by w00321336:why don't use CString::Format %d?
	dlg.m_strNum.Format(_T("来电号码: %s"), CTools::UTF2UNICODE(notifyInfo->acUserNumber));//Modified by w00321336 for DTS2015010704879 at 2015-1-20

	INT_PTR retCode = dlg.DoModal();
	if(retCode == IDOK)
	{		
		SetCurStatus(IM_E_STATUS_BUSY);
		tup_call_serverconf_accept(confid);
		if (CALL_E_SERVERCONF_AUDIO == notifyInfo->eConfType)
		{
			////语音会议////
			CConfDlg* pConfDlg = CIMManage::GetIntance().CreateConfDlgByConfID(confid);
			pConfDlg->m_uiCallID = notifyInfo->ulCallID;
			pConfDlg->ShowWindow(SW_NORMAL);
			//记录GroupID,一个语音会议窗口对应1个IM
			pConfDlg->SetGroupID(notifyInfo->acGroupUri);
		}
		else
		{
			/////收到的是数据会议邀请/////
			/////数据会议创建//////
			if(NULL == m_pDataDonfDlg)
			{
				m_pDataDonfDlg = new CDataConfDlg();
			}
			if(!IsWindow(m_pDataDonfDlg->GetSafeHwnd()))
			{
				m_pDataDonfDlg->Create(CDataConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
			}

			m_pDataDonfDlg->ShowWindow(SW_SHOW);
		}

		//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 begin
		//语音会议接通后关闭呼叫按钮
		CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(notifyInfo->acGroupUri);
		if(pIMDlg != NULL)
		{
			pIMDlg->EnableCallButton(false);
		}
		//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 end

	}
	else
	{
		tup_call_serverconf_leave(confid);
	}
	SAFE_DELETE(notifyInfo);

	return 0L;
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
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
void CMainDlg::Logout(void)
{
	//先把IM窗口和语音窗口关了，然后再注销
	if(m_pDataDonfDlg)
		::PostMessage(m_pDataDonfDlg->GetSafeHwnd(), WM_CLOSE, NULL, NULL);

	CIMManage::GetIntance().DeleteAllIMDlg();
	CIMManage::GetIntance().DeleteAllConfDlg();
	CIMManage::GetIntance().DelAllGroupNotifyDlg();

	TUP_RESULT tRet = tup_call_deregister(m_strSipAccount.c_str());
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_call_deregister failed."));
	}

	tRet = tup_im_setcancelsendingmessage();
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_setcancelsendingmessage failed."));
	}	

	tRet = tup_im_logout();
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_logout failed."));
	}

	tRet = tup_im_setdispatchmessage(TUP_FALSE);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
	}
	////louout时，需要将发送心跳的定时器停掉////
	KillTimer(HEART_BEAT_TIMEID);
}

//Add by lWX294490 to fix DTS2015082706818 at 2015-08-27 begin
LRESULT CMainDlg::OnKickOutNotify(WPARAM, LPARAM)
{
	Logout();
	OnOK();

	AfxMessageBox(_T("Kicked Off,Please Relogin."));

	return 0L;
}
//Add by lWX294490 to fix DTS2015082706818 at 2015-08-27 end

void CMainDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Logout();

	CDialog::OnClose();
}

void CMainDlg::OnStnClickedStaticHead()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowSetDlg();
	
}
LRESULT CMainDlg::OnCloseSetDlg(WPARAM,LPARAM)
{
	CHECK_POINTER_RETURN(m_pSettingDlg,-1L);

	if(::IsWindow(m_pSettingDlg->GetSafeHwnd()))
	{
		m_pSettingDlg->DestroyWindow();
	}

	SAFE_DELETE(m_pSettingDlg);
	return 0L;
}
LRESULT CMainDlg::OnCloseEntAddrDlg(WPARAM,LPARAM)
{
	CHECK_POINTER_RETURN(m_pEntAddDlg,-1L);

	if(::IsWindow(m_pEntAddDlg->GetSafeHwnd()))
	{
		m_pEntAddDlg->DestroyWindow();
	}

	SAFE_DELETE(m_pEntAddDlg);
	return 0L;
}
LRESULT CMainDlg::OnCloseDetailDlg(WPARAM,LPARAM)
{
	
	CHECK_POINTER_RETURN(m_pDetailDlg,-1L);

	if(::IsWindow(m_pDetailDlg->GetSafeHwnd()))
	{
		m_pDetailDlg->DestroyWindow();
	}

	SAFE_DELETE(m_pDetailDlg);

	return 0L;
}

LRESULT CMainDlg::OnShowDetailDlg(WPARAM pWaram,LPARAM lWaram)
{
	if(NULL == m_pDetailDlg)
	{
		m_pDetailDlg = new CDetailDlg();
	}
	if(!IsWindow(m_pDetailDlg->GetSafeHwnd()))
	{
		m_pDetailDlg->Create(CDetailDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
	}

	m_pDetailDlg->ShowWindow(SW_SHOW);
	m_pDetailDlg->PostMessage(WM_SHOW_DETAIL,pWaram,lWaram);

	return 0L;

}


void CMainDlg::ShowSetDlg(void)
{
	if(NULL == m_pSettingDlg)
	{
		m_pSettingDlg = new CSettingDlg();
	}
	if(!::IsWindow(m_pSettingDlg->GetSafeHwnd()))
	{
		m_pSettingDlg->Create(CSettingDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
	}

	m_pSettingDlg->ShowWindow(SW_SHOW);

}


void CMainDlg::OnCbnSelchangeComboStatus()
{
	// TODO: 在此添加控件通知处理程序代码
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
	else if(i == 3)
	{
		arg.status = IM_E_STATUS_DONTDISTURB;
	}
	else
	{
		arg.status = IM_E_STATUS_ONLINE;
	}
	CTools::CString2Char(L"1",arg.desc,IM_D_MAX_STATUS_DESCLEN);
	TUP_RESULT tRet = tup_im_publishstatus(&arg);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_publishstatus failed."));
	}
	

	if((arg.status == IM_E_STATUS_DONTDISTURB) && (m_iLoginStatus !=  !IM_E_STATUS_DONTDISTURB))
	{
		//开启免打扰
		CALL_S_SERVICE_RIGHT_CFG stServiceCfg;
		memset(&stServiceCfg, 0, sizeof(stServiceCfg));
		stServiceCfg.ulRight = 1;
		strncpy_s(stServiceCfg.acActiveAccessCode, "*56#", CALL_D_ACCESSCODE_MAX_LENGTH-1);
		strncpy_s(stServiceCfg.acDeactiveAccessCode, "#56#", CALL_D_ACCESSCODE_MAX_LENGTH-1);
		TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_DND, (TUP_VOID*)&stServiceCfg);
		//设置免打扰
		tup_call_set_IPTservice(CALL_E_SERVICE_CALL_TYPE_REG_DND,"");
	}
	else if((arg.status !=IM_E_STATUS_DONTDISTURB)&&(m_iLoginStatus == IM_E_STATUS_DONTDISTURB))
	{
		//取消免打扰
		tup_call_set_IPTservice(CALL_E_SERVICE_CALL_TYPE_UNREG_DND,"");	
	}

 
	m_iLoginStatus = arg.status;//Add by w00321336 to fix DTS2015010702889 at 2015-1-21
}

LRESULT CMainDlg::OnGroupNotify(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pNotify->groupID);
	if(NULL == pIMDlg)
	{
		pIMDlg = CIMManage::GetIntance().CreateIMDlgByGroupID(pNotify->groupID);
		pIMDlg->SetLoginAccount(g_Account);
		pIMDlg->SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
		pIMDlg->m_stcName.SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
	}
	pIMDlg->PostMessage(WM_GROUP_NOTIFY,(WPARAM)pNotify,NULL);
	return 0L;
}

void CMainDlg::OnEnChangeEditSigntrue()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	IM_S_USERINFO stUserInfo;

	CTools::CString2Char(m_cstrLoginAccount,stUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH);
	CString signtrue;
	m_edtSign.GetWindowText(signtrue);
	CTools::CString2Char(signtrue,stUserInfo.signature,IM_D_MAX_DESC_LENGTH);
	TUP_RESULT tRet = tup_im_setuserinfo(&stUserInfo);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_setuserinfo failed.");
	}
}

