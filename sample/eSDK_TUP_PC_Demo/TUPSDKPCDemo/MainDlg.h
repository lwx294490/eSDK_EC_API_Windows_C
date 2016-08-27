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
#include "EntAddrDlg.h"
#include "ContactDlg.h"
#include "GroupDlg.h"
#include "IMDlg.h"
#include "SettingDlg.h"
#include "ImageStatic.h"
#include "DataConfDlg.h"
#include "GroupInviteDlg.h"

// CMainDlg 对话框

class CMainDlg : public CDialog,public CUserQueryHelper
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnStnClickedStaticHead();
	afx_msg void OnBnClickedButtonEntaddr();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickMainMenuItem(UINT nID);
	afx_msg LRESULT OnMenuSendIM(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseIMWnd(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseConfWnd(WPARAM,LPARAM);
	afx_msg LRESULT OnRecvIM(WPARAM,LPARAM);
	afx_msg LRESULT OnUpdateConatct(WPARAM,LPARAM);
	afx_msg LRESULT OnCallConnceted(WPARAM,LPARAM);
	afx_msg LRESULT OnCallEnd(WPARAM,LPARAM);
	afx_msg LRESULT OnCallIncoming(WPARAM,LPARAM);
	afx_msg LRESULT OnCallOutgoing(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseSetDlg(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseEntAddrDlg(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseDetailDlg(WPARAM,LPARAM);
	afx_msg LRESULT OnShowDetailDlg(WPARAM,LPARAM);
	afx_msg LRESULT OnConfIncoming(WPARAM,LPARAM);
	afx_msg LRESULT OnConfCreate(WPARAM,LPARAM);
	afx_msg LRESULT OnConfConnect(WPARAM,LPARAM);
	afx_msg LRESULT OnCALLTOfCreate(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupNotify(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfCreate(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseDataConfWnd(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnKickOutNotify(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnIdentifyNotfiy(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnConfirmJoinNotify(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGroupChatSurface(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGroupDeleteMember(WPARAM wParam,LPARAM IParam);
	afx_msg LRESULT OnHeartBeatNotify(WPARAM wParam,LPARAM IParam);
	afx_msg LRESULT OnDismissFixedGroupNotify(WPARAM wParam,LPARAM IParam);
	afx_msg LRESULT OnGroupInvNotyClose(WPARAM wParam,LPARAM IParam);
	DECLARE_MESSAGE_MAP()

private:
	bool m_bLoginFlag;
	CString m_cstrLoginAccount;
	std::string m_strSipAccount;
	std::string m_strDataConfAddr;
	int m_iLoginStatus;
	CEntAddrDlg *m_pEntAddDlg;
	CContactDlg *m_pContactDlg;
	CSettingDlg* m_pSettingDlg;
	CDetailDlg* m_pDetailDlg;
	CDataConfDlg* m_pDataDonfDlg;
	int heartSum;

public:
	void SetLoginFlag(bool);
	void SetCurLoginAccount(CString&);
	void SetCurSipAccount(std::string&);
	void SetDataConfAddr(std::string& addr){m_strDataConfAddr = addr;}
	std::string GetDataConfAddr()const{return m_strDataConfAddr;}
	CString GetCurLoginAccount(void)const {return m_cstrLoginAccount;}
	void SetCurStatus(int);
	void RefreshControl(void);	
	void Logout(void);
	void ShowSetDlg(void);
	int GetLoginStatus(void){return m_iLoginStatus;};

	//Add by w00321336 to fix DTS2015010702889 at 2015-1-21
	int GetCurStatus() const;

	CDataConfDlg* GetDataConfDlg() {return m_pDataDonfDlg;}
	CContactDlg * GetContacDlg() {return m_pContactDlg ;}
public:
	CStatic m_stcUserName;
	CComboBox m_cbxStatus;
	CEdit m_editSearch;
	CTabCtrl m_tabMainWnd;	
	CEdit m_edtSign;
	CButton m_btnSysMenu;
	CButton m_btnEntAddr;
	afx_msg void OnCbnSelchangeComboStatus();
	CImageStatic m_stcHead;
	afx_msg void OnEnChangeEditSigntrue();
	CGroupDlg* m_pGroupDlg;
	//////数据会议标记/////
	bool m_bisDadtaConf;
};

