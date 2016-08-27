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
#include "afxwin.h"
#include "afxcmn.h"


// CSelectDlg 对话框

class CSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelectDlg();

// 对话框数据
	enum { IDD = IDD_SELECTUSER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnGetdispinfoListFriend(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnUpdateEdit1();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnNMDblclkListFriend(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSelect(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
public:	
	typedef std::map<int,IM_S_USERINFO> STAFF_MAP;
	STAFF_MAP m_mapStaff;							//当前所有的联系人
public:
	CEdit m_edtFind;
	CListCtrl m_listContact;		//联系人
	CListCtrl m_listSelect;			//选择的联系人
	void ShowFriendList();						//显示个人通讯录的人
	void ShowEntContactList(CString cstrKey);	//显示企业通讯录的人
	void AddSelectUser(int i);
	void DelSelectUser(int i);
	MAP_SELECT_USER m_mapSelectAccount;
	void GetSelectUser(MAP_SELECT_USER&);
};

