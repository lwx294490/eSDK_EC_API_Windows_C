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


// eSDK_TUP_PC_CONF_DemoDlg.h : header file
//

#pragma once

#include "NotifyCallBack.h"
#include "Tools.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <map>

// CeSDK_TUP_PC_CONF_DemoDlg dialog
using namespace std;

typedef enum
{
	MEET_INIT,			//初始状态
	MEET_IDLE,			//空闲
	MEET_REQUEST,		//发起呼叫请求
	MEET_INCOMING,		//来电
	MEET_CONNECTED,		//双方互通
	MEET_ENDED			//会议结束
};

typedef enum GROUPLIST_COLUMNID
{
	COL_MEM_NAME,
	COL_MEM_ACCOUNT,
	COL_MEM_STATUS, 
	COL_MEM_COMPERE, 
	COL_MEM_SPEAK_STATUS
};

typedef std::map<std::string, std::string> MAP_MEET_MEMBER;


class CeSDK_TUP_PC_CONF_DemoDlg : public CDialogEx
{
// Construction
public:
	CeSDK_TUP_PC_CONF_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ESDK_TUP_PC_CONF_DEMO_DIALOG };

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

private:
	CEdit m_editLoginAccount;
	CEdit m_editLoginPassword;
	CIPAddressCtrl m_ipCtrlServerIP;
	CEdit m_editServerPort;
	CButton m_btnLogin;
	CButton m_btnLogOff;
	CButton m_btnLogOut;
	CEdit m_editMeetStatus;
	CButton m_btnMeetStart;
	CButton m_btnMeetEnd;
	CButton m_btnAddMember;
	CButton m_btnDelMember;
	CButton m_btnAcceptMeet;
	CButton m_btnReFuseMeet;
	CButton m_btnLeaveMeet;
	CListCtrl m_listMeetMember;
	CEdit m_editTargetAccount;
	MAP_MEET_MEMBER  m_mapMeetMember;
	bool bLoginFlag;
	std::string m_strSipAccount;
	CString cstrOwnAccount;
	TUP_UINT32 m_uiConfID;
	bool bChairmanFlag;
	bool bInMeetFlag;
	TUP_CHAR localIP[IM_D_IP_LENGTH];    /**本地IP地址 */

private:
	void OnListMemberInit();
	bool LoginUCService(void);
	bool LoginCallService(void);
	void SetLoginSectionCtrl(bool bState);
	void SetLogOutSectionCtrl(bool bState);
	void SetMeetSectionCtrl(int iCallStatus);
	void LogoutService();
	bool getUserInfoByAccount(std::string _account, IM_S_USERINFO& _userInfo);
	bool getUserInfoByBindNo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo);
	bool ListCtrlAndMapAddMember(const CString& AddMemberAccount);
	bool MemberListFindColum(const CString& cstrKey, int iColnum, int& iFind);
	bool AddOtherMeetMember();
	bool MemberListMapFindByBindNo(std::string& strAccount, const std::string& strBindNo);
	void ResourceClear();
	bool InviteNewMember(const CString& cstrTargetAccount);

public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogoff();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonMeetStart();
	afx_msg void OnBnClickedButtonMemberAdd();
	afx_msg LRESULT OnKickOutUser(WPARAM, LPARAM);
	LRESULT OnMeetCreateSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT OnMeetInvite(WPARAM wParam, LPARAM lParam);
	LRESULT OnMeetMemberJoined(WPARAM wParam, LPARAM lParam);
	LRESULT OnMeetMemberRefresh(WPARAM wParam, LPARAM lParam);
	LRESULT OnMeetEnded(WPARAM wParam, LPARAM lParam);
	LRESULT OnMeetShowSpkMember(WPARAM wParam, LPARAM lParam);
	LRESULT OnManagetConnect(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonMeetAccept();
	afx_msg void OnBnClickedButtonMeetRefuse();
	afx_msg void OnBnClickedButtonMeetEnd();
	afx_msg void OnBnClickedButtonMeetLeave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMemberDelete();
	afx_msg void OnNMClickListMeetMember(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	virtual void OnCancel();
};
