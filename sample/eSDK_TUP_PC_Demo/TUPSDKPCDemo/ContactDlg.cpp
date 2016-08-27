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

// ContactDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "ContactDlg.h"
#include "Tools.h"
#include "UserGroupDlg.h"


// CContactDlg 对话框

IMPLEMENT_DYNAMIC(CContactDlg, CDialog)

CContactDlg::CContactDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContactDlg::IDD, pParent)
{
	LocalStatus.clear();
}

CContactDlg::~CContactDlg()
{
}

void CContactDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONTACT, m_treeContact);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
}


BEGIN_MESSAGE_MAP(CContactDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CContactDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_CONTACT, &CContactDlg::OnNMDblclkTreeContact)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_CONTACT, &CContactDlg::OnNMRClickTreeContact)
	ON_COMMAND_RANGE(ID_PRIGROUP_MODIFY_MENU, ID_PRIGROUP_ADD_UC_CONTACT_MENU, &CContactDlg::OnClickPriGroupMenuItem)
	ON_COMMAND_RANGE(ID_PRIGROUP_DEL_CONTACT_MENU, ID_PRIGROUP_CONTACT_MOVE_MENU_END, &CContactDlg::OnClickPriContactMenuItem)
	ON_MESSAGE(WM_UPDATE_CONTACT,&CContactDlg::OnUpdateConatct)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CONTACT, &CContactDlg::OnNMClickTreeContact)
END_MESSAGE_MAP()


// CContactDlg 消息处理程序

void CContactDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	m_btnAdd.GetWindowRect(&rc);
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_MENU, _T("新建分组"));	
	menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_CONTACT_MENU, _T("新建联系人"));
	menu.TrackPopupMenu(TPM_TOPALIGN, rc.left, rc.bottom, this);
}

BOOL CContactDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 状态图片列表
	m_imageList.Create(16, 16, ILC_COLORDDB, 4, 1);
	AddImage(m_imageList, IDB_BITMAP_FRIEND);		               //0
	AddImage(m_imageList, IDB_BITMAP_CUSCONTACT);                  //1 离线等状态选择该标记
	AddImage(m_imageList, IDB_BITMAP_UNFOLD);                      //2
	AddImage(m_imageList, IDB_BITMAP_FOLD);                        //3
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_Busy));         ////4忙碌状态标记
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_Oline));       ////5在线状态标记///////
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_Leave));       ////6在离开态标记///////
	m_treeContact.SetImageList(&m_imageList,LVSIL_NORMAL );
	

	GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
	
	UpdateContactListContrl();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CContactDlg::AddImage(CImageList& imageList, UINT _id)
{
	CBitmap bm;
	bm.LoadBitmap(_id);
	imageList.Add(&bm,RGB(0, 0, 0));
}

