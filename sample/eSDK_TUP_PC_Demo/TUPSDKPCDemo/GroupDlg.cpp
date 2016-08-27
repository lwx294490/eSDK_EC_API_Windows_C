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

// GroupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "GroupDlg.h"
#include "Tools.h"

// CGroupDlg 对话框

IMPLEMENT_DYNAMIC(CGroupDlg, CDialog)

CGroupDlg::CGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupDlg::IDD, pParent)
{
	m_pGroupAddDlg = NULL;
	m_pGroupSearchDlg = NULL;
}

CGroupDlg::~CGroupDlg()
{
}

void CGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_FIXGROUP, m_treeFixedGroup);
}


BEGIN_MESSAGE_MAP(CGroupDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDGROUP, &CGroupDlg::OnBnClickedButtonAddgroup)
	ON_BN_CLICKED(IDC_BUTTON_FINDGROUP, &CGroupDlg::OnBnClickedButtonFindgroup)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_FIXGROUP, &CGroupDlg::OnNMDblclkTreeGroup)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_FIXGROUP, &CGroupDlg::OnNMRClickTreeGroup)
	ON_COMMAND_RANGE(ID_GROUP_RELEASE_MEM_MENU,ID_GROUP_ADD_MENU ,&CGroupDlg::OnClickGroupMenuItem)
END_MESSAGE_MAP()


// CGroupDlg 消息处理程序

BOOL CGroupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(NULL == m_pGroupAddDlg)
	{
		m_pGroupAddDlg = new CGroupAddDlg(this);
		if(!::IsWindow(m_pGroupAddDlg->GetSafeHwnd()))
		{
			m_pGroupAddDlg->Create(IDD_GROUP_ADD_DIALOG);
		}
	}
	UpdateGroupListContrl();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CGroupDlg::PreTranslateMessage(MSG* pMsg)
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

void CGroupDlg::OnBnClickedButtonAddgroup()
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL == m_pGroupAddDlg)
	{
		m_pGroupAddDlg = new CGroupAddDlg(this);
		if(!::IsWindow(m_pGroupAddDlg->GetSafeHwnd()))
		{
			m_pGroupAddDlg->Create(IDD_GROUP_ADD_DIALOG);
		}
	}
	if(NULL!=m_pGroupAddDlg)
	{
		CTools::CString2Char(_T(""),m_pGroupAddDlg->m_id,IM_D_GROUPID_LENGTH);
		m_pGroupAddDlg->m_groupName = _T("");
		m_pGroupAddDlg->m_groupSynopsis = _T("");
		m_pGroupAddDlg->m_groupDescription = _T("");
		m_pGroupAddDlg->m_groupMemberList.DeleteAllItems();
		m_pGroupAddDlg->m_radioBtnGroup.SetCheck(true);
		m_pGroupAddDlg->m_radioBtnGroup1.SetCheck(false);
		m_pGroupAddDlg->UpdateData(FALSE);
		m_pGroupAddDlg->ShowWindow(SW_SHOW);
	}
}

void CGroupDlg::OnBnClickedButtonFindgroup()
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL == m_pGroupSearchDlg)
	{
		m_pGroupSearchDlg = new CGroupSearchDlg();
		if(!::IsWindow(m_pGroupSearchDlg->GetSafeHwnd()))
		{
			m_pGroupSearchDlg->Create(IDD_GROUP_SEARCH_DIALOG);
		}
	}
	if(NULL!=m_pGroupSearchDlg)
	{
		m_pGroupSearchDlg->m_groupSearch.Format(_T(""));
		m_pGroupSearchDlg->m_groupSearchList.DeleteAllItems();
		m_pGroupSearchDlg->UpdateData(FALSE);
		m_pGroupSearchDlg->ShowWindow(SW_SHOW);
	}

}

