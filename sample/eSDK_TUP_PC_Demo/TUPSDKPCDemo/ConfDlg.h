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


// CConfDlg 对话框

class CConfDlg : public CDialog, public CUserQueryHelper
{
	DECLARE_DYNAMIC(CConfDlg)

public:
	CConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfDlg();

// 对话框数据
	enum { IDD = IDD_CONF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnConfCreate(WPARAM,LPARAM);
	afx_msg LRESULT OnConfMemAddSuc(WPARAM,LPARAM);
	afx_msg LRESULT OnConfMemAddFailed(WPARAM,LPARAM);
	afx_msg LRESULT OnConfMemSpk(WPARAM,LPARAM);
	afx_msg LRESULT OnConfMemQuit(WPARAM,LPARAM);
	afx_msg LRESULT OnConfConnected(WPARAM,LPARAM);
	afx_msg LRESULT OnConfSubject(WPARAM,LPARAM);
	afx_msg LRESULT OnConfRefreshSingle(WPARAM,LPARAM);
	afx_msg LRESULT OnConfRefreshList(WPARAM,LPARAM);
	afx_msg void OnClickListMemMenuItem(UINT nID);
	CListCtrl m_listMember;
public:
	//void SetLoginAccount(const std::string& strAccount){m_strLoginAccount = strAccount;}
	void RefreshMemberList(CListCtrl& listMember);
	BOOL FindColum(const CString& cstrKey,int colnum,int& iFind);
	void InitAttendeeList();
	void SetGroupID(TUP_INT8 acGroupUri[CALL_D_MAX_LENGTH_NUM]){strcpy_s(m_acGroupUri, CALL_D_MAX_LENGTH_NUM, acGroupUri);};
	void ReshMemberlistByGroupID(std::string m_strGroupID);
public:
	//std::string m_strLoginAccount;
	TUP_UINT32 m_uiConfID;
	TUP_UINT32 m_uiCallID;
	afx_msg void OnClose();
	CButton m_btnAdd;
	CStatic m_stcName;
	bool isChairman;
	CButton m_btnMute;
	CButton m_btnLock;
	CButton m_btnHold;
	CButton m_btnSubject;
	afx_msg void OnBnClickedButtonMute();
	afx_msg void OnBnClickedButtonLock();
	afx_msg void OnBnClickedButtonHold();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDataconf();
	void CloseDlg();
	void PubSelfStatus(IM_E_USER_ONLINESTATUS _status);
private:
	TUP_INT8 m_acGroupUri[CALL_D_MAX_LENGTH_NUM];
};