void CContactDlg::GetContactList(MAP_GROUP& mapGroup,MAP_USER_GROUP& mapUserGroup,MAP_CONTACT& mapContact,MAP_USER& mapUser,MAP_IMGROUP& mapImGroup)
{
	mapGroup.clear();
	mapUserGroup.clear();
	mapUser.clear();
	mapContact.clear();
	mapImGroup.clear();


	IM_S_GETCONTACTLIST_ARG arg;
	IM_S_GETCONTACTLIST_ACK ack;
	arg.isSyncAll = TUP_TRUE;
	CTools::CString2Char(L"19000000000000",arg.timestamp,IM_D_MAX_TIMESTAMP_LENGTH);
	TUP_RESULT tRet = tup_im_getcontactlist(&arg,&ack);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getcontactlist failed."));
		return;
	}

	//获取所有联系人分组
	TUP_S_LIST* pGroupList =  ack.userGroupList;
	while(NULL != pGroupList)
	{
		IM_S_USERGROUPINFO* pGroupInfo = (IM_S_USERGROUPINFO*)pGroupList->data;
		if(NULL == pGroupInfo)
		{
			continue;
		}

		IM_S_USERGROUPINFO GroupInfo;
		memset(&GroupInfo,0,sizeof(IM_S_USERGROUPINFO));
		memcpy(&GroupInfo,pGroupInfo,sizeof(IM_S_USERGROUPINFO));

		mapGroup[pGroupInfo->id] = GroupInfo;

		pGroupList = pGroupList->next;
	}

	//获取分组和联系人的对应关系
	TUP_S_LIST* pUserGroupMemberList =  ack.userGroupMemberList;
	while(NULL != pUserGroupMemberList)
	{
		IM_S_USERGROUPMEMBERINFO* pUserGroup = (IM_S_USERGROUPMEMBERINFO*)pUserGroupMemberList->data;
		if(NULL == pUserGroup)
		{
			continue;
		}
		mapUserGroup.insert(std::make_pair(pUserGroup->contactID,pUserGroup->groupID));

		pUserGroupMemberList = pUserGroupMemberList->next;
	}

	//获取分组和联系人的对应关系
	TUP_S_LIST* pContactList =  ack.contactList;
	while(NULL != pContactList)
	{
		IM_S_CONTACTNFO* pContactInfo = (IM_S_CONTACTNFO*)pContactList->data;
		if(NULL == pContactInfo)
		{
			continue;
		}
		IM_S_CONTACTNFO contact;
		memset(&contact,0,sizeof(IM_S_CONTACTNFO));
		memcpy(&contact,pContactInfo,sizeof(IM_S_CONTACTNFO));
		mapContact[pContactInfo->id] = contact;

		pContactList = pContactList->next;
	}

	//
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}
		IM_S_USERINFO userInfo;
		memset(&userInfo,0,sizeof(IM_S_USERINFO));
		memcpy(&userInfo,pUser,sizeof(IM_S_USERINFO));
		mapUser[pUser->staffID] = userInfo;
		pUserList = pUserList->next;
	}

	//获取固定群列表
	TUP_S_LIST* PImGroupList = ack.imGroupList;
	while(NULL!=PImGroupList)
	{
		IM_S_IMGROUPINFO* pGroups = (IM_S_IMGROUPINFO*)PImGroupList->data;
		if(NULL == pGroups)
		{
			continue;
		}
		IM_S_IMGROUPINFO imgroupInfo;
		memset(&imgroupInfo,0,sizeof(IM_S_IMGROUPINFO));
		memcpy(&imgroupInfo,pGroups,sizeof(IM_S_IMGROUPINFO));
		if(IM_E_IMGROUP_FIXGROUP_TYPE == pGroups->groupType)
		{
			mapImGroup[CTools::str2num(pGroups->id)] = imgroupInfo;
		}
		PImGroupList = PImGroupList->next;
	}
	///////释放IM_S_GETCONTACTLIST_ACK中TUP_S_LIST指针/////
	tup_im_release_tup_list(ack.userList);
	tup_im_release_tup_list(ack.contactList);
	tup_im_release_tup_list(ack.userGroupList);
	tup_im_release_tup_list(ack.userGroupMemberList);
	tup_im_release_tup_list(ack.imGroupList);
}

void CContactDlg::UpdateContactListContrl(void)
{
	m_treeContact.DeleteAllItems();

	typedef std::map<TUP_INT64,HTREEITEM> MAP_GROUPTREE;
	MAP_GROUPTREE mapGroupTree;

	//插入所有群组
	MAP_GROUP::iterator itGroup = g_mapGroup.begin();
	MAP_GROUP::iterator itEnd = g_mapGroup.end();
	for(;itGroup!=itEnd;itGroup++)
	{
		IM_S_USERGROUPINFO group = (IM_S_USERGROUPINFO)itGroup->second;
		CString cstrGroupName = CTools::UTF2UNICODE(group.name);
		HTREEITEM item = m_treeContact.InsertItem(cstrGroupName,TVI_ROOT);
		m_treeContact.SetItemImage(item, 2, 2);
		mapGroupTree[group.id] = item;
		m_treeContact.SetItemData(item,(DWORD)group.id);
	}

	//遍历所有成员，插入成员
	MAP_USER_GROUP::iterator itUser = g_mapUserGroup.begin();
	MAP_USER_GROUP::iterator itUserEnd = g_mapUserGroup.end();
	for(;itUser!=itUserEnd;itUser++)
	{
		TUP_INT64 contactID = (TUP_INT64)itUser->first;
		TUP_INT64 groupID = (TUP_INT64)itUser->second;

		HTREEITEM item = mapGroupTree[groupID];
		if(NULL != item)
		{
			IM_S_CONTACTNFO contact = g_mapContact[contactID];				
			if(0 == contact.staffID)
			{
				CString cstrName = CTools::UTF2UNICODE(contact.name);		
				HTREEITEM subItem = m_treeContact.InsertItem(cstrName,item);
				m_treeContact.SetItemData(subItem,(DWORD)contactID);
				m_treeContact.SetItemImage(subItem, 0, 0);
			}
			else
			{
				IM_S_USERINFO userInfo = g_mapUser[contact.staffID];
				CString cstrAccount =  CTools::UTF2UNICODE(userInfo.account);
				CString cstrDisplayName = CTools::UTF2UNICODE(userInfo.name) + L" "+ cstrAccount;
				HTREEITEM subItem = m_treeContact.InsertItem(cstrDisplayName,item);
				m_treeContact.SetItemData(subItem,(DWORD)contactID);
				m_treeContact.SetItemImage(subItem, 1, 1);
			}
			

			m_treeContact.Expand(item,TVE_EXPAND);
		}		
	}

	UpdateLocalMenbStatus();

}