void CGroupDlg::UpdateGroupListContrl()
{
	m_treeFixedGroup.DeleteAllItems();
	TUP_INT64 cstr;

	typedef std::map<TUP_INT64,HTREEITEM> MAP_GROUPTREE;
	
	//插入所有群组
	MAP_IMGROUP::iterator itGroup = g_mapImGroup.begin();
	MAP_IMGROUP::iterator itEnd = g_mapImGroup.end();
	for(;itGroup!=itEnd;itGroup++)
	{
		IM_S_IMGROUPINFO group = (IM_S_IMGROUPINFO)itGroup->second;
		CString cstrGroupName = CTools::UTF2UNICODE(group.name);
		HTREEITEM item = m_treeFixedGroup.InsertItem(cstrGroupName,TVI_ROOT);
		cstr = CTools::str2num(group.id);
		m_treeFixedGroup.SetItemData(item,(DWORD)cstr);
		m_treeFixedGroup.SetItemImage(item, 2, 2);
	}
}

void CGroupDlg::OnNMDblclkTreeGroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CPoint pt;
	::GetCursorPos(&pt);
	m_treeFixedGroup.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeFixedGroup.HitTest(pt,&uFlag);
	if(NULL != hSelectedItem)
	{
		//////双击默认打开该处的群组，并发起对话///////
		HTREEITEM item = m_treeFixedGroup.GetSelectedItem();
		TUP_INT64 groupID;
		if(NULL != item)
		{
			groupID =(TUP_INT64)m_treeFixedGroup.GetItemData(item);
		}
		else
		{
			return;
		}

		IM_S_IMGROUPINFO groupInfo = g_mapImGroup[groupID];

		if(groupInfo.id != 0)
		{
			IM_S_IMGROUPINFO* pUserInfo= new IM_S_IMGROUPINFO;
			IM_S_IMGROUPINFO userInfo = g_mapImGroup[groupID];
			memcpy(pUserInfo,&userInfo,sizeof(IM_S_IMGROUPINFO));
			::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_MENU_GROUP_CHAT,NULL,(LPARAM)pUserInfo);
		}
	}
	
}

void CGroupDlg::OnNMRClickTreeGroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CPoint pt, pmenu;
	TUP_INT64 groupID;
	IM_S_IMGROUPINFO ack;
	CString admin;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_treeFixedGroup.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeFixedGroup.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_GROUP_ADD_MENU, _T("新建群"));	
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
		return;
	}

	m_treeFixedGroup.SelectItem(hSelectedItem);

	CMenu menu;
	menu.CreatePopupMenu();
	HTREEITEM item = m_treeFixedGroup.GetSelectedItem();
	groupID =(TUP_INT64)m_treeFixedGroup.GetItemData(item);
	TUP_RESULT tRet = tup_im_getfixedgroupdetail(CTools::num2str(groupID).c_str(),&ack);
	if (TUP_FAIL == tRet)
	{
		AfxMessageBox(_T("tup_im_getfixedgroupdetail fail"));
	}
	else
	{
		admin = CTools::UTF2UNICODE(ack.owner);
		if(0 == admin.Compare(CTools::UTF2UNICODE(g_Account)))
		{
			menu.AppendMenu(MF_STRING, ID_GROUP_ADD_MEMBER_MENU, _T("添加成员"));
			menu.AppendMenu(MF_STRING, ID_GROUP_RELEASE_MEM_MENU, _T("解散群组"));
		}
		else
		{
			menu.AppendMenu(MF_STRING, ID_GROUP_EXIT_MENU, _T("退出群组"));
		}
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
}

void CGroupDlg::OnClickGroupMenuItem(UINT nID)
{
	HTREEITEM item = m_treeFixedGroup.GetSelectedItem();
	TUP_INT64 groupID;
	std::string id;
	if(NULL != item)
	{
		groupID = (TUP_INT64)m_treeFixedGroup.GetItemData(item);
		id = CTools::num2str(groupID);
	}

	switch (nID)
	{

	case ID_GROUP_RELEASE_MEM_MENU:
		{
			//解散群组
			TUP_BOOL bisRet = false;
			TUP_RESULT delfixedgroupRet = tup_im_delfixedgroup(id.c_str(), &bisRet);
		}
		break;
	case ID_GROUP_ADD_MEMBER_MENU:
		{
			TUP_CHAR groupid[IM_D_GROUPID_LENGTH] ={0};
			strncpy(groupid,id.c_str(),IM_D_GROUPID_LENGTH-1);
			OnAddGroupMember(groupid);
		}
		break;
	case ID_GROUP_ADD_MENU:
		{
			OnBnClickedButtonAddgroup();
		}
		break;
	case ID_GROUP_EXIT_MENU:
		{
			if(TUP_SUCCESS != tup_im_leavefixedgroup (id.c_str()))
			{
				return;
			}
		}
		break;

	}
	if(m_pGroupAddDlg)
	{
		m_pGroupAddDlg->GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
	}
	UpdateGroupListContrl();
}

