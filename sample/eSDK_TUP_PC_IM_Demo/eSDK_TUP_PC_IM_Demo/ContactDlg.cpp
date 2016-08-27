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

// ContactDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eSDK_TUP_PC_IM_Demo.h"
#include "ContactDlg.h"
#include "Tools.h"
#include "UserGroupDlg.h"
#include "ReGroupNameDlg.h"

// CContactDlg �Ի���

IMPLEMENT_DYNAMIC(CContactDlg, CDialog)

CContactDlg::CContactDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContactDlg::IDD, pParent)
{
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
	ON_COMMAND_RANGE(ID_PRIGROUP_MODIFY_MENU, ID_PRIGROUP_SENDMESSAGE, &CContactDlg::OnClickPriGroupMenuItem)
	ON_COMMAND_RANGE(ID_PRIGROUP_DEL_CONTACT_MENU, ID_PRIGROUP_CONTACT_MOVE_MENU_END, &CContactDlg::OnClickPriContactMenuItem)
	ON_MESSAGE(WM_UPDATE_CONTACT,&CContactDlg::OnUpdateConatct)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CONTACT, &CContactDlg::OnNMClickTreeContact)
END_MESSAGE_MAP()


// CContactDlg ��Ϣ�������

void CContactDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���'+'�����������˵�ѡ��
	CRect rc;
	m_btnAdd.GetWindowRect(&rc);
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_MENU, _T("�½�����"));	
	//menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_CONTACT_MENU, _T("�½���ϵ��"));
	menu.TrackPopupMenu(TPM_TOPALIGN, rc.left, rc.bottom, this);
}

BOOL CContactDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ������ϵ���б���ͼ�ؼ�
	m_imageList.Create(16, 16, ILC_COLORDDB, 4, 1);
	AddImage(m_imageList, IDB_BITMAP_FRIEND);		//0
	AddImage(m_imageList, IDB_BITMAP_CUSCONTACT);   //1
	AddImage(m_imageList, IDB_BITMAP_UNFOLD);   //2
	AddImage(m_imageList, IDB_BITMAP_FOLD);   //3
	m_treeContact.SetImageList(&m_imageList,LVSIL_NORMAL );
	
	GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser);
	
	//������ʾ��ϵ��
	UpdateContactListContrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CContactDlg::AddImage(CImageList& imageList, UINT _id)
{
	//����ͼƬ
	CBitmap bm;
	bm.LoadBitmap(_id);
	imageList.Add(&bm, RGB(0, 0, 0));
}

//��ȡ��ϵ����Ϣ
void CContactDlg::GetContactList(MAP_GROUP& mapGroup,MAP_USER_GROUP& mapUserGroup,MAP_CONTACT& mapContact,MAP_USER& mapUser)
{
	mapGroup.clear();
	mapUserGroup.clear();
	mapUser.clear();
	mapContact.clear();

	IM_S_GETCONTACTLIST_ARG arg;
	IM_S_GETCONTACTLIST_ACK ack;
	arg.isSyncAll = TUP_TRUE;
	CTools::CString2Char(L"19000000000000",arg.timestamp,IM_D_MAX_TIMESTAMP_LENGTH);
	//��ȡ����������ϵ�ˣ������������ʾ
	TUP_RESULT tRet = tup_im_getcontactlist(&arg,&ack);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getcontactlist failed."));
		return;
	}

	//���ѷ���������Ϣ�������ѷ�����Ϣ����mapGroup��
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

	//���ѷ������ϵ�˶�Ӧ��ϵ
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

	//�Զ�����ϵ���б�
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

	//�����б�
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
	///////�ͷ�IM_S_GETCONTACTLIST_ACK��TUP_S_LISTָ��/////
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

	//��������Ⱥ��
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

	//�������г�Ա�������Ա
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
			
			//չ������ѡ��
			m_treeContact.Expand(item,TVE_EXPAND);
		}		
	}

}

//���˫����ϵ������
void CContactDlg::OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CPoint pt;
	::GetCursorPos(&pt);
	m_treeContact.ScreenToClient(&pt);

	UINT uFlag = 0;
	//�õ����λ�õ����ڵ�
	HTREEITEM hSelectedItem = m_treeContact.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		//���û�е��нڵ���˳�
		return;
	}

	//ѡ�и����Ľڵ�
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