void CContactDlg::OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt;
	::GetCursorPos(&pt);
	m_treeContact.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeContact.HitTest(pt,&uFlag);
	if (/*NULL == hSelectedItem || !(TVHT_ONITEM & uFlag)*/ (NULL != hSelectedItem) &&(NULL != m_treeContact.GetParentItem(hSelectedItem)))
	{
		//////双击默认打开该处的联系人，并发起对话///////
		HTREEITEM item = m_treeContact.GetSelectedItem();
		TUP_INT64 conatctID;
		TUP_INT64 groupID;
		if(NULL != item)
		{
			conatctID = (TUP_INT64)m_treeContact.GetItemData(item);
			HTREEITEM parentItem =  m_treeContact.GetParentItem(item);
			groupID  = (TUP_INT64)m_treeContact.GetItemData(parentItem);
		}
		else
		{
			return;
		}
		IM_S_CONTACTNFO contactInfo = g_mapContact[conatctID];

		if(contactInfo.staffID != 0)
		{
			IM_S_USERINFO* pUserInfo= new IM_S_USERINFO;
			IM_S_USERINFO userInfo = g_mapUser[contactInfo.staffID];
			memcpy(pUserInfo,&userInfo,sizeof(IM_S_USERINFO));
			::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_MENU_SEND_IM,NULL,(LPARAM)pUserInfo);
		}
	}


	////////展开关闭组///////
	if (!(NULL == hSelectedItem || !(TVHT_ONITEM & uFlag)))
	{
		m_treeContact.SelectItem(hSelectedItem);
		if (m_treeContact.GetParentItem(hSelectedItem) == NULL)
		{
			int iImageID = -1;
			int iSelectImageID = -1;
			m_treeContact.GetItemImage(hSelectedItem,iImageID,iSelectImageID);
			if(2 == iImageID)
			{
				m_treeContact.SetItemImage(hSelectedItem,3,3);
			}
			else
			{
				m_treeContact.SetItemImage(hSelectedItem,2,2);
			}
		}
	}

}

