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

// ConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_CONF_Demo.h"
#include "ConfDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include <string.h>

// ConfDlg dialog

IMPLEMENT_DYNAMIC(ConfDlg, CDialogEx)

ConfDlg::ConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConfDlg::IDD, pParent)
{
	m_ulConfID = 0;
	m_ulCallID = 0;
	acGroupUri.clear();
}

ConfDlg::~ConfDlg()
{
}

void ConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listMember);
	DDX_Control(pDX, IDC_ST_CONFNAME, m_strConfName);
	DDX_Control(pDX, IDC_EDIT1, m_AccountName);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_strAccount);
}


BEGIN_MESSAGE_MAP(ConfDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &ConfDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &ConfDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &ConfDlg::OnNMRClickList1)
	ON_COMMAND(ID_DELETE, &ConfDlg::OnDelete)
	ON_BN_CLICKED(IDC_ENDCONF, &ConfDlg::OnClickedEndconf)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ONEKEY_TO_CONF_RESULT, &ConfDlg::OnOnekeyToConfResult)
END_MESSAGE_MAP()


// ConfDlg message handlers


BOOL ConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_strConfName.SetWindowText(_T("会议成员列表"));
	//////设置列表框状态//////
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
	// EXCEPTION: OCX Property Pages should return FALSE
}


void ConfDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	if(m_ulCallID != 0)
	{
		tup_call_end_call(m_ulCallID);		//结束和其他用户的通话或者结束来电。
		m_ulCallID = 0;
	}
	if (m_ulConfID != 0)
	{
		tup_call_serverconf_leave(m_ulConfID);		//调用者离开会议，会议继续进行
		m_ulConfID = 0;
	}
	m_listMember.DeleteAllItems();
	m_strConfName.SetWindowText(_T(""));
	acGroupUri.clear();

	//CDialogEx::OnCancel();
	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
}
void ConfDlg::SetConfPara(std::string GropnUrl,TUP_UINT32 ulConfID)
{
	m_ulConfID = ulConfID;
	if (!GropnUrl.empty())
	{
		InitConfMember(GropnUrl);
	}
	
}

void ConfDlg::SetCallID(TUP_UINT32 ulCallID,std::string subject)
{
	m_strConfName.SetWindowText(CString(subject.c_str()));
	m_ulCallID = ulCallID;
}

void ConfDlg::InitConfMember(std::string strGroupID)
{
	m_listMember.DeleteAllItems();

	IM_S_REQUESTIMGROUPMEMBERS_ARG groupMembArg;
	IM_S_GROUPUSERLIST groupList;

	strcpy_s(groupMembArg.groupID,IM_D_GROUPID_LENGTH,strGroupID.c_str());
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
					list = NULL;
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
			groupUser = NULL;
		}
		list = list->next;
	}
}

void ConfDlg::RefreshMember(CALL_S_CONF_MEMBER* confMember,TUP_UINT32 memberCount)
{
	int j = -1;
	for (int i = 0;i<memberCount;i++)
	{
		/////依次刷新/////
		CString cstrConfState;
		switch (confMember[i].enState)
		{
		    case CALL_E_CONF_ATTENDEE_INVITING:
				{
					cstrConfState = L"邀请中";
					break;
				}
			case CALL_E_CONF_ATTENDEE_INCONF:
				{
					cstrConfState = L"会议中";
					IM_S_USERINFO userInfo;
					if(!GetTargetUserInfo(confMember[i].acAttendeeNumber, userInfo))
					{
						AfxMessageBox(_T("Get target user info failed by bind no."));
						return;
					}
					CString cstrNum = CTools::UTF2UNICODE(confMember[i].acAttendeeNumber);
					if (!FindColum(cstrNum,COL_MEM_CALLNO,j))	//若与会人员中找不到此人，则把他添加到与会人员列表
					{
						int iSize = m_listMember.GetItemCount();
						m_listMember.InsertItem(iSize,L"");
						j = iSize;
					}
					else	//若与会人员中找到此人，则更新他的状态
					{
					}
					m_listMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
					m_listMember.SetItemText(j, COL_MEM_Name, CTools::UTF2UNICODE(userInfo.name));
					m_listMember.SetItemText(j, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(userInfo.account));
					//Add by w00321336 for DTS2015010706187 at 2015-1-22 end

					m_listMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
					m_listMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);
					if(confMember[i].enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
					{
						m_listMember.SetItemText(j,COL_MEM_Compere,L"主席");
					}
					CString cstrAccount;
					m_strAccount.GetWindowText(cstrAccount);
					if ( cstrAccount == CTools::UTF2UNICODE(userInfo.account) )
					{
						if(confMember[i].enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
						{
							m_bIsChairMan = true;
							m_AccountName.EnableWindow(true);
							GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
							GetDlgItem(IDC_ENDCONF)->EnableWindow(true);
						}
						else
						{
							m_bIsChairMan = false;
							m_AccountName.EnableWindow(false);
							GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
							GetDlgItem(IDC_ENDCONF)->EnableWindow(false);
						}
					}

					if(confMember[i].ulRight != 1)
					{
						m_listMember.SetItemText(j,COL_MEM_MUTE,L"静音");
					}
					else
					{
						m_listMember.SetItemText(j,COL_MEM_MUTE,L"未静音");
					}
					m_listMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);
					break;
				}
			case CALL_E_CONF_ATTENDEE_INVITE_FAIL:
				{
					cstrConfState = L"邀请失败";
					break;
				}
			case CALL_E_CONF_ATTENDEE_OUT:
				{	
					cstrConfState = L"退出会议";
					CString cstrNum = CTools::UTF2UNICODE(confMember[i].acAttendeeNumber);
					if(FindColum(cstrNum,COL_MEM_CALLNO,j))	////找到联系人，但是联系人的状态是out
					{
						m_listMember.DeleteItem(j);//用户退出会议就删除此人
					}
					break;
				}
			default:
				{
					cstrConfState = L"添加失败";
					break;
				}
		}
	}
}

