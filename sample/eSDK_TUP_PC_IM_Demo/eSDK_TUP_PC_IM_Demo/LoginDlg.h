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


// LoginDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLoginDlg dialog
class CLoginDlg : public CDialogEx
{
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TUPSDKDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginButton();

public:
	bool GetLoginflag(){return m_bLoginFlag;}
	CString GetLoginAccount() {return m_cstrAccount;}

private:
	CIPAddressCtrl m_ipCtrlServerIP;
	CEdit m_edtServerPort;
	CEdit m_edtLoginAccount;
	CEdit m_edtPWD;
	bool m_bLoginFlag;
	CString m_cstrAccount;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
