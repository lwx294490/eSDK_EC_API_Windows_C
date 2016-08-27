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
#include "GroupAddDlg.h"
#include "GroupSearchDlg.h"

class CGroupAddDlg;
// CGroupDlg 对话框

class CGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroupDlg)

public:
	CGroupDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGroupDlg();

// 对话框数据
	enum { IDD = IDD_GROUP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnClickGroupMenuItem(UINT nID);
	afx_msg void OnNMDblclkTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAddgroup();
	afx_msg void OnBnClickedButtonFindgroup();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CTreeCtrl m_treeFixedGroup;
	void GetFixedGroupList(MAP_GROUP&,MAP_USER_GROUP&,MAP_CONTACT&,MAP_USER&);
	void UpdateGroupListContrl();
	CGroupAddDlg* m_pGroupAddDlg;
	CGroupSearchDlg* m_pGroupSearchDlg;
	TUP_CHAR m_id[IM_D_GROUPID_LENGTH];
	void OnAddGroupMember(TUP_CHAR* id);
	

};
