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

#pragma once
#include "afxcmn.h"
#include "MainDlg.h"

class CMainDlg;
// CGroupDlg 对话框

class CGroupInviteDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroupInviteDlg)

public:
	CGroupInviteDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGroupInviteDlg();

// 对话框数据
	enum { IDD = IDD_INVITE_GROUP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	
	CString m_inviteGroupName;
	CString m_inviteOwner;
	std::string m_groupId;
	std::string m_account;
	void GetContactList(MAP_GROUP& mapGroup,MAP_USER_GROUP& mapUserGroup,MAP_CONTACT& mapContact,MAP_USER& mapUser,MAP_IMGROUP& mapImGroup);
	afx_msg void OnBnClickedBtagree();
	afx_msg void OnBnClickedBtrefause();
	afx_msg void OnClose();
};