void CGroupDlg::OnAddGroupMember(TUP_CHAR* id)
{
	if(m_pGroupAddDlg)
	{
		IM_S_REQUESTIMGROUPMEMBERS_ARG arg;
		IM_S_GROUPUSERLIST ack;
		int i=0;
		IM_S_IMGROUPINFO groupDetail;
		TUP_RESULT Ret = tup_im_getfixedgroupdetail (id, &groupDetail);
		if(TUP_SUCCESS == Ret)
		{
			m_pGroupAddDlg->m_groupName = CTools::UTF2UNICODE(groupDetail.name);
			m_pGroupAddDlg->m_groupDescription = CTools::UTF2UNICODE(groupDetail.manifesto);
			m_pGroupAddDlg->m_groupSynopsis = CTools::UTF2UNICODE(groupDetail.desc);
			if(groupDetail.autoJoinFlag == IM_E_IMGROUP_JOIN_AUTO)
			{
				m_pGroupAddDlg->m_radioBtnGroup.SetCheck(TRUE);
			}
			else
			{
				m_pGroupAddDlg->m_radioBtnGroup1.SetCheck(TRUE);
			}
			m_pGroupAddDlg->UpdateData(FALSE);
		}
		arg.isSyncAll = false;
		CTools::CString2Char(L"19000000000000",arg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH);
		strcpy_s( arg.groupID, sizeof(arg.groupID),id);
		TUP_RESULT getRst = tup_im_getfixedgroupmembers(&arg, &ack);
		if(TUP_SUCCESS == getRst)
		{
			LONG lStyle;
			lStyle = GetWindowLong(m_pGroupAddDlg->m_groupMemberList.m_hWnd, GWL_STYLE);//获取当前窗口style
			lStyle &= ~LVS_TYPEMASK; //清除显示方式位
			lStyle |= LVS_REPORT; //设置style
			SetWindowLong(m_pGroupAddDlg->m_groupMemberList.m_hWnd, GWL_STYLE, lStyle);//设置style

			DWORD dwStyle =m_pGroupAddDlg->m_groupMemberList.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
			dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
			//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
			m_pGroupAddDlg->m_groupMemberList.SetExtendedStyle(dwStyle); //设置扩展风格
			m_pGroupAddDlg->m_groupMemberList.InsertColumn( 0, CTools::UTF2UNICODE(g_Account), LVCFMT_LEFT, 290);//插入列
			TUP_S_LIST* list =  ack.memberInfo;
			while(list != NULL)
			{
				IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
				if(NULL != groupUser)
				{
					CString cstrAccount = CTools::UTF2UNICODE(groupUser->account);
					if(cstrAccount.Compare(CTools::UTF2UNICODE(g_Account)))
					{
						int nRow = m_pGroupAddDlg->m_groupMemberList.InsertItem(i, cstrAccount);//插入行
						//m_pGroupAddDlg->m_groupMemberList.SetItemText(nRow, 1, _T("jacky"));//设置数据
						i++;
					}
				}
				list = list->next;
			}
		}
		tup_im_release_tup_list(ack.memberInfo);
		strncpy(m_pGroupAddDlg->m_id, id,IM_D_GROUPID_LENGTH-1);
		m_pGroupAddDlg->ShowWindow(SW_HIDE);
		m_pGroupAddDlg->OnBnClickedButtonAddmembers();
		m_pGroupAddDlg->OnBnClickedOk();
	}
}