void CContactDlg::OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_treeContact.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeContact.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_MENU, _T("新建分组"));	
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_CONTACT_MENU, _T("新建联系人"));
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
		return;
	}

	m_treeContact.SelectItem(hSelectedItem);

	if (m_treeContact.GetParentItem(hSelectedItem) != NULL)
	{
		//联系人节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_INSTANTMSG_MENU, _T("发起即时消息"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_DEL_CONTACT_MENU, _T("删除联系人"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_CONTACT_DETAIL_MENU, _T("查看个人详情"));
		//menu.AppendMenu(MF_STRING, ID_PRIGROUP_AUDIOCONF_MENU, _T("加入会议"));

		CMenu submenu;
		submenu.CreatePopupMenu();

		m_mapGroup.clear();
		MAP_GROUP::iterator itGroup = g_mapGroup.begin();
		MAP_GROUP::iterator itEnd = g_mapGroup.end();
		UINT umenuid = ID_PRIGROUP_CONTACT_MOVE_MENU_START;
		for(;itGroup!=itEnd;itGroup++)
		{
			IM_S_USERGROUPINFO group = (IM_S_USERGROUPINFO)itGroup->second;
			CString strGroupName = CTools::UTF2UNICODE(group.name);
			submenu.AppendMenu(MF_STRING, umenuid,  strGroupName);
			m_mapGroup[umenuid] = group.id;
			umenuid++;
		}

		menu.AppendMenu(MF_BYPOSITION | MF_POPUP, (UINT)submenu.m_hMenu,  _T("移动联系人至"));
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
	else
	{
		//分组节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_MODIFY_MENU, _T("重命名"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_DEL_MENU, _T("删除分组"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_CONTACT_MENU, _T("新建联系人"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_UC_CONTACT_MENU, _T("新建好友"));		
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
}
void CContactDlg::OnClickPriGroupMenuItem(UINT uID)
{
	HTREEITEM item = m_treeContact.GetSelectedItem();
	TUP_INT64 groupID;
	if(NULL != item)
	{
		groupID = (TUP_INT64)m_treeContact.GetItemData(item);
	}

	switch (uID)
	{

	case ID_PRIGROUP_MODIFY_MENU:
		{
			CUserGroupDlg dlg;
			dlg.m_iShowType = 1;
			INT_PTR nResponse =dlg.DoModal();
			if(nResponse != IDOK)
			{
				return;
			}
			CString name = dlg.GetGroupName();

			TUP_BOOL bResult;
			IM_S_MODUSERGROUP_ARG arg;
			arg.id = groupID;
			CTools::CString2Char(name,arg.name,IM_D_MAX_NAME_LENGTH);
			TUP_RESULT tRet = tup_im_modusergroup(&arg,&bResult);
			if(TUP_SUCCESS != tRet || TUP_FALSE == bResult)
			{
				AfxMessageBox(_T("tup_im_modusergroup fail."));
			}			
		}
		break;
	case ID_PRIGROUP_ADD_MENU:
		{
			CUserGroupDlg dlg;
			dlg.m_iShowType = 0;
			INT_PTR nResponse =dlg.DoModal();
			if(nResponse != IDOK)
			{
				return;
			}
			CString name = dlg.GetGroupName();

			IM_S_ADDUSERGROUP_ARG arg;
			IM_S_ADDUSERGROUP_ACK ack;
			arg.index = -1;
			CTools::CString2Char(name,arg.name,IM_D_MAX_NAME_LENGTH);
			TUP_RESULT tRet = tup_im_addusergroup(&arg,&ack);
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(_T("tup_im_addusergroup fail."));
			}
		}
		break;
	case ID_PRIGROUP_DEL_MENU:
		{
//Add by lWX294490 to fix DTS2015071005783 at 2015-7-16 begin
			MAP_USER_GROUP::iterator itUser = g_mapUserGroup.begin();
			MAP_USER_GROUP::iterator itUserEnd = g_mapUserGroup.end();
			for(;itUser!=itUserEnd;itUser++)
			{	
				if((TUP_INT64)itUser->second == groupID)
				{
					TUP_INT64 contactID = (TUP_INT64)itUser->first;
					IM_S_DELCONTACT_ARG delArg;
					delArg.contactID = contactID;
					delArg.groupID = groupID;
					TUP_BOOL bResult;
					TUP_RESULT tRet = tup_im_delfriendorcontact(&delArg,&bResult);
					if(TUP_SUCCESS != tRet || TUP_FALSE == bResult)
					{
						AfxMessageBox(_T("tup_im_delfriendorcontact fail."));
					}
				}
			}
//Add by lWX294490 to fix DTS2015071005783 at 2015-7-16 end

			TUP_BOOL bResult;
			TUP_RESULT tRet = tup_im_delusergroup(groupID,&bResult);
			if(TUP_SUCCESS != tRet || TUP_FALSE == bResult)
			{
				AfxMessageBox(_T("tup_im_delusergroup fail."));
			}
		}
		break;

	}

	GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
	UpdateContactListContrl();


}
void CContactDlg::OnClickPriContactMenuItem(UINT uID)
{
	HTREEITEM item = m_treeContact.GetSelectedItem();
	TUP_INT64 conatctID;
	TUP_INT64 groupID;
	if(NULL != item)
	{
		conatctID = (TUP_INT64)m_treeContact.GetItemData(item);
		HTREEITEM parentItem =  m_treeContact.GetParentItem(item);
		groupID  = (TUP_INT64)m_treeContact.GetItemData(parentItem);
	}
	else
	{
		return;
	}
	IM_S_CONTACTNFO contactInfo = g_mapContact[conatctID];

	switch(uID)
	{
	case ID_PRIGROUP_CONTACT_DETAIL_MENU:
		{			
			if(contactInfo.staffID == 0)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_SHOW_DETAIL,FALSE,(LPARAM)&contactInfo);
			}
			else
			{
				IM_S_USERINFO* pUserInfo= new IM_S_USERINFO;
				IM_S_USERINFO userInfo = g_mapUser[contactInfo.staffID];
				memcpy(pUserInfo,&userInfo,sizeof(IM_S_USERINFO));
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_SHOW_DETAIL,TRUE,(LPARAM)pUserInfo);
			}	
		}
		break;
	case ID_PRIGROUP_INSTANTMSG_MENU:
		{
			if(contactInfo.staffID != 0)
			{
				IM_S_USERINFO* pUserInfo= new IM_S_USERINFO;
				IM_S_USERINFO userInfo = g_mapUser[contactInfo.staffID];
				memcpy(pUserInfo,&userInfo,sizeof(IM_S_USERINFO));
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_MENU_SEND_IM,NULL,(LPARAM)pUserInfo);
			}

		}
		break;
	case ID_PRIGROUP_DEL_CONTACT_MENU:
		{
			IM_S_DELCONTACT_ARG delArg;
			delArg.contactID = conatctID;
			delArg.groupID = groupID;
			TUP_BOOL bResult;
			TUP_RESULT tRet = tup_im_delfriendorcontact(&delArg,&bResult);
			if(TUP_SUCCESS != tRet || TUP_FALSE == bResult)
			{
				AfxMessageBox(_T("tup_im_delfriendorcontact fail."));
			}
			GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
			UpdateContactListContrl();
		}
		break;
	case ID_PRIGROUP_MODIFY_CONTACT_MENU:
		{
			

		}
		break;
	}
	if(uID >= ID_PRIGROUP_CONTACT_MOVE_MENU_START && uID <= ID_PRIGROUP_CONTACT_MOVE_MENU_END)
	{
		IM_S_MODCONTACTGROUP_ARG arg;
		arg.newGroupID = m_mapGroup[uID];
		arg.oldGroupID = groupID;
		arg.contactID = conatctID;
		////仅支持移动操作//////
		arg.type = IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_MOVE;
		TUP_BOOL bRet;
		TUP_RESULT tRet = tup_im_movecontactgroup(&arg,&bRet);
		if(tRet != TUP_SUCCESS && !bRet)
		{
			AfxMessageBox(L"tup_im_movecontactgroup failed.");
		}

		PostMessage(WM_UPDATE_CONTACT,NULL,NULL);
	}
}

