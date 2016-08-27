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

// ConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "ConfDlg.h"
#include "IMDlg.h"
#include "Tools.h"
#include "IMManage.h"
#include "SelectDlg.h"


// CConfDlg 对话框

IMPLEMENT_DYNAMIC(CConfDlg, CDialog)

CConfDlg::CConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfDlg::IDD, pParent)
	, m_uiConfID(0)
	, m_uiCallID(0)
	,isChairman(false)
{
	memset(m_acGroupUri, 0, sizeof(m_acGroupUri));
}

CConfDlg::~CConfDlg()
{
}

void CConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listMember);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcName);
	DDX_Control(pDX, IDC_BUTTON_MUTE, m_btnMute);
	DDX_Control(pDX, IDC_BUTTON_LOCK, m_btnLock);
	DDX_Control(pDX, IDC_BUTTON_HOLD, m_btnHold);
	DDX_Control(pDX, IDC_BUTTON_SUB, m_btnSubject);
}


BEGIN_MESSAGE_MAP(CConfDlg, CDialog)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_CONF_CREATE_RET,&CConfDlg::OnConfCreate)

	ON_MESSAGE(WM_CONF_ADD_MEM_SUC,&CConfDlg::OnConfMemAddSuc)
	ON_MESSAGE(WM_CONF_ADD_MEM_FAIL,&CConfDlg::OnConfMemAddFailed)
	ON_MESSAGE(WM_CONF_MEM_SPK,&CConfDlg::OnConfMemSpk)
	ON_MESSAGE(WM_CONF_MEM_QUIT,&CConfDlg::OnConfMemQuit)
	ON_MESSAGE(WM_CONF_CONNECTED,&CConfDlg::OnConfConnected)
	ON_MESSAGE(WM_CONF_SUBJECT,&CConfDlg::OnConfSubject)
	ON_MESSAGE(WM_CONF_REFESH_SIGNLE,&CConfDlg::OnConfRefreshSingle)
	ON_MESSAGE(WM_CONF_REFESH_LIST,&CConfDlg::OnConfRefreshList)
	ON_BN_CLICKED(IDC_BUTTON_MUTE, &CConfDlg::OnBnClickedButtonMute)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, &CConfDlg::OnBnClickedButtonLock)
	ON_BN_CLICKED(IDC_BUTTON_HOLD, &CConfDlg::OnBnClickedButtonHold)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CConfDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CConfDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CConfDlg::OnNMRClickList1)
	ON_COMMAND_RANGE(ID_CONF_DEL_MEM_MENU, ID_CONF_UNMUTE_MEM_MENU, &CConfDlg::OnClickListMemMenuItem)
	ON_BN_CLICKED(IDC_BUTTON_DataConf, &CConfDlg::OnBnClickedButtonDataconf)
END_MESSAGE_MAP()


// CConfDlg 消息处理程序