//����Ҽ�������ϵ������
void CContactDlg::OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_treeContact.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeContact.HitTest(pt,&uFlag);
	//����˿հ״����½���ϵ��
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_MENU, _T("�½�����"));	
		//menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_CONTACT_MENU, _T("�½���ϵ��"));
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
		return;
	}

	m_treeContact.SelectItem(hSelectedItem);

	if (m_treeContact.GetParentItem(hSelectedItem) != NULL)
	{
		//��ϵ�˽ڵ�
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_INSTANTMSG_MENU, _T("����ʱ��Ϣ"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_DEL_CONTACT_MENU, _T("ɾ����ϵ��"));

		CMenu submenu;
		submenu.CreatePopupMenu();

		//��ʾ������Ϣ
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

		menu.AppendMenu(MF_BYPOSITION | MF_POPUP, (UINT)submenu.m_hMenu,  _T("�ƶ���ϵ����"));
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
	else
	{
		//����ڵ�
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_MODIFY_MENU, _T("������"));
		menu.AppendMenu(MF_STRING, ID_PRIGROUP_DEL_MENU, _T("ɾ������"));
//		menu.AppendMenu(MF_STRING, ID_PRIGROUP_SENDMESSAGE, _T("���ͼ�ʱ��Ϣ"));
//		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_CONTACT_MENU, _T("�½���ϵ��"));
//		menu.AppendMenu(MF_STRING, ID_PRIGROUP_ADD_UC_CONTACT_MENU, _T("�½�����"));		
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
}

//ѡ��������
void CContactDlg::OnClickPriGroupMenuItem(UINT uID)
{
	HTREEITEM item = m_treeContact.GetSelectedItem();
	TUP_INT64 groupID;
	CString cstrGroupName;
	if(NULL != item)
	{
		groupID = (TUP_INT64)m_treeContact.GetItemData(item);
		//��ȡ����������
		cstrGroupName = CTools::UTF2UNICODE(g_mapGroup[groupID].name);
	}

	switch (uID)
	{
		case ID_PRIGROUP_ADD_MENU:
		{
			CUserGroupDlg dlg;
			//�����������½����黹������������
			dlg.m_iShowType = 0;
			INT_PTR nResponse =dlg.DoModal();
			if(nResponse != IDOK)
			{
				return;
			}
			CString name = dlg.GetGroupName();

			//�����������Ƿ�����������
			if(!CheckGroupName(name))
				return;

			IM_S_ADDUSERGROUP_ARG arg;
			IM_S_ADDUSERGROUP_ACK ack;
			arg.index = -1;
			CTools::CString2Char(name,arg.name,IM_D_MAX_NAME_LENGTH);
			TUP_RESULT tRet = tup_im_addusergroup(&arg,&ack);
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(_T("tup_im_addusergroup fail."));
			}
			GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser);
			UpdateContactListContrl();
		}
		break;
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

			//����޸�ǰ���޸ĺ������һ���������κδ���
			if(name.Compare(cstrGroupName) == 0)
				return;

			//�����������Ƿ�����������
			if(!CheckGroupName(name))
				return;

			TUP_BOOL bResult;
			IM_S_MODUSERGROUP_ARG arg;
			arg.id = groupID;
			CTools::CString2Char(name,arg.name,IM_D_MAX_NAME_LENGTH);
			TUP_RESULT tRet = tup_im_modusergroup(&arg,&bResult);
			if(TUP_SUCCESS != tRet || TUP_FALSE == bResult)
			{
				AfxMessageBox(_T("tup_im_modusergroup fail."));
			}			
			GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser);
			UpdateContactListContrl();
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
			GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser);
			UpdateContactListContrl();
		}
		break;
//Del by lwx294490 at 2015-7-13 start
//Send group message function for temporary retention
// 	case ID_PRIGROUP_SENDMESSAGE:
// 		{
// 			::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_MENU_GROUP_SENDMESSAGE,NULL,(LPARAM)groupID);
// 		}
// 		break;
//Del by lwx294490 at 2015-7-13 end
	}
}