BOOL CContactDlg::PreTranslateMessage(MSG* pMsg)
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
LRESULT CContactDlg::OnUpdateConatct(WPARAM wParam,LPARAM lParam)
{
	GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
	UpdateContactListContrl();
	return 0L;
}
bool CContactDlg::UpdateConStatus(std::string _account ,IM_E_USER_ONLINESTATUS _status)
{
	//////1.账号对应的群组号///////
	if (m_treeContact.GetCount() == 0)
	{
		return false;
	}
	TUP_INT64 conatctID;
	TUP_INT64 groupID;
	TUP_INT64 m_staffID;

    MAP_USER::iterator itUser = g_mapUser.begin();
	MAP_USER::iterator itUserEnd = g_mapUser.end();
	for (;itUser != itUserEnd;itUser++)
	{
		IM_S_USERINFO userInfo = (IM_S_USERINFO)itUser->second;
		std::string m_name = userInfo.account;
		if (m_name == _account)
		{
			m_staffID = userInfo.staffID;
			break;
		}

	}
	//////非本地成员状态不处理/////
	if (itUser == itUserEnd)
	{
		return false ;
	}

	MAP_CONTACT::iterator itCon = g_mapContact.begin();
	MAP_CONTACT::iterator itConEnd = g_mapContact.end();
	for(;itCon != itConEnd;itCon++)
	{
		IM_S_CONTACTNFO ContaInfo = (IM_S_CONTACTNFO)itCon->second ;
		if (ContaInfo.staffID == m_staffID)
		{
			conatctID = ContaInfo.id;
			break;
		}

	}


	MAP_USER_GROUP::iterator itGroup = g_mapUserGroup.begin();
	MAP_USER_GROUP::iterator itGroupEnd = g_mapUserGroup.end();
	for(;itGroup != itGroupEnd;itGroup++)
	{
		if (conatctID == (TUP_INT64)itGroup->first)
		{
			groupID = (TUP_INT64)itGroup->second;
		}

	}


	//////2.查找Tree中的位置////////

	HTREEITEM GroupNode;
	GroupNode= m_treeContact.GetRootItem();
	for (unsigned int i=0;i< m_treeContact.GetCount();i++)
	{
		if (groupID == m_treeContact.GetItemData(GroupNode))
		{
			break;
		}
		GroupNode = m_treeContact.GetNextSiblingItem(GroupNode);
      
	}
   HTREEITEM UserNode;
   UserNode= m_treeContact.GetChildItem(GroupNode);
   while (m_treeContact.GetItemData(UserNode) != conatctID)
   {
	   UserNode = m_treeContact.GetNextSiblingItem(UserNode);
   }
	if (UserNode != NULL)
	{
		switch(_status)
		{
		case IM_E_STATUS_BUSY:
        case IM_E_STATUS_DONTDISTURB :
			m_treeContact.SetItemImage(UserNode, 4, 4);
			break;
		case IM_E_STATUS_ONLINE:
			m_treeContact.SetItemImage(UserNode ,5, 5);
			break;
		case IM_E_STATUS_LEAVE :
			m_treeContact.SetItemImage(UserNode ,6, 6);
			break;
		default:
			m_treeContact.SetItemImage(UserNode ,0, 0);
		    break;
		}
		return true;
		LocalStatus[_account] = _status;
	}
	return false;
}