BOOL CConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listMember.ModifyStyle(0,LVS_SINGLESEL);
	m_listMember.InsertColumn(COL_MEM_Compere, _T("主席"), LVCFMT_LEFT, 40);
	m_listMember.InsertColumn(COL_MEM_Status, _T("状态"), LVCFMT_LEFT, 40);
	m_listMember.InsertColumn(COL_MEM_Name, _T("姓名"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_ACCOUNT, _T("账号"), LVCFMT_LEFT, 70);
	m_listMember.InsertColumn(COL_MEM_CALLNO, _T("号码"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_CALLSTATE, _T("呼叫状态"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_SPK, _T("发言"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_MUTE, _T("静音"), LVCFMT_LEFT, 60);
	DWORD dwStyle = m_listMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listMember.SetExtendedStyle(dwStyle); //设置扩展风格

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CConfDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}
	if(m_uiConfID != 0)
	{
		if(isChairman)
		{
			tup_call_serverconf_end(m_uiConfID);
//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 begin
			//离开会议时,打开IM窗口上呼叫按钮。主席的IM窗口肯定是根据会议ID创建的
			CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByConfID(m_uiConfID);
			if(pDlg != NULL)
			{
				pDlg->EnableCallButton(true);
			}
//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 end
		}
		else
		{
			tup_call_serverconf_leave(m_uiConfID);
//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 begin
			//离开会议时,打开IM窗口上呼叫按钮。与会者的IM窗口是根据GroupID创建的
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(m_acGroupUri);
			if(pIMDlg != NULL)
			{
				pIMDlg->EnableCallButton(true);
			}
//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 end
		}
		
		m_uiConfID = 0;
	}
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_CONF_WND,(WPARAM)this,NULL);
	PubSelfStatus(IM_E_STATUS_ONLINE);
	CDialog::OnClose();
}

LRESULT CConfDlg::OnConfConnected(WPARAM,LPARAM)
{
	TRACE0("CConfDlg::OnConfConnected\n");

	if(!isChairman)
	{
		m_btnAdd.EnableWindow(FALSE);
		m_btnHold.EnableWindow(FALSE);
		m_btnLock.EnableWindow(FALSE);
		m_btnSubject.EnableWindow(FALSE);
		m_btnMute.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DataConf)->EnableWindow(FALSE);
	}	
	else
	{
		////C50 修改入会逻辑，在收到CALL_E_EVT_SERVERCONF_CONNECT_RESULT时才能够加人////
		CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByConfID(m_uiConfID);
		RefreshMemberList(pDlg->m_listMember);
		Sleep(1000);    ////暂停一秒，给界面绘制准备时间/////
		int iSize =  pDlg->m_listMember.GetItemCount();
		for(int i=0;i<iSize;i++)
		{
			CString cstrCallNo = pDlg->m_listMember.GetItemText(i,COL_MEM_CALLNO);
			if (CTools::UNICODE2UTF(cstrCallNo) == g_BindNO)
			{
				continue;
			}
			std::string strCallno = CTools::UNICODE2UTF(cstrCallNo);
			tup_call_serverconf_add_attendee(m_uiConfID,1,strCallno.c_str(),strCallno.size()+1);
		}
	}
    PubSelfStatus(IM_E_STATUS_BUSY);
	return 0L;

}
void CConfDlg::RefreshMemberList(CListCtrl& listMember)
{
	m_listMember.DeleteAllItems();

	int iSize = listMember.GetItemCount();
	for(int i=0;i<iSize;i++)
	{	
		m_listMember.InsertItem(i,L"");
		CString cstr = L"";
		//主席用户重新设定，拉起语音会议的设为主席
		//cstr = listMember.GetItemText(i,COL_MEM_Compere);
		//m_listMember.SetItemText(i,COL_MEM_Compere,cstr);

		cstr = L"";
		cstr = listMember.GetItemText(i,COL_MEM_Status);
		m_listMember.SetItemText(i,COL_MEM_Status,cstr);

		cstr = L"";
		cstr = listMember.GetItemText(i,COL_MEM_Name);
		m_listMember.SetItemText(i,COL_MEM_Name,cstr);

		cstr = L"";
		cstr = listMember.GetItemText(i,COL_MEM_ACCOUNT);
		m_listMember.SetItemText(i,COL_MEM_ACCOUNT,cstr);

		cstr = L"";
		cstr = listMember.GetItemText(i,COL_MEM_CALLNO);
		m_listMember.SetItemText(i,COL_MEM_CALLNO,cstr);

		cstr = L"";
		cstr = listMember.GetItemText(i,COL_MEM_CALLSTATE);
		m_listMember.SetItemText(i,COL_MEM_CALLSTATE,cstr);

		cstr = L"";
		cstr = listMember.GetItemText(i,COL_MEM_SPK);
		m_listMember.SetItemText(i,COL_MEM_SPK,cstr);
	}



}

void CConfDlg::ReshMemberlistByGroupID(std::string m_strGroupID)
{
	m_listMember.DeleteAllItems();

	IM_S_REQUESTIMGROUPMEMBERS_ARG groupMembArg;
	IM_S_GROUPUSERLIST groupList;

	strcpy_s(groupMembArg.groupID,IM_D_GROUPID_LENGTH,m_strGroupID.c_str());
	groupMembArg.isSyncAll = TUP_TRUE;
	strcpy_s(groupMembArg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");

	tup_im_getfixedgroupmembers(&groupMembArg,&groupList);
	TUP_S_LIST* list =  groupList.memberInfo;
	while(list != NULL)
	{
		IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
		if(NULL != groupUser)
		{
			CString cstrAccount = CTools::UTF2UNICODE(groupUser->account);
			bool bFind = false;
			int iSize = m_listMember.GetItemCount();
			for(int i = 0; i< iSize; i++)
			{
				if(cstrAccount.Compare(m_listMember.GetItemText(i,COL_MEM_ACCOUNT)) == 0)
				{
					bFind = true;
					break;
				}
			}
			if(!bFind)
			{
				m_listMember.InsertItem(iSize,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Compere,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Status,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Name,CTools::UTF2UNICODE(groupUser->name));
				m_listMember.SetItemText(iSize,COL_MEM_ACCOUNT,cstrAccount);
				m_listMember.SetItemText(iSize,COL_MEM_CALLNO,CTools::UTF2UNICODE(groupUser->bindNO));
				m_listMember.SetItemText(iSize,COL_MEM_CALLSTATE,L"");
				m_listMember.SetItemText(iSize,COL_MEM_SPK,L"");
			}
		}
		list = list->next;
	}
	//////释放IM_S_GROUPUSERLIST中的TUP_S_LIST指针/////
	tup_im_release_tup_list(groupList.memberInfo);

	m_btnAdd.EnableWindow(FALSE);
	m_btnHold.EnableWindow(FALSE);
	m_btnLock.EnableWindow(FALSE);
	m_btnSubject.EnableWindow(FALSE);
	m_btnMute.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DataConf)->EnableWindow(FALSE);
}