//ѡ�е�����ϵ��
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
	case ID_PRIGROUP_INSTANTMSG_MENU:
		{
			//����ʱ��Ϣ
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
			//ɾ����ϵ��
			IM_S_DELCONTACT_ARG delArg;
			delArg.contactID = conatctID;
			delArg.groupID = groupID;
			TUP_BOOL bResult;
			//��ĳ��������ɾ��һ�����ѻ����Զ�����ϵ��
			TUP_RESULT tRet = tup_im_delfriendorcontact(&delArg,&bResult);
			if(TUP_SUCCESS != tRet || TUP_FALSE == bResult)
			{
				AfxMessageBox(_T("tup_im_delfriendorcontact fail."));
			}
			GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser);
			UpdateContactListContrl();
		}
		break;
	}

	//���ѡ�е��Ƿ����е�ĳһ��
	if(uID >= ID_PRIGROUP_CONTACT_MOVE_MENU_START && uID <= ID_PRIGROUP_CONTACT_MOVE_MENU_END)
	{
		IM_S_MODCONTACTGROUP_ARG arg;
		arg.newGroupID = m_mapGroup[uID];
		arg.oldGroupID = groupID;
		arg.contactID = conatctID;
		////��֧���ƶ�����//////
		arg.type = IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_MOVE;
		TUP_BOOL bRet;
		//��ĳ����ϵ�˻��ߺ��Ѵ�ĳ���������ƶ�����һ��������
		TUP_RESULT tRet = tup_im_movecontactgroup(&arg,&bRet);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(L"tup_im_movecontactgroup failed.");
		}

		PostMessage(WM_UPDATE_CONTACT,NULL,NULL);
	}
}

BOOL CContactDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	//����ȥ��ȡ��ϵ���б���Ϣ�����Ҹ��¿ؼ�
	GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser);
	UpdateContactListContrl();	
	return 0L;
}

bool CContactDlg::CheckGroupName(CString &GroupName)
{
	bool GroupNameConvertFlag = false;
	EnsureGroupNameUnique(GroupName, GroupNameConvertFlag);

	//ȷ������Ψһ��
	if(GroupNameConvertFlag)
	{
		bool bPopupFlag = PopupPromptDlg(GroupName);
		return bPopupFlag;
	}
	else
		return true;
}

void CContactDlg::EnsureGroupNameUnique(CString &GroupName, bool &GroupNameConvertFlag)
{
	//��������Ⱥ��
	MAP_GROUP::iterator itGroup = g_mapGroup.begin();
	MAP_GROUP::iterator itEnd = g_mapGroup.end();
	for(;itGroup!=itEnd;itGroup++)
	{
		IM_S_USERGROUPINFO group = (IM_S_USERGROUPINFO)itGroup->second;
		CString cstrGroupName = CTools::UTF2UNICODE(group.name);
		if(cstrGroupName.Compare(GroupName) == 0)
		{
			GroupNameConvertFlag = true;
			GroupName += _T("[1]");
			EnsureGroupNameUnique(GroupName, GroupNameConvertFlag);
			break;
		}
	}

	return;
}

bool CContactDlg::PopupPromptDlg(const CString &cstrPrompt)
{
	CReGroupNameDlg dlg;
	dlg.SetPromptCStr(cstrPrompt);
	INT_PTR nResponse =dlg.DoModal();
	if(nResponse != IDOK)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CContactDlg::OnNMClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CPoint pt;
	::GetCursorPos(&pt);
	m_treeContact.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_treeContact.HitTest(pt,&uFlag);

	//�ж���굥��λ��
	if (!(NULL == hSelectedItem || !(TVHT_ONITEM & uFlag)))
	{
		m_treeContact.SelectItem(hSelectedItem);
		if (m_treeContact.GetParentItem(hSelectedItem) == NULL)
		{
			//�ڵ�λ��
			int iImageID = -1;
			int iSelectImageID = -1;
			m_treeContact.GetItemImage(hSelectedItem,iImageID,iSelectImageID);
			if(2 == iImageID)
			{
				//�����ڵ�
				m_treeContact.Expand(hSelectedItem, TVE_COLLAPSE);
				m_treeContact.SetItemImage(hSelectedItem,3,3);
			}
			else
			{
				//չ���ڵ�
				m_treeContact.Expand(hSelectedItem, TVE_EXPAND);
				m_treeContact.SetItemImage(hSelectedItem,2,2);
			}
		}
	}
}
