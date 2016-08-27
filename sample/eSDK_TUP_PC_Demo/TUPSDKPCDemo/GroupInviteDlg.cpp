#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "Tools.h"
#include "GroupInviteDlg.h"

// CGroupDlg 对话框
IMPLEMENT_DYNAMIC(CGroupInviteDlg, CDialog)

CGroupInviteDlg::CGroupInviteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupInviteDlg::IDD, pParent)
	, m_inviteGroupName(_T(""))
	, m_inviteOwner(_T(""))
{
}

CGroupInviteDlg::~CGroupInviteDlg()
{
}

void CGroupInviteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_inviteGroupName);
	DDX_Text(pDX, IDC_EDIT2, m_inviteOwner);
}
BEGIN_MESSAGE_MAP(CGroupInviteDlg, CDialog)

	ON_BN_CLICKED(IDC_BTAGREE, &CGroupInviteDlg::OnBnClickedBtagree)
	ON_BN_CLICKED(IDC_BTREFAUSE, &CGroupInviteDlg::OnBnClickedBtrefause)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
void CGroupInviteDlg::GetContactList(MAP_GROUP& mapGroup,MAP_USER_GROUP& mapUserGroup,MAP_CONTACT& mapContact,MAP_USER& mapUser,MAP_IMGROUP& mapImGroup)
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
void CGroupInviteDlg::OnBnClickedBtagree()
{
	// TODO: 在此添加控件通知处理程序代码
	IM_S_CONFIRM_JOINFIXEDGROUP_ARG arg;
	memset(&arg,0,sizeof(IM_S_CONFIRM_JOINFIXEDGROUP_ARG)); 
	strcpy_s( arg.groupID, sizeof(arg.groupID), m_groupId.c_str());
	strcpy_s( arg.groupName, sizeof(arg. groupName), CTools::UNICODE2UTF(m_inviteGroupName).c_str());
	strcpy_s( arg.memberAccount, sizeof(arg.memberAccount), m_account.c_str());
	strcpy_s( arg.displayName, sizeof(arg. displayName), CTools::UNICODE2UTF(m_inviteOwner).c_str());
	arg.agreeJoin = true;
	TUP_RESULT confirmfixedgroupinviteRet = tup_im_confirmfixedgroupinvite (&arg);
	if(confirmfixedgroupinviteRet == TUP_SUCCESS)
	{
		//AfxMessageBox(_T("you  already had joined the group "));
		GetContactList(g_mapGroup,g_mapUserGroup,g_mapContact,g_mapUser,g_mapImGroup);
		CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if(pMainDlg->m_pGroupDlg)
		{
			pMainDlg->m_pGroupDlg->UpdateGroupListContrl();
		}
		
	}
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_GROUP_INVITEDLG_CLOSE,(WPARAM)this,NULL);
}

void CGroupInviteDlg::OnBnClickedBtrefause()
{
	// TODO: 在此添加控件通知处理程序代码
	IM_S_CONFIRM_JOINFIXEDGROUP_ARG arg;
	memset(&arg,0,sizeof(IM_S_CONFIRM_JOINFIXEDGROUP_ARG));
	strcpy_s( arg.groupID, sizeof(arg.groupID), m_groupId.c_str());
	strcpy_s( arg.groupName, sizeof(arg. groupName), CTools::UNICODE2UTF(m_inviteGroupName).c_str());
	strcpy_s( arg.memberAccount, sizeof(arg.memberAccount), m_account.c_str());
	strcpy_s( arg.displayName, sizeof(arg. displayName), CTools::UNICODE2UTF(m_inviteOwner).c_str());
	arg.agreeJoin = false;
	TUP_RESULT confirmfixedgroupinviteRet = tup_im_confirmfixedgroupinvite (&arg);
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_GROUP_INVITEDLG_CLOSE,(WPARAM)this,NULL);
}

void CGroupInviteDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_GROUP_INVITEDLG_CLOSE,(WPARAM)this,NULL);
}
