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
#include "eSDK_TUP_PC_IM_Demo.h"
#include "MainDlg.h"
#include "Tools.h"
#include "IMManage.h"
#include "NotifyCallBack.h"

#define HEARTBEAT_TIME (30*1000)
const int HEART_BEAT_TIMEID = 1000;

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
	,m_bLoginFlag(false)
	,m_cstrLoginAccount(L"")
	,m_pEntAddDlg(NULL)
	,m_pContactDlg(NULL)
{
}

CMainDlg::~CMainDlg()
{
	SAFE_DELETE(m_pContactDlg);
	SAFE_DELETE(m_pEntAddDlg);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcUserName);
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
	ON_MESSAGE(WM_MENU_SEND_IM,&CMainDlg::OnMenuSendIM)
//	ON_MESSAGE(WM_MENU_GROUP_SENDMESSAGE,&CMainDlg::OnMenuGroupSendMsg)
	ON_MESSAGE(WM_CLOSE_IM_WND,&CMainDlg::OnCloseIMWnd)
	ON_MESSAGE(WM_RECV_IM,&CMainDlg::OnRecvIM)
	ON_MESSAGE(WM_UPDATE_CONTACT,&CMainDlg::OnUpdateConatct)
	ON_MESSAGE(WM_CLOSE_ENT_DLG,&CMainDlg::OnCloseEntAddrDlg)
	ON_MESSAGE(WM_GROUP_NOTIFY,&CMainDlg::OnGroupNotify)
	ON_COMMAND_RANGE(ID_MAIN_SETTING_MENU, ID_MAIN_EXIT_MENU, &CMainDlg::OnClickMainMenuItem)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_DISPATCH_MESSAGE_IM,&CMainDlg::OnDispatchMessage)
	ON_MESSAGE(WM_KICK_USER, &CMainDlg::OnKickOutUser)
	ON_EN_KILLFOCUS(IDC_EDIT_SIGNTRUE, &CMainDlg::OnKillfocusEditSigntrue)
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
	//TabCtrl控件上添加新的标签页
	m_tabMainWnd.InsertItem(0,L"联系人");

	CRect rc;
	m_tabMainWnd.GetClientRect(&rc);
	rc.top+=20; 
	rc.bottom-=4; 
	rc.left+=4; 
	rc.right-=4; 
	if(NULL != m_pContactDlg)
	{
		m_pContactDlg->MoveWindow(&rc,TRUE);
		m_pContactDlg->ShowWindow(SW_NORMAL);
	}

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

void CMainDlg::RefreshControl(void)
{
	//设置主窗口标题
	SetWindowText(m_cstrLoginAccount);

	IM_S_GETUSERINFOARG sefInfoarg;
	CTools::CString2Char(m_cstrLoginAccount,sefInfoarg.account,IM_D_MAX_ACCOUNT_LENGTH);
	IM_S_USERINFO userinfo;	
	//精确查找某个用户的信息，此处是查找自身信息
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
			//从服务器获取自定义的头像数据
			tRet = tup_im_getuserdefineimage(&ImageArg,&ImageAck);
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_im_getuserdefineimage failed.");
			}
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
}

