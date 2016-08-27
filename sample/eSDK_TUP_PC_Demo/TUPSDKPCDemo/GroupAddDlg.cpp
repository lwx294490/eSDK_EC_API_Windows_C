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
#include "GroupAddDlg.h"
#include "Tools.h"
#include "SelectDlg.h"

// CGroupDlg 对话框

IMPLEMENT_DYNAMIC(CGroupAddDlg, CDialog)

CGroupAddDlg::CGroupAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupAddDlg::IDD, pParent)
	, m_groupName(_T(""))
	, m_groupSynopsis(_T(""))
	, m_groupDescription(_T(""))
{
	pGroup = (CGroupDlg*)pParent;
	memset(m_id,0,IM_D_GROUPID_LENGTH);
}

CGroupAddDlg::~CGroupAddDlg()
{
}

void CGroupAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUP_NAME, m_groupName);
	DDX_Text(pDX, IDC_EDIT_GROUP_SYNOPSIS, m_groupSynopsis);
	DDX_Text(pDX, IDC_EDIT_GROUP_DESCRIPTION, m_groupDescription);
	DDX_Control(pDX, IDC_LIST_MEMBER_LIST, m_groupMemberList);
	DDX_Control(pDX, IDC_RADIO1, m_radioBtnGroup);
	DDX_Control(pDX, IDC_RADIO2, m_radioBtnGroup1);
}


BEGIN_MESSAGE_MAP(CGroupAddDlg, CDialog)
	
	ON_BN_CLICKED(IDOK, &CGroupAddDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_AddMembers, &CGroupAddDlg::OnBnClickedButtonAddmembers)
END_MESSAGE_MAP()

BOOL CGroupAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	LONG lStyle;
	lStyle = GetWindowLong(m_groupMemberList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_groupMemberList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_groupMemberList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_groupMemberList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_groupMemberList.InsertColumn( 0, CTools::UTF2UNICODE(g_Account), LVCFMT_LEFT, 290);//插入列
	m_radioBtnGroup.SetCheck(true);
//	int nRow = m_groupMemberList.InsertItem(0, _T("11"));//插入行
	//m_groupMemberList.SetItemText(nRow, 1, _T("jacky"));//设置数据

	////  限制部分输入框的字符长度 Start//////
	/*((CEdit*)GetDlgItem(IDC_EDIT_GROUP_NAME))->SetLimitText(IM_D_MAX_NAME_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDIT_GROUP_SYNOPSIS))->SetLimitText(IM_D_MAX_DESC_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDIT_GROUP_DESCRIPTION))->SetLimitText(IM_D_MAX_DESC_LENGTH);*/
		////  限制部分输入框的字符长度 End//////

	return TRUE;  
}

void CGroupAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//创建群组
	IM_S_IMGROUP_OP_ARG arg;
	IM_S_ADDIMGROUP_ACK ack;
	memset(&arg,0,sizeof(IM_S_IMGROUP_OP_ARG));
	memset(&ack,0,sizeof(IM_S_ADDIMGROUP_ACK));
	int len = 0,i=0,count = 0;
	CString tempEmpty;
	UpdateData(TRUE);
	
	std::string groupname = CTools::UNICODE2UTF(m_groupName);
	if(m_groupName.GetLength()>IM_D_MAX_NAME_LENGTH-1)
	{
		AfxMessageBox(_T("the group name length is too long"));
		return;
	}
	if(m_groupSynopsis.GetLength()>IM_D_MAX_DESC_LENGTH-1)
	{
		AfxMessageBox(_T("the group synopsis length is too long"));
		return;
	}
	if(m_groupDescription.GetLength()>IM_D_MAX_DESC_LENGTH-1)
	{
		AfxMessageBox(_T("the group description length is too long"));
		return;
	}
	if(groupname.find_first_not_of(" ") == string::npos)
	{
		AfxMessageBox(_T("the group name can't empty"));
		return;
	}
	
	strcpy_s( arg.fixedgroupInfo.name, sizeof(arg.fixedgroupInfo.name), CTools::UNICODE2UTF(m_groupName).c_str());
	strcpy_s( arg.fixedgroupInfo.owner, sizeof(arg.fixedgroupInfo.owner), g_Account.c_str());
	strcpy_s( arg.fixedgroupInfo.desc, sizeof(arg.fixedgroupInfo.desc), CTools::UNICODE2UTF(m_groupSynopsis).c_str());
	strcpy_s( arg.fixedgroupInfo.manifesto, sizeof(arg.fixedgroupInfo.manifesto), CTools::UNICODE2UTF(m_groupDescription).c_str());
	arg.fixedgroupInfo.capacity = 200;
	if(m_radioBtnGroup.GetCheck())
	{
		arg.fixedgroupInfo.autoJoinFlag = IM_E_IMGROUP_JOIN_AUTO;
	}
	if(m_radioBtnGroup1.GetCheck())
	{
		arg.fixedgroupInfo.autoJoinFlag = IM_E_IMGROUP_JOIN_NEED_APPROVE;
	}
	if(!strcmp(m_id,""))
	{
		TUP_RESULT addfixedgroupRet = tup_im_addfixedgroup(&arg, &ack);
		if(addfixedgroupRet == TUP_SUCCESS)
		{
			IM_S_ADDIMGROUPMEMBER_ARG groupMember;
			memset(&groupMember,0,sizeof(IM_S_ADDIMGROUPMEMBER_ARG));
			std::string tempAccount;
			std::string tempDisplay;
			TUP_CHAR tempGroupName[IM_D_MAX_NAME_LENGTH]= {0};
			MAP_SELECT_USER::iterator it = m_selUser.begin();
			MAP_SELECT_USER::iterator itEnd = m_selUser.end();
			for(;it!=itEnd;it++)
			{
				strcpy_s( groupMember.groupID, sizeof(groupMember.groupID), ack.id);
				strncpy_s(groupMember.groupName, CTools::UNICODE2UTF(m_groupName).c_str(),IM_D_MAX_NAME_LENGTH);
				tempAccount = it->second.account;
				strcpy_s(groupMember.account,sizeof(groupMember.account),tempAccount.c_str());
				tempDisplay = it->second.name;
				strcpy_s(groupMember.displayName,sizeof(groupMember.displayName),tempDisplay.c_str());
				TUP_RESULT addfixedgroupmemberRet = tup_im_addfixedgroupmember(&groupMember);
			}
		}
		else
		{
			AfxMessageBox(_T("group number has reached the maximum"));
		}
	}
	else
	{
		IM_S_ADDIMGROUPMEMBER_ARG groupMember;
		memset(&groupMember,0,sizeof(IM_S_ADDIMGROUPMEMBER_ARG));
		std::string tempAccount;
		std::string tempDisplay;
		TUP_CHAR tempGroupName[IM_D_MAX_NAME_LENGTH] = {0};
		MAP_SELECT_USER::iterator it = m_selUser.begin();
		MAP_SELECT_USER::iterator itEnd = m_selUser.end();
		for(;it!=itEnd;it++)
		{
			/////此处增加过滤操作/////
			tempAccount = it->second.account;
			if (IsMemberInGroup(tempAccount,m_id))
				continue;

			strcpy_s( groupMember.groupID, sizeof(groupMember.groupID), m_id);
			strcpy_s(groupMember.account,sizeof(groupMember.account),tempAccount.c_str());
			strncpy_s(groupMember.groupName,CTools::UNICODE2UTF(m_groupName).c_str(),IM_D_MAX_NAME_LENGTH);
			tempDisplay = it->second.name;
			strcpy_s(groupMember.displayName,sizeof(groupMember.displayName),tempDisplay.c_str());
			TUP_RESULT addfixedgroupmemberRet = tup_im_addfixedgroupmember(&groupMember);
		}
	}
	m_selUser.clear();
	GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
	if(pGroup)
	{
		pGroup->UpdateGroupListContrl();
	}
	OnOK();
}

bool CGroupAddDlg::IsMemberInGroup(std::string _account,std::string _groupID)
{
	IM_S_REQUESTIMGROUPMEMBERS_ARG groupMembArg;
	IM_S_GROUPUSERLIST groupList;

	strcpy_s(groupMembArg.groupID,IM_D_GROUPID_LENGTH,_groupID.c_str());
	groupMembArg.isSyncAll = TUP_TRUE;
	strcpy_s(groupMembArg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");

	tup_im_getfixedgroupmembers(&groupMembArg,&groupList);
	TUP_S_LIST* list =  groupList.memberInfo;
	while(list != NULL)
	{
		IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
		if(NULL != groupUser)
		{
			if(strcmp(_account.c_str(),groupUser->account) == 0)
			{
				tup_im_release_tup_list(groupList.memberInfo);
				return true;
			}
		}
		list = list->next;
	}
	//////释放IM_S_GROUPUSERLIST中的TUP_S_LIST指针/////
	tup_im_release_tup_list(groupList.memberInfo);
}

void CGroupAddDlg::OnBnClickedButtonAddmembers()
{
	// TODO: 在此添加控件通知处理程序代码
	m_groupMemberList.DeleteAllItems();
	CSelectDlg dlg;
	if(IDOK != dlg.DoModal())
	{
		return;
	}

	dlg.GetSelectUser(m_selUser);	
	int iSize = m_selUser.size();
	if(iSize == 0)
	{
		return;		
	}

	MAP_SELECT_USER::iterator it = m_selUser.begin();
	MAP_SELECT_USER::iterator itEnd = m_selUser.end();
	for(;it!=itEnd;it++)
	{
		CString cstrAccount = CTools::UTF2UNICODE(it->second.name)+CTools::UTF2UNICODE(it->second.account);
		int nRow = m_groupMemberList.InsertItem(0, cstrAccount);//插入行
		m_groupMemberList.SetItemText(nRow, 1, _T(""));//设置数据
	}
}


void CGroupAddDlg::GetContactList(MAP_GROUP& mapGroup,MAP_USER_GROUP& mapUserGroup,MAP_CONTACT& mapContact,MAP_USER& mapUser,MAP_IMGROUP& mapImGroup)
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
		if(NULL == PImGroupList)
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