//Add by w00321336 to fix DTS2015010706187 at 2015-1-20 begin
//Query & init it from IM list?refresh list callback from eSDK is not to stable
void CConfDlg::InitAttendeeList()
{
	CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByConfID(m_uiConfID);
	if(pDlg != NULL)
	{
		RefreshMemberList(pDlg->m_listMember);
	}
}
//Add by w00321336 end

LRESULT CConfDlg::OnConfCreate(WPARAM w,LPARAM l)
{
	TRACE0("CConfDlg::OnConfCreate\n");
	TUP_UINT32 tRet =  TUP_UINT32(w);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"create conference failed");
	}

	if(isChairman)
	{
		m_btnAdd.EnableWindow(TRUE);
		m_btnHold.EnableWindow(TRUE);
		m_btnLock.EnableWindow(TRUE);
		m_btnSubject.EnableWindow(TRUE);
		m_btnMute.EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DataConf)->EnableWindow(TRUE);
	}
	else
	{
		m_btnAdd.EnableWindow(FALSE);
		m_btnHold.EnableWindow(FALSE);
		m_btnLock.EnableWindow(FALSE);
		m_btnSubject.EnableWindow(FALSE);
		m_btnMute.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DataConf)->EnableWindow(FALSE);

	}

	return 0L;
}

LRESULT CConfDlg::OnConfMemAddSuc(WPARAM w,LPARAM l)
{
	TRACE0("CConfDlg::OnConfMemAddSuc\n");
	char* num = (char*)w;
	CString cstrNum = CTools::UTF2UNICODE(num);
	bool bFind = false; 
	int iSize = m_listMember.GetItemCount();
	int j = -1;
	for(int i = 0; i< iSize; i++)
	{
		if(cstrNum.Compare(m_listMember.GetItemText(i,COL_MEM_CALLNO)) == 0)
		{
			bFind = true;
			j = i;
			break;
		}
	}
	if(bFind)
	{
		m_listMember.SetItemText(j,COL_MEM_CALLSTATE,L"会议中");
	}
	delete[] num;
	num = NULL;
	return 0L;
}

LRESULT CConfDlg::OnConfMemAddFailed(WPARAM w,LPARAM l)
{
	TRACE0("CConfDlg::OnConfMemAddFailed\n");
	char* num = (char*)w;
	CString cstrNum = CTools::UTF2UNICODE(num);
	bool bFind = false; 
	int iSize = m_listMember.GetItemCount();
	int j = -1;
	for(int i = 0; i< iSize; i++)
	{
		if(cstrNum.Compare(m_listMember.GetItemText(i,COL_MEM_CALLNO)) == 0)
		{
			bFind = true;
			j = i;
			break;
		}
	}
	if(bFind)
	{
		m_listMember.SetItemText(j,COL_MEM_CALLSTATE,L"未加入");
	}
	delete[] num;
	num = NULL;
	return 0L;

}
LRESULT CConfDlg::OnConfMemSpk(WPARAM w,LPARAM l)
{
	TRACE0("CConfDlg::OnConfMemSpk\n");
	char* num = (char*)w;
	CString cstrNum = CTools::UTF2UNICODE(num);
	bool bFind = false; 
	int iSize = m_listMember.GetItemCount();
	int j = -1;
	for(int i = 0; i< iSize; i++)
	{
		m_listMember.SetItemText(i,COL_MEM_SPK,L"");
		if(cstrNum.Compare(m_listMember.GetItemText(i,COL_MEM_CALLNO)) == 0)
		{
			bFind = true;
			j = i;
		}
	}
	if(bFind)
	{
		m_listMember.SetItemText(j,COL_MEM_SPK,L"发言");
	}
	delete[] num;
	num = NULL;

	return 0L;
}
LRESULT CConfDlg::OnConfMemQuit(WPARAM w,LPARAM)
{
	TRACE0("CConfDlg::OnConfMemQuit\n");
	char* num = (char*)w;
	CString cstrNum = CTools::UTF2UNICODE(num);
	bool bFind = false; 
	int iSize = m_listMember.GetItemCount();
	int j = -1;
	for(int i = 0; i< iSize; i++)
	{
		if(cstrNum.Compare(m_listMember.GetItemText(i,COL_MEM_CALLNO)) == 0)
		{
			bFind = true;
			j = i;
			break;
		}
	}
	if(bFind)
	{
		m_listMember.SetItemText(j,COL_MEM_CALLSTATE,L"已挂断");
	}
	delete[] num;
	num = NULL;

	return 0L;

}

