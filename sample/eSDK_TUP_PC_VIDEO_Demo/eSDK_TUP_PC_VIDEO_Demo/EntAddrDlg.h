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

#include <map>

// CEntAddrDlg dialog

class CEntAddrDlg : public CDialog
{
	DECLARE_DYNAMIC(CEntAddrDlg)

public:
	CEntAddrDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEntAddrDlg();

// Dialog Data
	enum { IDD = IDD_ENT_ADDR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonLast();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonEnd();
	afx_msg void OnEnUpdateEditFind();
	afx_msg void OnEnUpdateEditPage();
	afx_msg void OnTvnSelchangedTreeDept(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnGetdispinfoListMember(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnNMClickListMember(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	void RefreshControl(void);
	void InsertDpt(TUP_INT64 dptID,HTREEITEM item);
	void ShowDptMember(TUP_INT64 dptID,unsigned int uiPage);
	int GetPageSize();
	void SetPageSize(int iPage);
	void ShowPageCtrl(int iSumPage);
	void RefreshPageSize();
	bool IsContactMenber(std::string _account);

private:
private:
	typedef std::map<int,IM_S_USERINFO> STAFF_MAP;
	STAFF_MAP m_mapStaff;			//当前部门的所有员工
	TUP_INT64 m_iCurDptID;			//当前选中的部门
	unsigned long m_ulStaffSize;	//员工总数
	unsigned int m_uiMaxPage;
	unsigned int m_uiMinPage;
	typedef std::map<int, TUP_INT64> MENU_GROUP_MAP;
	MENU_GROUP_MAP m_mapGroup;

public:
	CTreeCtrl m_treeDpt;
	CStatic m_stcSumPage;
	CListCtrl m_listMember;
	CEdit m_editCurPage;
	CEdit m_editSearch;
	CButton m_btnStart;
	CButton m_btnNext;
	CButton m_btnPrev;
	CButton m_btnEnd;
	afx_msg void OnClickedMenuItem();
};
