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
#include <map>
#include "ConfDlg.h"
#include "ConfInComing.h"
#include "DataConfDlg.h"

#define USER_AGENT						 "Huawei SoftCoPCA"
#define WM_USER_KICKOUT					 (WM_USER + 1111)
#define WM_LOGOUT						 (WM_USER + 1112)
#define WM_INTOCONF						 (WM_USER + 1113)
#define WM_REFRESHMEMBER				 (WM_USER + 1114)
#define WM_CONF_INCMING					 (WM_USER + 1115)			//会议来电
#define WM_CONF_CREATE_RET				 (WM_USER + 1116)			//创建会议成功
#define WM_CAll_END		      		     (WM_USER + 1117)			//会叫结束
#define WM_CLEAR_MEETING_LIST	  		 (WM_USER + 1118)			//清空会议列表
#define WM_DATACONF_CREAT				 (WM_USER + 1119)			//创建数据会议
#define WM_DATACONF_JOINSUCCESS			 (WM_USER + 1120)			//加入数据会议成功
#define WM_DATACONF_AS_STATE_NOTIFY		 (WM_USER + 1121)			//共享状态通知
#define WM_DATACONF_AS_OWNER_NOTIFY		 (WM_USER + 1122)			//共享拥有者通知
#define WM_DATACONF_AS_SCREENDATA_NOTIFY (WM_USER + 1123)			//共享数据通知
#define WM_DATACONF_UPDATE_PRESENTINFO   (WM_USER + 1124)			//主讲人变更消息
#define WM_DATACONF_USER_ADD             (WM_USER + 1125)			//数据会议与会者加入会议
#define WM_DATACONF_USER_DEL             (WM_USER + 1126)			//数据会议与会者离开会议
#define WM_DATACONF_END                  (WM_USER + 1127)			//与会者收到自己被踢出会议
#define WM_DATACONF_BE_CLOSED            (WM_USER + 1128)			//与会者收到会议被关闭
#define WM_DATACONF_AS_ON_CHANNEL        (WM_USER + 1129)
#define WM_ONEKEY_TO_CONF_RESULT         (WM_USER + 1130)           //CALL_E_EVT_SERVERCONF_CONNECT_ONEKEY_TO_CONF_RESULT

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}

#define TUP_UINT32_MAX 4294967295

// CeSDK_TUP_PC_CONF_DemoDlg dialog
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
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonAppintment();
	afx_msg void OnBnClickedButtonLogoff();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonGetMeetinglist();
	afx_msg LRESULT OnLogoutEvent(WPARAM, LPARAM);// 注销事件
	afx_msg LRESULT OnKickoutUser(WPARAM, LPARAM);// 用户被剔出
	afx_msg LRESULT OnInConf(WPARAM, LPARAM);   ///一键入会成功////
	afx_msg LRESULT OnReshMember(WPARAM, LPARAM);  ////刷新与会列表
	afx_msg LRESULT OnConfIncming(WPARAM , LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	bool LoginCallService(void);  ////注册call服务

public:
	CIPAddressCtrl						m_editIP;
	CEdit								m_editPort;
	CEdit								m_editPSD;
	CEdit								m_editAccount;
	CString								m_cstrMettingUrl;
	CListCtrl							m_listMeetingInfo;
	CButton								m_btnMeeting;
	CButton								m_btnGetMeeting;
	CButton								m_btnLogin;
	CButton								m_btnLogoff;
	std::map<int, IM_S_MEETINGINFO>		m_ConferenceList;
	BOOL								m_bLoginFlag;			// 登录状态
	BOOL								m_bLogOff;				// 注销时不退出对话框
	std::string                         m_strSipAccount;
	ConfDlg								*m_pConfDlg;
	CDataConfDlg						*m_pDataConfDlg;
	std::string							m_strConfServerAddress;
	bool                                m_bInConference;

public:
	void EnableRelativeControl();
	void DisableRelativeControl();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDetail();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAdd();
protected:
	//afx_msg LRESULT OnConfIncming(WPARAM wParam, LPARAM lParam);
public:
	BOOL getAccountINfoByBingNum(std::string _phoneID, IM_S_USERINFO& _userInfo);
protected:
	afx_msg LRESULT OnConfCreateRet(WPARAM wParam, LPARAM lParam);	//创建会议成功
public:
	IM_S_USERINFO m_CurrentUserInfo;
protected:
	afx_msg LRESULT OnClearMeetingList(WPARAM wParam, LPARAM lParam);
public:
	bool getAccountInfo(std::string _KeyWord, IM_E_IMUSERQUERYTYPE _ImUserQueryType, IM_S_USERINFO& _userInfo);
};