BOOL ConfDlg::FindColum(const CString& cstrKey,int iColnum,int& iFind)
{
	if ( NULL != m_listMember.m_hWnd )
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
	}
	return FALSE;
}

bool ConfDlg::GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)
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

	IM_S_USERINFO userQueryAck;
	if(!GetUserInfoFromList(ack, acTelNum, userQueryAck))
	{
		return false;
	}

	userInfo = userQueryAck;
	tup_im_release_tup_list(ack.userList);
	return true;
}
bool ConfDlg::GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack, const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)
{
	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL != pUser)
		{
			IM_S_USERINFO curUserInfo;
			memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));
			pUser = NULL;
			//accurate search
			if (strcmp(curUserInfo.bindNO, acTelNum) == 0)
			{
				userInfo = curUserInfo;
				pUserList = NULL;
				bRet = true;
				break;
			}
		}
		pUserList = pUserList->next;
	}

	return bRet;
}

void ConfDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CString cstrKey;
	m_AccountName.GetWindowText(cstrKey);
	cstrKey.MakeLower();  //转换成小写

	IM_S_QUERY_ENTADDRESSBOOK_ARG entArg;
	entArg.isNeedAmount = TUP_TRUE;
	entArg.deptID = 0;
	entArg.orderType = IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN;
	entArg.orderModel = IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC;
	entArg.offset = -20;
	entArg.count = 20;
	CTools::CString2Char(cstrKey,entArg.queryKey,IM_D_MAX_DESC_LENGTH);
	IM_S_QUERY_ENTADDRESSBOOK_ACK entAck;
	memset(&entAck,0,sizeof(IM_S_QUERY_ENTADDRESSBOOK_ACK));

	TUP_RESULT tRet = tup_im_queryentaddressbook(&entArg,&entAck);
	if ( TUP_SUCCESS != tRet )
	{
		AfxMessageBox(_T("tup_im_queryentaddressbook failed!"));
		tup_im_release_tup_list(entAck.userList);
		return;
	}

	//m_ulStaffSize = entAck.recordAmount;
	//RefreshPageSize();

	TUP_S_LIST* pUserItem = entAck.userList;
	if ( NULL == pUserItem )
	{
		AfxMessageBox(_T("Account not exist!"));
		tup_im_release_tup_list(entAck.userList);
		return;
	}

	std::string strCallNO;
	while(NULL != pUserItem)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserItem->data;
		if(NULL != pUser)
		{
			if ( 0 == strcmp( pUser->account, entArg.queryKey ) )
			{
				strCallNO = pUser->bindNO;
				pUserItem = NULL;
				pUser = NULL;
				break;
			}
			pUser = NULL;
		}
		pUserItem = pUserItem->next;
	}
	//////释放IM_S_QUERY_ENTADDRESSBOOK_ACK中的tuplist指针////
	tup_im_release_tup_list(entAck.userList);

	if ( strCallNO == "" )
	{
		AfxMessageBox(_T("Account not match!"));
		return;
	}
	int iListMemberSize = m_listMember.GetItemCount();
	for ( int i = 0; i < iListMemberSize; i++ )
	{
		CString cstrMemberId = m_listMember.GetItemText(i,COL_MEM_CALLNO);
		CString cstrMemberState = m_listMember.GetItemText(i,COL_MEM_CALLSTATE);
		CString cstrCallNo;
		CTools::string2CString(strCallNO,cstrCallNo);
		if ( cstrMemberId == cstrCallNo && cstrMemberState == L"会议中" )
		{
			AfxMessageBox(_T("Account already in conference!"));
			return;
		}
	}

	// confid:会议ID
	// count:成员个数
	// number:成员号码组
	// persize:数组成员长度 
	tRet = tup_call_serverconf_add_attendee(m_ulConfID, 1, strCallNO.c_str(), strCallNO.size() + 1);
	if ( TUP_SUCCESS != tRet )
	{
		AfxMessageBox(_T("tup_call_serverconf_add_attendee failed!"));
		return;
	}
	else
	{
		AfxMessageBox(_T("操作成功"));
		return;
	}
}


void ConfDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	// 防止在空白区点击弹出菜单
	if (m_listMember.GetSelectedCount() <= 0)
	{
		return;
	}

	if ( true == m_bIsChairMan )
	{
		CPoint hitPt;
		::GetCursorPos(&hitPt);
		CMenu menu;
		menu.LoadMenu(IDR_MENU2);
		if ( NULL != menu.m_hMenu )
		{
			CMenu *pop = menu.GetSubMenu(0);
			if ( NULL != pop )
			{
				pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, hitPt.x, hitPt.y, this);
			}
		}
	}

	*pResult = 0;
}


void ConfDlg::OnDelete()
{
	// TODO: Add your command handler code here
	//////一键删除成员/////
	//1.获取选中的成员信息////
	int nRow = m_listMember.GetNextItem(-1, LVIS_SELECTED);
	//获得成员的ID号
	CString cstrCallNo = m_listMember.GetItemText(nRow,COL_MEM_CALLNO);

	TUP_CHAR ctrCallNo[31] = {0};
	CTools::CString2Char(cstrCallNo, ctrCallNo, sizeof(ctrCallNo)/sizeof(*ctrCallNo));

	//m_uiConfID:会议ID
	//strCallNo:被移除的成员ID，长度小于32
	TUP_RESULT tRet = tup_call_serverconf_kick_attendee(m_ulConfID,ctrCallNo);
	if (tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("Kick attendee failed"));
		return ;
	}
}


void ConfDlg::OnClickedEndconf()
{
	// TODO: Add your control notification handler code here
	//if ( CALL_E_SERVERCONF_AUDIO == m_ConfType )
	//{
		if ( 0 != m_ulCallID )
		{
			TUP_RESULT tRet = tup_call_end_call(m_ulCallID);
			if ( TUP_SUCCESS != tRet )	//结束和其他用户的通话或者结束来电。
			{
				AfxMessageBox(_T("Close call failed"));
				return ;
			}
			else
			{
				m_ulCallID = 0;
			}
		}
		if ( 0 != m_ulConfID )	//语音会议
		{
			TUP_RESULT tRet = tup_call_serverconf_end(m_ulConfID);	//关闭数据会议
			if ( TUP_SUCCESS != tRet )
			{
				AfxMessageBox(_T("Close conference failed"));
				return ;
			}
			else
			{
				m_ulConfID = 0;
			}
		}
		else
		{
			m_listMember.DeleteAllItems();
			m_strConfName.SetWindowText(_T(""));
			acGroupUri.clear();

			CWnd::DestroyWindow();
			CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
			if ( NULL != pMainDlg )
			{
				pMainDlg->m_bInConference = false;
			}
		}
	//}
	//else if ( CALL_E_SERVERCONF_DATA == m_ConfType )
	//{
	//	if ( 0 != m_ulConfID )	//数据会议
	//	{
	//		TUP_RESULT tRet = tup_call_serverconf_end(m_ulConfID);	//关闭数据会议
	//		if ( TUP_SUCCESS != tRet )
	//		{
	//			AfxMessageBox(_T("Close conference failed"));
	//			return ;
	//		}
	//	}
	//}
}


void ConfDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(m_ulCallID != 0)
	{
		tup_call_end_call(m_ulCallID);		//结束和其他用户的通话或者结束来电。
		m_ulCallID = 0;
	}
	if (m_ulConfID != 0)
	{
		tup_call_serverconf_leave(m_ulConfID);		//调用者离开会议，会议继续进行
		m_ulConfID = 0;
	}
	m_listMember.DeleteAllItems();
	m_strConfName.SetWindowText(_T(""));
	acGroupUri.clear();

	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
	//CDialogEx::OnClose();
}


void ConfDlg::SetConfType(CALL_E_SERVERCONF_TYPE ConfType)
{
	m_ConfType = ConfType;
}


void ConfDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
	//CDialogEx::OnCancel();
}


afx_msg LRESULT ConfDlg::OnOnekeyToConfResult(WPARAM wParam, LPARAM lParam)
{
	TUP_UINT32 uiResult = (TUP_UINT32)lParam;
	if ( uiResult != 0 )
	{
		AfxMessageBox(_T("join in conference failed,please close conference dialog and try again!"));
	}
	return 0;
}
