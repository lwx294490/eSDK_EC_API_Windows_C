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
#include "afxwin.h"
#include "LoginDlg.h"
#include "GroupDlg.h"
#include "ContactDlg.h"

class CGroupDlg;
class CContactDlg;
// CGroupDlg 对话框

class CGroupAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroupAddDlg)

public:
	CGroupAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGroupAddDlg();

// 对话框数据
	enum { IDD = IDD_GROUP_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
protected:
	bool IsMemberInGroup(std::string _account,std::string _groupID);
public:
	
	CString m_groupName;
	CString m_groupSynopsis;
	CString m_groupDescription;
	CListCtrl m_groupMemberList;
	afx_msg void OnBnClickedOk();
	CButton m_radioBtnGroup;
	CButton m_radioBtnGroup1;
	afx_msg void OnBnClickedButtonAddmembers();
	MAP_SELECT_USER m_selUser;
	CGroupDlg* pGroup;
	void GetContactList(MAP_GROUP& mapGroup,MAP_USER_GROUP& mapUserGroup,MAP_CONTACT& mapContact,MAP_USER& mapUser,MAP_IMGROUP& mapImGroup);
	TUP_CHAR m_id[IM_D_GROUPID_LENGTH];
};