void CMainDlg::OnBnClickedButtonEntaddr()
{
	// TODO: 在此添加控件通知处理程序代码
	//“企业通讯录”
	if(NULL == m_pEntAddDlg)
	{
		m_pEntAddDlg = new CEntAddrDlg();	
	}
	if(!::IsWindow(m_pEntAddDlg->GetSafeHwnd()))
	{
		m_pEntAddDlg->Create(CEntAddrDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
	}
	m_pEntAddDlg->ShowWindow(SW_SHOW);
	m_pEntAddDlg->SetCurLoginAccount(m_cstrLoginAccount);
}

void CMainDlg::OnBnClickedButtonMenu()
{
	// TODO: 在此添加控件通知处理程序代码
	//“系统菜单”
	CRect rc;
	m_btnSysMenu.GetWindowRect(&rc);

	CMenu menu;
	menu.CreatePopupMenu();
//	menu.AppendMenu(MF_STRING, ID_MAIN_SETTING_MENU, _T("设置"));
	menu.AppendMenu(MF_STRING, ID_MAIN_LOGOUT_MENU, _T("注销"));
	menu.AppendMenu(MF_STRING, ID_MAIN_EXIT_MENU, _T("退出"));
	menu.TrackPopupMenu(TPM_BOTTOMALIGN, rc.left, rc.top, this);
}

void CMainDlg::OnClickMainMenuItem(UINT nID)
{
	//“系统菜单”选择
	switch (nID)
	{
	case ID_MAIN_LOGOUT_MENU:
		{
			Logout();
			OnOK();
			break;
		}
	case ID_MAIN_EXIT_MENU:
		{
			Logout();
			break;
		}
	}
}

void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//定时调用，向服务器发送心跳消息
	if(HEART_BEAT_TIMEID == nIDEvent)
	{
		TUP_RESULT tRet = tup_im_sendheartbeat();
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_im_sendheartbeat failed.");
		}
	}

	CDialog::OnTimer(nIDEvent);
}


LRESULT CMainDlg::OnMenuSendIM(WPARAM wParam,LPARAM lParam)
{
	//发送即时消息
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
	m_stcUserName.GetWindowText(Name);
	//传递发送方的姓名和账号
	pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
	pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
	pIMDlg->PostMessage(WM_MENU_SEND_IM,wParam,lParam);
	return 0L;
}

//Del by lwx294490 at 2015-7-13 start
//Send group message function for temporary retention
//Send Group Message
// LRESULT CMainDlg::OnMenuGroupSendMsg(WPARAM wParam,LPARAM lParam)
// {
// 	//Storing discuss group member account
// 	typedef std::vector<TUP_CHAR*>VEC_ACCOUNT;
// 	VEC_ACCOUNT m_vecAccount;
// 	m_vecAccount.clear();
// 
// 	//GroupID
// 	TUP_INT64 SendMsggroupID = (TUP_INT64)lParam;
// 
// 	//Get LoginAccount And Name 
// 	CString Name;
// 	m_stcUserName.GetWindowText(Name);
// 	std::string groupname = CTools::UNICODE2UTF(Name);
// 	std::string m_strLoginAccount = CTools::UNICODE2UTF(m_cstrLoginAccount);
// 	MAP_USER_GROUP::iterator itUser = g_mapUserGroup.begin();
// 	MAP_USER_GROUP::iterator itUserEnd = g_mapUserGroup.end();
// 
// 	for(;itUser!=itUserEnd;itUser++)
// 	{
// 		TUP_INT64 groupID = (TUP_INT64)itUser->second;
// 		if(SendMsggroupID == groupID)
// 		{
// 			TUP_INT64 contactID = (TUP_INT64)itUser->first;
// 			IM_S_CONTACTNFO contact = g_mapContact[contactID];	
// 			IM_S_USERINFO userInfo = g_mapUser[contact.staffID];
// 			//Create DisscussGroupName
// 			groupname.append(",");
// 			groupname.append(userInfo.name);
// 			//Put every member's account into vector
// 			m_vecAccount.push_back(g_mapUser[contact.staffID].account);
// 		}
// 	}
// 
// 	//judge the chat dialog is opening or not
// 	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupName(groupname);
// 	if(NULL != pIMDlg)
// 	{
// 		pIMDlg->ShowWindow(SW_SHOW);
// 		return 0L;
// 	}
// 
// 	//Add discuss group
// 	IM_S_IMGROUP_OP_ARG addDgroupArg;
// 	IM_S_ADDIMGROUP_ACK addDGroupAck;
// 	strcpy_s(addDgroupArg.fixedgroupInfo.name,IM_D_MAX_NAME_LENGTH,groupname.c_str());
// 	strcpy_s(addDgroupArg.fixedgroupInfo.owner,IM_D_MAX_ACCOUNT_LENGTH,m_strLoginAccount.c_str());
// 	TUP_RESULT tRet = tup_im_adddiscussiongroup(&addDgroupArg,&addDGroupAck);
// 	if(tRet == TUP_FAIL || addDGroupAck.result == TUP_FALSE)
// 	{
// 		AfxMessageBox(L"tup_im_adddiscussiongroup failed");
// 		return 0L;
// 	}
// 	else
// 	{
// 		//Add discuss group member
// 		VEC_ACCOUNT::iterator it = m_vecAccount.begin();
// 		VEC_ACCOUNT::iterator itEnd = m_vecAccount.end();
// 		for(; it != itEnd; it++)
// 		{
// 			IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
// 			strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,addDGroupAck.id);
// 			strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,groupname.c_str());
// 			strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,*(it));
// 			tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
// 			if(tRet == TUP_FAIL)
// 			{
// 				AfxMessageBox(L"tup_im_adddiscussiongroupmember failed");
// 				return 0L;
// 			}
// 		}
// 	}
// 	
// 	return 0L;
// }
//Del by lwx294490 at 2015-7-13 end