LRESULT CConfDlg::OnConfSubject(WPARAM w,LPARAM)
{
	TRACE0("CConfDlg::OnConfSubject\n");
	std::string* strSubject = (std::string*)w;
	m_stcName.SetWindowText(CTools::UTF2UNICODE(strSubject->c_str()));
	SAFE_DELETE(strSubject);
	return 0L;
}
LRESULT CConfDlg::OnConfRefreshSingle(WPARAM w,LPARAM)
{
	TRACE0("CConfDlg::OnConfRefreshSingle\n");
	CALL_S_CONF_MEMBER* pMem = (CALL_S_CONF_MEMBER*)w;
	if(NULL != pMem)
	{
		CString cstrConfState;
		if(pMem->enState == CALL_E_CONF_ATTENDEE_INVITING)
		{	
			cstrConfState = L"邀请中";
		}
		else if(pMem->enState == CALL_E_CONF_ATTENDEE_INCONF)
		{
			cstrConfState = L"会议中";
		}
		else if(pMem->enState == CALL_E_CONF_ATTENDEE_INVITE_FAIL)
		{
			cstrConfState = L"邀请失败";
		}
		else if(pMem->enState == CALL_E_CONF_ATTENDEE_ADD_FAIL)
		{
			cstrConfState = L"添加失败";
		}

		CString cstrNum = CTools::UTF2UNICODE(pMem->acAttendeeNumber);
		int j = -1;
		if(FindColum(cstrNum,COL_MEM_CALLNO,j))
		{
			m_listMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);			
		}
		else
		{			
			int iSize = m_listMember.GetItemCount();
			m_listMember.InsertItem(iSize,L"");
			j= iSize;
		}
		m_listMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
		m_listMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);
		if(pMem->enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
		{
			m_listMember.SetItemText(j,COL_MEM_Compere,L"主席");
		}

		if(pMem->ulRight != 1)
		{
			m_listMember.SetItemText(j,COL_MEM_MUTE,L"静音");
		}
		else
		{
			m_listMember.SetItemText(j,COL_MEM_MUTE,L"未静音");
		}
		m_listMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);

	}
	SAFE_DELETE(pMem);
	return 0L;
}
LRESULT CConfDlg::OnConfRefreshList(WPARAM w,LPARAM l)
{
	TRACE0("CConfDlg::OnConfRefreshList\n");
	CALL_S_CONF_MEMBER* pMem = (CALL_S_CONF_MEMBER*)w;
	TUP_UINT32 uiSize = (TUP_UINT32)l;
	for(TUP_UINT32 i=0;i<uiSize;i++)
	{

		CString cstrConfState;
		if(pMem[i].enState == CALL_E_CONF_ATTENDEE_INVITING)
		{	
			cstrConfState = L"邀请中";
		}
		else if(pMem[i].enState == CALL_E_CONF_ATTENDEE_INCONF)
		{
			cstrConfState = L"会议中";
		}
		else if(pMem[i].enState == CALL_E_CONF_ATTENDEE_INVITE_FAIL)
		{
			cstrConfState = L"邀请失败";
		}
		else if(pMem[i].enState == CALL_E_CONF_ATTENDEE_ADD_FAIL)
		{
			cstrConfState = L"添加失败";
		}
		
		CString cstrNum = CTools::UTF2UNICODE(pMem[i].acAttendeeNumber);
		int j = -1;
		if(FindColum(cstrNum,COL_MEM_CALLNO,j))
		{
			if(pMem[i].enState != CALL_E_CONF_ATTENDEE_OUT)
			{
				m_listMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
			}
			else
			{
				m_listMember.DeleteItem(j);//用户退出会议就删除此人
				continue;
			}
			
		}
		else if(pMem[i].enState != CALL_E_CONF_ATTENDEE_OUT)//Add condition statement by w00321336 for DTS2015010706285 at 2015-1-20: stop to insert deleting attendee again 
		{			
			int iSize = m_listMember.GetItemCount();
			m_listMember.InsertItem(iSize,L"");
			j = iSize;
		}

		//Add by w00321336 for DTS2015010706187 at 2015-1-22 begin
		IM_S_USERINFO userInfo;
		if(!GetTargetUserInfo(pMem[i].acAttendeeNumber, userInfo))
		{
			AfxMessageBox(_T("Get target user info failed by bind no."));
		}

		m_listMember.SetItemText(j, COL_MEM_Name, CTools::UTF2UNICODE(userInfo.name));
		m_listMember.SetItemText(j, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(userInfo.account));
		//Add by w00321336 for DTS2015010706187 at 2015-1-22 end

		m_listMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
		m_listMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);
		if(pMem[i].enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
		{
			m_listMember.SetItemText(j,COL_MEM_Compere,L"主席");
		}

		if(pMem[i].ulRight != 1)
		{
			m_listMember.SetItemText(j,COL_MEM_MUTE,L"静音");
		}
		else
		{
			m_listMember.SetItemText(j,COL_MEM_MUTE,L"未静音");
		}
		m_listMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);


	}
	if(uiSize>1)
	{
		SAFE_DELETE(pMem);
	}
	else
	{
		delete[] pMem;
		pMem = NULL;
	}
	
	return 0L;
}


