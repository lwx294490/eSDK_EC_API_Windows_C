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
#include "NotifyCallBack.h"
#include "eSDK_TUP_PC_CALL_Demo.h"
#include "Tools.h"

// CeSDK_TUP_PC_CALL_DemoDlg dialog
#define USER_AGENT				"Huawei SoftCoPCA"

typedef enum
{
	CALL_INIT,			//初始状态
	CALL_IDLE,			//空闲
	CALL_REQUEST,		//发起呼叫请求
	CALL_INCOMING,		//来电
	CALL_RING,			//振铃
	CALL_CONNECTED,		//双方互通
	CALL_ENDED			//通话结束
};

class CeSDK_TUP_PC_CALL_DemoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CeSDK_TUP_PC_CALL_DemoDlg)

public:
	CeSDK_TUP_PC_CALL_DemoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CeSDK_TUP_PC_CALL_DemoDlg();

// Dialog Data
	enum { IDD = IDD_CALL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
public:
	afx_msg LRESULT OnCallIncoming(WPARAM,LPARAM);
	afx_msg LRESULT OnCallRing(WPARAM,LPARAM);
	afx_msg LRESULT OnCallConnected(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCallEnded(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnKickOutUser(WPARAM, LPARAM);
	afx_msg LRESULT OnLoginResult(WPARAM, LPARAM);
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonCall();
	afx_msg void OnBnClickedButtonAcceptCall();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonLogoff();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonRefuseCall();
	afx_msg void OnBnClickedButtonCallHold();
	afx_msg void OnBnClickedButtonSpeaker();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonMicrophone();
	afx_msg void OnClose();
	afx_msg void OnNMReleasedcaptureSliderSpeaker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderMicro(NMHDR *pNMHDR, LRESULT *pResult);
	
private:
	bool LoginUCService(void);
	bool LoginCallService(std::string strsipaccount,std::string strsipserver,std::string strsippwd);
	void SetCallSectionCtrl(int iCallStatus);
	void SetLoginSectionCtrl(bool bState);
	void SetLogOutSectionCtrl(bool bState);
	void SpeakerVolumeSave();
	void MicroVolumeSave();
	void SetPartCallSectionCtrl(int nCmdShow);

private:
	CIPAddressCtrl m_ipCtrlServerIP;
	CEdit m_editServerPort;
	CEdit m_editLoginAccount;
	CEdit m_editLoginPassword;
	CEdit m_editTargetAccount;
	CButton m_btnCallHold;
	CButton m_btnSpeaker;
	CButton m_btnMicro;
	CButton m_btnDisconnect;
	CStatic m_stcCallStatus;
	CButton m_btnCall;
	CStatic m_stcCallTime;
	CStatic m_stcCallNumber;
	CStatic m_stcCallName;
	CEdit m_editCallNumber;
	CEdit m_editCallName;
	CButton m_btnAcceptCall;
	CButton m_btnRefuseCall;
	CButton m_btnLogOff;
	CButton m_btnLogOut;
	CButton m_btnLogin;
	CEdit m_editCallStatus;
	CEdit m_editCallTime;
	CSliderCtrl m_sldSpeaker;
	CSliderCtrl m_sldMicro;
	bool bLoginFlag;
	bool bCalledFlag;
	TUP_UINT32 m_callid;
	TUP_UINT64 m_callConnectTime;
	std::string m_strSipAccount;
	std::string m_strCalleerSipNumber; ////被叫方账号////
	TUP_CHAR localIP[1024];    /**本地IP地址 */
public:


	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
