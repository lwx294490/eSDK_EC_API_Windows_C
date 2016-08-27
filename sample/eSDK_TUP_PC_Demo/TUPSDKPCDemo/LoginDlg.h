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


// LoginDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define UMSERVERLENT 128
// CLoginDlg 对话框
class CLoginDlg : public CDialog
{
// 构造
public:
	CLoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonLogin();
	DECLARE_MESSAGE_MAP()
private:
	bool m_bLoginFlag;
	CString m_cstrAccount;
	std::string m_strSipAccount;
	std::string m_strDataConfAddr;
	int m_iStatus;
public:
	static CLoginDlg& instance(){static CLoginDlg s_LoginDlg; return s_LoginDlg;}
	bool GetLoginflag(){return m_bLoginFlag;}	
	CString GetLoginAccount() {return m_cstrAccount;}
	std::string GetSipAccount() {return m_strSipAccount;}
	int GetStatus()	{return m_iStatus;}
public:
	CIPAddressCtrl m_ipCtrlServerIP;
	CEdit m_edtServerPort;
	CEdit m_edtLoginAccount;
	CEdit m_edtPWD;	
	CComboBox m_cbxStatus;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	void GetOffLineLoginInfo(OFFLINE_LOGININFO& m_offlineLoginInfo,IM_S_SERVICEPROFILEACK& m_serverceAck,std::string& m_strLocalIP);
	void GetOffLineUserInfo(OFFLINE_USERINFO& m_offlineUserInfo,IM_S_LOGIN_ARG& m_LoginArg);
	BOOL GetDeviceInfo(std::string& sys, std::string& ver, std::string& sn);
	BOOL LoginUM(IM_S_LOGIN_ARG& m_LoginArg,IM_S_SERVICEPROFILEACK& m_serverceAck,std::string& m_strLocalIP);
	void DeleteOfflineInfo(OFFLINE_LOGININFO& m_offlineLoginInfo,OFFLINE_USERINFO& m_offlineUserInfo);
};