LRESULT CMainDlg::OnCloseIMWnd(WPARAM wParam,LPARAM lParam)
{
	CIMDlg* pDlg = (CIMDlg*)wParam;
	CIMManage::GetIntance().DeleteIMDlgByIMDlg(pDlg);
	return 0L;
}

LRESULT CMainDlg::OnDispatchMessage(WPARAM wParam,LPARAM lParam)
{
	//关闭上报消息使能，用户退出登录时调用
	TUP_RESULT tRet = tup_im_setdispatchmessage(TUP_FALSE);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed."));
	}
	else
	{
		//正常退出
		PostMessage(WM_CLOSE,NULL,NULL);
	}
	return 0L;
}

LRESULT CMainDlg::OnKickOutUser(WPARAM wParam, LPARAM lParam)
{
	Logout();
	OnOK();
	AfxMessageBox(_T("Kicked Off,Please Relogin!"));
	return 0L;
}

LRESULT CMainDlg::OnRecvIM(WPARAM wParam,LPARAM lParam)
{
	//接收消息
	IM_S_CODECHAT_NOTIFY *notify  = (IM_S_CODECHAT_NOTIFY *)wParam;
	if(NULL == notify)
	{
		return -1L;
	}

	CString Name;
	m_stcUserName.GetWindowText(Name);

	//判断聊天模式
	if(notify->chatInfo.chatType == IM_E_IM_CHAT_TYPE_SINGLE)
	{	
		//单聊
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
		pIMDlg->SetLoginAccount(CTools::UNICODE2UTF(m_cstrLoginAccount));
		pIMDlg->SetLoginName(CTools::UNICODE2UTF(Name));
		pIMDlg->SetGroupID(notify->chatInfo.groupID);
		pIMDlg->PostMessage(WM_RECV_IM,wParam,lParam);
	}

	return 0L;
}
LRESULT CMainDlg::OnUpdateConatct(WPARAM wParam,LPARAM lParam)
{
	if(NULL != m_pContactDlg)
	{
		//因为添加、删除联系人，所有需要更新联系人列表
		m_pContactDlg->PostMessage(WM_UPDATE_CONTACT,wParam,lParam);
	}
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
	//取消底层模块中未处理的消息处理
	CIMManage::VEC_IMDLG::iterator it = CIMManage::GetIntance().m_vecIMDlg.begin();
	CIMManage::VEC_IMDLG::iterator itEnd = CIMManage::GetIntance().m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg *pDel = *it;
		(*it)->DestroyWindow();
		SAFE_DELETE(pDel);
	}

	CIMManage::GetIntance().m_vecIMDlg.clear();
	
	TUP_RESULT tRet = tup_im_setcancelsendingmessage();
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_setcancelsendingmessage failed."));
	}

	//注销UC服务器的登录
	tRet = tup_im_logout();
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_logout failed."));
	}	
}

void CMainDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
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

//设置个性签名
void CMainDlg::OnKillfocusEditSigntrue()
{
	// TODO: Add your control notification handler code here
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