void CContactDlg::UpdateLocalMenbStatus()
{
	////////刷新g_mapUser中所有人的状态////////

	MAP_USER::iterator itUser = g_mapUser.begin();
	MAP_USER::iterator itUserEnd = g_mapUser.end();
	for (;itUser != itUserEnd;itUser++)
	{
		IM_S_USERINFO userInfo = (IM_S_USERINFO)itUser->second;
		/////查询状态//////
		TUP_S_LIST arg;
		char account[IM_D_MAX_ACCOUNT_LENGTH] = {0};
		strcpy_s(account,IM_D_MAX_ACCOUNT_LENGTH,userInfo.account);
		arg.data = account;
		arg.next = NULL;
		TUP_RESULT tRet = tup_im_detectuserstatus(&arg);
		
		///////录入初始状态//////
		std::string m_localAccount;
		m_localAccount = userInfo.account;
		LocalStatus[m_localAccount] = IM_E_STATUS_OFFLINE;

	}
}
void CContactDlg::OnNMClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt;
	::GetCursorPos(&pt);
	m_treeContact.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeContact.HitTest(pt,&uFlag);

	//判断鼠标单击位置
	if (!(NULL == hSelectedItem || !(TVHT_ONITEM & uFlag)))
	{
		m_treeContact.SelectItem(hSelectedItem);
		if (m_treeContact.GetParentItem(hSelectedItem) == NULL)
		{
			//节点位置
			int iImageID = -1;
			int iSelectImageID = -1;
			m_treeContact.GetItemImage(hSelectedItem,iImageID,iSelectImageID);
			if(2 == iImageID)
			{
				//收缩节点
				m_treeContact.Expand(hSelectedItem, TVE_COLLAPSE);
				m_treeContact.SetItemImage(hSelectedItem,3,3);
			}
			else
			{
				//展开节点
				m_treeContact.Expand(hSelectedItem, TVE_EXPAND);
				m_treeContact.SetItemImage(hSelectedItem,2,2);
			}
		}
	}
}