void CConfDlg::OnBnClickedButtonMute()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstr;
	m_btnMute.GetWindowText(cstr);
	if(cstr.Compare(L"会场静音") == 0)
	{
		tup_call_serverconf_mute(m_uiConfID,TUP_TRUE);
		m_btnMute.SetWindowText(L"取消静音");
	}
	else
	{
		tup_call_serverconf_mute(m_uiConfID,TUP_FALSE);
		m_btnMute.SetWindowText(L"会场静音");
	}
}

void CConfDlg::OnBnClickedButtonLock()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstr;
	m_btnLock.GetWindowText(cstr);
	if(cstr.Compare(L"会场锁定")  == 0)
	{
		tup_call_serverconf_lock(m_uiConfID,TUP_TRUE);
		m_btnLock.SetWindowText(L"取消锁定");
		m_btnAdd.EnableWindow(FALSE);
	}
	else
	{
		tup_call_serverconf_lock(m_uiConfID,TUP_FALSE);
		m_btnLock.SetWindowText(L"会场锁定");
		m_btnAdd.EnableWindow(TRUE);
	}
}

void CConfDlg::OnBnClickedButtonHold()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstr;
	m_btnHold.GetWindowText(cstr);
	if(cstr.Compare(L"会议保持") == 0)
	{
		tup_call_serverconf_hold(m_uiConfID);
		m_btnHold.SetWindowText(L"取消保持");
	}
	else
	{
		tup_call_serverconf_unhold(m_uiConfID);
		m_btnHold.SetWindowText(L"会议保持");
	}
}

void CConfDlg::OnBnClickedButtonSub()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CConfDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelectDlg dlg;
	if(IDOK != dlg.DoModal())
	{
		return;
	}

	MAP_SELECT_USER selUser;
	dlg.GetSelectUser(selUser);	
	int iSize = selUser.size();
	if(iSize == 0)
	{
		return;		
	}

	CString cstrName;
	m_stcName.GetWindowText(cstrName);
	MAP_SELECT_USER::iterator it = selUser.begin();
	MAP_SELECT_USER::iterator itEnd = selUser.end();
	for(;it!=itEnd;it++)
	{	
		std::string strCallno = it->second.CallNo;
		CString cstrNum = CTools::UTF2UNICODE(strCallno);
		//添加会议成员
		int j = -1;
		if(!FindColum(cstrNum,COL_MEM_CALLNO,j))
		{
			tup_call_serverconf_add_attendee(m_uiConfID,1,strCallno.c_str(),strCallno.size()+1);
		}
	}


}
BOOL CConfDlg::FindColum(const CString& cstrKey,int iColnum,int& iFind)
{
	int iSize = m_listMember.GetItemCount();
	for(int i = 0; i< iSize; i++)
	{
		if(cstrKey.Compare(m_listMember.GetItemText(i,iColnum)) == 0)
		{
			iFind = i;
			return TRUE;
		}
	}
	return FALSE;
}
void CConfDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if(!isChairman)
	{
		return;
	}

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_listMember.ScreenToClient(&pt);

	UINT uFlag = 0;
	int hSelectedItem = m_listMember.HitTest(pt,&uFlag);
	if (0 <= hSelectedItem)
	{
		CMenu menu;
		menu.CreatePopupMenu();

		menu.AppendMenu(MF_STRING, ID_CONF_DEL_MEM_MENU, _T("移除与会者"));

		//Modified by w00321336 to disable this item when it's a chairman at 2015-1-20 begin
		CString strCompere = m_listMember.GetItemText(hSelectedItem, COL_MEM_Compere);
		if (strCompere.Compare(L"主席") == 0)
		{
			menu.EnableMenuItem(ID_CONF_DEL_MEM_MENU, MF_DISABLED|MF_GRAYED);
		}
		//Modified by w00321336 end

		CString cstrCallState = m_listMember.GetItemText(hSelectedItem,COL_MEM_CALLSTATE);
		if(cstrCallState == L"会议中")
		{
			CString cstrMute = m_listMember.GetItemText(hSelectedItem,COL_MEM_MUTE);
			if(cstrMute != L"静音")
			{
				menu.AppendMenu(MF_STRING, ID_CONF_MUTE_MEM_MENU, _T("静音"));
			}
			else
			{
				menu.AppendMenu(MF_STRING, ID_CONF_UNMUTE_MEM_MENU, _T("取消静音"));
			}
		}
		else
		{
			menu.AppendMenu(MF_STRING, ID_CONF_RECALL_MEM_MENU, _T("重新发起呼叫"));
		}
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);		                 
	}

	
}
void CConfDlg::OnClickListMemMenuItem(UINT nID)
{
	int nItem = -1;
	POSITION pos = m_listMember.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	else
	{
		while (pos)
		{
			nItem = m_listMember.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			break;
		}
	}
	CString cstrAccount = m_listMember.GetItemText(nItem,COL_MEM_ACCOUNT);
	CString cstrBindNo = m_listMember.GetItemText(nItem,COL_MEM_CALLNO);
	std::string strCallNo = CTools::UNICODE2UTF(cstrBindNo);
	if(nID == ID_CONF_DEL_MEM_MENU)
	{
		tup_call_serverconf_kick_attendee(m_uiConfID,strCallNo.c_str());
		//Add by w00321336 to fix DTS2015010706285: Remove attendee from list at 2015-01-20 begin
		::SendMessage(m_listMember.m_hWnd, LVM_DELETEITEM, nItem, 0);;
		//Add by w00321336 to fix DTS2015010706285 end
	}
	else if(nID == ID_CONF_RECALL_MEM_MENU)
	{
		tup_call_serverconf_add_attendee(m_uiConfID,1,strCallNo.c_str(),strCallNo.size()+1);
	}
	else if(nID == ID_CONF_MUTE_MEM_MENU)
	{
		tup_call_serverconf_modify_right(m_uiConfID,strCallNo.c_str(),0);
	}
	else if(nID == ID_CONF_UNMUTE_MEM_MENU)
	{
		tup_call_serverconf_modify_right(m_uiConfID,strCallNo.c_str(),1);
	}
}
void CConfDlg::OnBnClickedButtonDataconf()
{
	// TODO: 在此添加控件通知处理程序代码
	tup_call_serverconf_transferto_dataconf(m_uiConfID);
}

void CConfDlg::CloseDlg()
{
	/////数据清零////
	m_uiConfID = 0;
	m_uiCallID = 0;
	isChairman = false;
	OnOK();
}

void CConfDlg::PubSelfStatus(IM_E_USER_ONLINESTATUS _status)
{
	IM_S_STATUSARG arg;
	CTools::CString2Char(L"desc",arg.desc,IM_D_MAX_STATUS_DESCLEN);
	arg.status = _status;
	tup_im_publishstatus(&arg);
}